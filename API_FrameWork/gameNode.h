#pragma once
#include "image.h"
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _DOLBuffer = IMAGE->addImage("DOLBuffer", WINSIZEX*3, WINSIZEY*3);	//������ DC
static float StretchRatio = 1.5;													//������ ���
class gameNode
{
private:
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
	void setStretchRatio(float rt) { StretchRatio = rt; }		//������ ���

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);
	RECT getClRect() { return _rt; }	//����â�� �簢�� ��������(0, 0, ����, ����)
};

