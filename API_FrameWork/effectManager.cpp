#include "framework.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager()
{
}

effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{

    return S_OK;
}

void effectManager::release()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        //����Ʈ�� ��� �� vIter
        for (mIter = vIter->begin(); mIter != vIter->end(); )
        {
            //����� ������ �����.
            if (mIter->second.size() != 0)
            {
                //����Ʈ Ŭ������ ���� ����
                viEffect vArriter;
                for (vArriter = mIter->second.begin(); vArriter!=mIter->second.end(); )
                {
                    //����Ʈ Ŭ���� ������
                    (*vArriter)->release();
                    SAFE_DELETE(*vArriter);
                    vArriter = mIter->second.erase(vArriter);
                }
            }
            else 
            {
                ++mIter;
            }
        }
    }

}

void effectManager::update()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                (*vArriter)->update();
            }

        }
    }

}

void effectManager::render()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                (*vArriter)->render();
            }

        }
    }
}

void effectManager::addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{
    image* img;
    vEffect vEffectBuffer;
    mEffect mArrEffect;

    if (IMAGE->findImage(imageName))
    {
        img = IMAGE->findImage(imageName);
    }
    else
    {
        img = IMAGE->addImage(effectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
    }

    //����ũ�⸸ŭ ����Ʈ�� �Ҵ� �� �ʱ�ȭ �ؼ� ���ͷ� �����.
    for (size_t i = 0; i < buffer; i++)
    {
        vEffectBuffer.push_back(new effect);
        vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
    }

    //���۸� �ʿ� �־��ְ�
    mArrEffect.insert(make_pair(effectKey, vEffectBuffer));
    //��Ż���ۿ� ���� �ִ´�.
    m_vTotalEffect.push_back(mArrEffect);
}

void effectManager::play(string effectKey, int x, int y)
{
    viTotalEffect vIter;
    miEffect mIter;

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            //ã�� Ű���� �ƴ϶�� �� ���� �ٷ� ��������.
            if (!(mIter->first == effectKey)) break;

            //����Ʈ Ű���� ��ġ�ϸ� ����Ʈ�� �÷�������.
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                if ((*vArriter)->getIsRunning()) continue;
                (*vArriter)->startEffect(x, y);
                return;
            }
        }
    }
}
