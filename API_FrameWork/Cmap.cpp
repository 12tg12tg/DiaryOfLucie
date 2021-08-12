#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{

}

Cmap::~Cmap()
{
}

HRESULT Cmap::init()
{
	IMAGE->addImage("배경화면", "images/map/ground95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("산", "images/map/!m95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("산뒤", "images/map/par95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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
	IMAGE->findImage("산")->render(getMemDC());
	IMAGE->findImage("배경화면")->render(getMemDC());
	IMAGE->findImage("산뒤")->render(getMemDC());
}




