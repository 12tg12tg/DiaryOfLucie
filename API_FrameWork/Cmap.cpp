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
	IMAGE->addImage("95���", "images/map/ground95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95�ȼ�", "images/map/!m95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("95����", "images/map/par95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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




