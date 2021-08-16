#pragma once
#include "image.h"
//Z레이어설정
#define ZFLOORMAP	0
#define ZCOLMAP		1
#define ZEFFECT1	2
#define ZCOL1		3
#define ZCOL2		4
#define ZUNIT		5
#define ZCOL3		6
#define ZCOL4		7
#define ZEFFECT2	8
#define ZABOVEMAP	9

//최대레이어
#define ZMAXLAYER	9

//색상정의
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

