#pragma once
#include "image.h"
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _DOLBuffer = IMAGE->addImage("DOLBuffer", 1920, 1017);	//������ DC
class gameNode
{
private:

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

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

	RECT getClRect() { return _rt; }
};

