#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("95배경", "images/map/ground95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95픽셀", "images/map/!m95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95가림", "images/map/par95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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
	IMAGE->findImage("95픽셀")->render(getMemDC());
	IMAGE->findImage("95배경")->render(getMemDC());
	IMAGE->findImage("95가림")->render(getMemDC());


		 
	
	
}

Cmap2::Cmap2()
{
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{
	IMAGE->addImage("57배경", "images/map/ground57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("57픽셀", "images/map/!m57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("57가림", "images/map/par57.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
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
	IMAGE->findImage("57픽셀")->render(getMemDC());
	IMAGE->findImage("57배경")->render(getMemDC());
	IMAGE->findImage("57가림")->render(getMemDC());

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
	IMAGE->addImage("104배경", "images/map/ground104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("104픽셀", "images/map/!m104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("104가림", "images/map/par104.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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
	IMAGE->findImage("104픽셀")->render(getMemDC());
	IMAGE->findImage("104배경")->render(getMemDC());
	IMAGE->findImage("104가림")->render(getMemDC());

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
	IMAGE->addImage("105배경", "images/map/ground105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("105픽셀", "images/map/!m105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("105가림", "images/map/par105.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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
	IMAGE->findImage("105픽셀")->render(getMemDC());
	IMAGE->findImage("105배경")->render(getMemDC());
	IMAGE->findImage("105가림")->render(getMemDC());

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
	IMAGE->addImage("115배경", "images/map/ground115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("115픽셀", "images/map/!m115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("115가림", "images/map/par115.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
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

	IMAGE->findImage("115픽셀")->render(getMemDC());
	IMAGE->findImage("115배경")->render(getMemDC());
	IMAGE->findImage("115가림")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}
