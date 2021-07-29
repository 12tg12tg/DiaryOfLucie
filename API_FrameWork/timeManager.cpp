#include "framework.h"
#include "timeManager.h"

timeManager::timeManager()
{
}

timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{

	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void timeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];

	string strFrame;

	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(0, 0, 255));

//����� �����
#ifdef _DEBUG

	if (_timer != nullptr)
	{
		//FPS
		sprintf_s(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		//��ü ����ð�
		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		//�������Ӵ� ����ð�
		sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}

#else
	if (_timer != nullptr)
	{
		//FPS
		sprintf_s(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

	}

#endif // _DEBUG


}
