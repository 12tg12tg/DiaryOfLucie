#include "framework.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime 함수를 사용하기 위해 라이브러리를 추가한 것. : 윈도우 경과시간을 리턴해준다.

timer::timer()
{
}

timer::~timer()
{
}

HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) //타이머의 주파수를 반환하는 녀석
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); //cpu의 클럭수를 얻어주는 녀석

		//초당 시간 계산 범위 //고성능 타이머를 사용하면 초당 마이크로세컨드까지 값이들어간다.
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime(); //밀리세컨드단위 시간으로 초당 천번을 카운트해줌.
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
	//고성능 타이머를 지원한다면
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime); //마이크로초단위 계산
	}
	else {
		_curTime = timeGetTime(); //밀리세컨드단위 계산
	}
	//마지막시간과 현재시간의 경과량
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f/lockFPS)) //고정프레임시간을 만족할 때까지 돌리자
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;					//마지막 시간 기록
	_FPSFrameCount++;						//자동으로 프레임카운트 증가
	_FPStimeElapsed += _timeElapsed;		//초당 프레임 시간 경과량 증가
	_worldTime += _timeElapsed;				//전체 시간 경과량 증가

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
