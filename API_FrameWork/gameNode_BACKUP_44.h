#pragma once
#include "image.h"
//Z·¹ÀÌ¾î¼³Á¤
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

//ÃÖ´ë·¹ÀÌ¾î
#define ZMAXLAYER	10

//»ö»óÁ¤ÀÇ
#define MINT		RGB(88, 245, 206)

<<<<<<< HEAD
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _DOLBuffer = IMAGE->addImage("DOLBuffer", WINSIZEX*2, WINSIZEY*2);	//ÆÀÇÁ¿ë DC
=======
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX+300, WINSIZEY+300);
>>>>>>> ìƒˆë¡œíƒœì–´ë‚˜ìžë¸Œëžœì¹˜
class gameNode
{
private:

	//image* _backBuffer;//¹é¹öÆÛ
	//void setBackBuffer();//¹é¹öÇÁ¼ÂÆÃ
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update(); //°è»êÇÏ´Â°÷
	virtual void render(/*HDC hdc*/);


	image* getBackBuffer()const { return _backBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return _backBuffer->getMemDC(); }

	HDC getDolDC()const { return _DOLBuffer->getMemDC(); }		//ÆÀÇÁ¿ë DC

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);

};

