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
	IMAGE->addImage("95배경", "images/map/ground95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95픽셀", "images/map/!m95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95가림", "images/map/par95.bmp", 1104, 960, true, RGB(255, 0, 255));
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




