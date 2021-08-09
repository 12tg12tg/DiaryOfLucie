#include "framework.h"
#include "animation.h"

animation::animation() :_frameNum(0), _frameWidth(0), _frameHeight(0), _loop(false), 
_elapseSec(0), _nowPlayIndex(0), _play(false)
{
}

animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
    //���� ������ ����
    _frameWidth = frameW;
    int frameWidthNum = totalW / _frameWidth;
    //���� ������ ����
    _frameHeight = frameH;
    int frameHeightNum = totalH / _frameHeight;

    //�� ������ ��
    _frameNum = frameWidthNum * frameHeightNum;

    //������ ��ġ ��� ����.
    _frameList.clear();

    for (int i = 0; i < frameHeightNum; i++)
    {
        for (int j = 0; j < frameWidthNum; j++)
        {
            POINT framePos;
            framePos.x = j * _frameWidth;
            framePos.y = i * _frameHeight;

            //������ ��ġ ��� �߰�
            _frameList.push_back(framePos);
        }
    }

    //�⺻ ���������� ����.
    setDefPlayFrame();

    _elapseSec = 0;


    return S_OK;
}

void animation::setDefPlayFrame(bool reverse, bool loop)
{
    _loop = loop;
    _playList.clear();

    if (reverse) {
        if (_loop)
        {
            //������
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }
            //������
            for (int i = _frameNum - 2; i > 0; i--)
            {
                _playList.push_back(i);
            }
        }
        else
        {
            //������
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }
            //������
            for (int i = _frameNum - 2; i >= 0; i--)
            {
                _playList.push_back(i);
            }
        }
    }
    else
    {
        //������
        for (int i = 0; i < _frameNum; i++)
        {
            _playList.push_back(i);
        }
    }

}

void animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
    _loop = loop;
    _playList.clear();

    for (int i = 0; i < arrLen; i++)
    {
        _playList.push_back(playArr[i]);
    }
}

void animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
    _loop = loop;
    _playList.clear();

    //���۰� ���� ���� ���(�����ӱ���) ��� ���� �ʴ´�.
    if (start == end)
    {
        _playList.clear();
        stop();
        return;
    }
    //������������ �� �����Ӻ��� ũ�ٸ�
    else if (start > end)
    {
        if (reverse)
        {
            if (_loop)
            {
                for (int i = start; i >= end; i--)
                {
                    _playList.push_back(i);
                }
                for (int i = end+1; i < start; i++)
                {
                    _playList.push_back(i);
                }
            }
            else
            {
                for (int i = start; i >= end; i--)
                {
                    _playList.push_back(i);
                }
                for (int i = end + 1; i <= start; i++)
                {
                    _playList.push_back(i);
                }
            }
        }
        else
        {
            for (int i = start; i >= end; i--)
            {
                _playList.push_back(i);
            }
        }
    }
    //���������� ������������ �������Ӻ��� �������
    else
    {
        if (reverse)
        {
            if (_loop)
            {
                for (int i = start; i <= end; i++)
                {
                    _playList.push_back(i);
                }
                for (int i = end-1; i > start; i--)
                {
                    _playList.push_back(i);
                }
            }
            else
            {
                for (int i = start; i <= end; i++)
                {
                    _playList.push_back(i);
                }
                for (int i = end - 1; i >= start; i--)
                {
                    _playList.push_back(i);
                }
            }
        }
        else
        {
            for (int i = start; i <= end; i++)
            {
                _playList.push_back(i);
            }
        }
    }
}

void animation::setFPS(int framePerSec)
{
    _frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate(float elapsedTime)
{
    if (_play)
    {
        _elapseSec += elapsedTime;

        if (_elapseSec >= _frameUpdateSec)
        {
            _elapseSec -= _frameUpdateSec;
            _nowPlayIndex++;

            if (_nowPlayIndex == _playList.size())
            {
                if (_loop)
                {
                    _nowPlayIndex = 0;
                }
                else
                {
                    _nowPlayIndex--;
                    _play = false;
                }
            }
        }
    }
}

void animation::start()
{
    _play = true;
    _nowPlayIndex = 0;
}

void animation::stop()
{
    _play = false;
    _nowPlayIndex = 0;
}

void animation::pause()
{
    _play = false;
}

void animation::resume()
{
    _play = true;
}
