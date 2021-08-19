#include "framework.h"
#include "gameNode.h"

gameNode::gameNode(){}

gameNode::~gameNode(){}

HRESULT gameNode::init()
{
	

	//타이머란 일정한 주기마다 정해진 함수를 실행
	//1.인자 : 윈도우 핸들, 타이머 번호, 타이머 주기(1000ms=1초), NULL이면 WM_TIMER 
	//SetTimer(m_hWnd, 1, 10, NULL);

	////매니저 초기화
	//InputManager->init();
	//IMAGE->init();
	//setBackBuffer();


	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;//석세스오케이(성공했다)
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		//매니저 초기화
		InputManager->init();
		IMAGE->init();
		TIME->init();
		SOUND->init();
	}

	return S_OK;
}

//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{
	//타이머 해제

	if (_managerInit)
	{
		KillTimer(m_hWnd, 1); //킬타이머안하면 종료해도 메모리가 샌다.

		//매니저 해제
		SCENE->release();
		IMAGE->release();
		TIME->release();
		SOUND->release();
		ANIMATION->release();
		EFFECT->release();
		ZORDER->release();
		BUTTON->release();

		InputManager->releaseSingleton();
		RND->releaseSingleton();
		IMAGE->releaseSingleton();
		TIME->releaseSingleton();
		TXT->releaseSingleton();
		SCENE->releaseSingleton();
		SOUND->releaseSingleton();
		ANIMATION->releaseSingleton();
		EFFECT->releaseSingleton();
		OBB->releaseSingleton();
		ZORDER->releaseSingleton();
		BUTTON->releaseSingleton();
		
		//아이템 해제
		ITEM->release();


		//플레이어 해제
		PLAYER->release();
		PLAYER->releaseSingleton();
		PLAYERDATA->release();
		PLAYERDATA->releaseSingleton();
	}
	ReleaseDC(m_hWnd, _hdc);


	//SAFE_DELETE(_backBuffer);
}

void gameNode::update()
{
	//더블버퍼이후 사용하지 않는다 -> false로 바꾸기.
	InvalidateRect(m_hWnd, NULL, false); //무효화
}

void gameNode::render(/*HDC hdc*/)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	//case WM_TIMER:
	//	this->update(); //주기적으로 업데이트 실행
	//	break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);	
	//	this->render(hdc);
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		//switch (wParam)
		//{
		//case VK_ESCAPE: //ESC
		//	PostQuitMessage(0);
		//	break;
		//}
		break;

	case WM_SIZE:
		GetClientRect(hWnd, &_rt);		//20210816추가 - 윈도우창 사이즈 담기

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
