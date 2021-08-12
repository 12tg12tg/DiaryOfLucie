#pragma once
#include "image.h"

#define ZFLOORMAP	1
#define ZCOL1		2
#define ZCOL2		3
#define ZUNIT		4
#define ZCOL3		5
#define ZCOL4		6
#define ZEFFECT		7
#define ZABOVEMAP	8
#define ZMAXLAYER	8

#define MINT		RGB(88, 245, 206)

static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
class gameNode
{
private:

	//image* _backBuffer;//백버퍼
	//void setBackBuffer();//백버프셋팅
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update(); //계산하는곳
	virtual void render(/*HDC hdc*/);


	image* getBackBuffer()const { return _backBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return _backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

};

