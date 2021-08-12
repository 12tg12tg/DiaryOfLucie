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
	IMAGE->addImage("���ȭ��", "images/map/ground95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("��", "images/map/!m95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("���", "images/map/par95.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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
	IMAGE->findImage("��")->render(getMemDC());
	IMAGE->findImage("���ȭ��")->render(getMemDC());
	IMAGE->findImage("���")->render(getMemDC());
}




