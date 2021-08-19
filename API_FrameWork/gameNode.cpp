#include "framework.h"
#include "gameNode.h"

gameNode::gameNode(){}

gameNode::~gameNode(){}

HRESULT gameNode::init()
{
	

	//Ÿ�̸Ӷ� ������ �ֱ⸶�� ������ �Լ��� ����
	//1.���� : ������ �ڵ�, Ÿ�̸� ��ȣ, Ÿ�̸� �ֱ�(1000ms=1��), NULL�̸� WM_TIMER 
	//SetTimer(m_hWnd, 1, 10, NULL);

	////�Ŵ��� �ʱ�ȭ
	//InputManager->init();
	//IMAGE->init();
	//setBackBuffer();


	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;//������������(�����ߴ�)
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		//�Ŵ��� �ʱ�ȭ
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
	//Ÿ�̸� ����

	if (_managerInit)
	{
		KillTimer(m_hWnd, 1); //ųŸ�̸Ӿ��ϸ� �����ص� �޸𸮰� ����.

		//�Ŵ��� ����
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
		
		//������ ����
		ITEM->release();


		//�÷��̾� ����
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
	//����������� ������� �ʴ´� -> false�� �ٲٱ�.
	InvalidateRect(m_hWnd, NULL, false); //��ȿȭ
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
	//	this->update(); //�ֱ������� ������Ʈ ����
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
		GetClientRect(hWnd, &_rt);		//20210816�߰� - ������â ������ ���

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
