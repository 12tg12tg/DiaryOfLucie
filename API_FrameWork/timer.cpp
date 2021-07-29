#include "framework.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime �Լ��� ����ϱ� ���� ���̺귯���� �߰��� ��. : ������ ����ð��� �������ش�.

timer::timer()
{
}

timer::~timer()
{
}

HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) //Ÿ�̸��� ���ļ��� ��ȯ�ϴ� �༮
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); //cpu�� Ŭ������ ����ִ� �༮

		//�ʴ� �ð� ��� ���� //���� Ÿ�̸Ӹ� ����ϸ� �ʴ� ����ũ�μ�������� ���̵���.
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime(); //�и���������� �ð����� �ʴ� õ���� ī��Ʈ����.
		_timeScale = 0.001f;
	}
	_frameRate = 0;
	_FPSFrameCount = 0;

	_FPStimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	//���� Ÿ�̸Ӹ� �����Ѵٸ�
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime); //����ũ���ʴ��� ���
	}
	else {
		_curTime = timeGetTime(); //�и���������� ���
	}
	//�������ð��� ����ð��� �����
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f/lockFPS)) //���������ӽð��� ������ ������ ������
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;					//������ �ð� ���
	_FPSFrameCount++;						//�ڵ����� ������ī��Ʈ ����
	_FPStimeElapsed += _timeElapsed;		//�ʴ� ������ �ð� ����� ����
	_worldTime += _timeElapsed;				//��ü �ð� ����� ����

	if (_FPStimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPStimeElapsed = 0.0f;
	}


}

unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
