#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("95���", "images/map/ground95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95�ȼ�", "images/map/!m95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95����", "images/map/par95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

}

Cmap::~Cmap()
{
}

HRESULT Cmap::init()
{
	

	
	return S_OK;
}

void Cmap::release()
{

}

void Cmap::update()
{
}

void Cmap::render()
{
	IMAGE->findImage("95�ȼ�")->render(getMemDC());
	IMAGE->findImage("95���")->render(getMemDC());
	IMAGE->findImage("95����")->render(getMemDC());


		 
	
	
}

Cmap2::Cmap2()
{
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{
	IMAGE->addImage("57���", "images/map/ground57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("57�ȼ�", "images/map/!m57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("57����", "images/map/par57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	tagDOOR door;
	door.BOTTOMDOOR = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	door.TOPDOOR = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	door.RIGHTDOOR = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	door.LEFTDOOR = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
	return S_OK;
}

void Cmap2::release()
{
}

void Cmap2::update()
{
}

void Cmap2::render()
{
	IMAGE->findImage("57�ȼ�")->render(getMemDC());
	IMAGE->findImage("57���")->render(getMemDC());
	IMAGE->findImage("57����")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap3::Cmap3()
{
}

Cmap3::~Cmap3()
{
}

HRESULT Cmap3::init()
{
	IMAGE->addImage("104���", "images/map/ground104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("104�ȼ�", "images/map/!m104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("104����", "images/map/par104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	tagDOOR door;
	door.BOTTOMDOOR = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	door.TOPDOOR = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	door.RIGHTDOOR = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	door.LEFTDOOR = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
	return S_OK;
}

void Cmap3::release()
{
}

void Cmap3::update()
{
}

void Cmap3::render()
{
	IMAGE->findImage("104�ȼ�")->render(getMemDC());
	IMAGE->findImage("104���")->render(getMemDC());
	IMAGE->findImage("104����")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}
	

Cmap4::Cmap4()
{
}

Cmap4::~Cmap4()
{
}

HRESULT Cmap4::init()
{
	IMAGE->addImage("105���", "images/map/ground105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("105�ȼ�", "images/map/!m105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("105����", "images/map/par105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	tagDOOR door;
	door.BOTTOMDOOR = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	door.TOPDOOR = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	door.RIGHTDOOR = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	door.LEFTDOOR = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
	return S_OK;
}

void Cmap4::release()
{
}

void Cmap4::update()
{
}

void Cmap4::render()
{
	IMAGE->findImage("105�ȼ�")->render(getMemDC());
	IMAGE->findImage("105���")->render(getMemDC());
	IMAGE->findImage("105����")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap5::Cmap5()
{
}

Cmap5::~Cmap5()
{
}

HRESULT Cmap5::init()
{
	IMAGE->addImage("115���", "images/map/ground115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("115�ȼ�", "images/map/!m115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("115����", "images/map/par115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	tagDOOR door;
	door.BOTTOMDOOR = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	door.TOPDOOR = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	door.RIGHTDOOR = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	door.LEFTDOOR = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
	return S_OK;
}

void Cmap5::release()
{
	
}

void Cmap5::update()
{
}

void Cmap5::render()
{

	IMAGE->findImage("115�ȼ�")->render(getMemDC());
	IMAGE->findImage("115���")->render(getMemDC());
	IMAGE->findImage("115����")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}
