#pragma once
#include "image.h"
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _DOLBuffer = IMAGE->addImage("DOLBuffer", WINSIZEX*3, WINSIZEY*3);	//������ DC
class gameNode
{
private:
	HWND hWnd;
	//image* _backBuffer;//�����
	//void setBackBuffer();//���������
	HDC _hdc;
	bool _managerInit;
	RECT _rt;
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update(); //����ϴ°�
	virtual void render(/*HDC hdc*/);


	image* getBackBuffer()const { return _backBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return _backBuffer->getMemDC(); }

	HDC getDolDC()const { return _DOLBuffer->getMemDC(); }		//������ DC
	HWND gethwnd()const { return hWnd; }

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

	RECT getClRect() { return _rt; }
};

