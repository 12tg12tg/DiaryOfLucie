#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("95¹è°æ", "images/map/ground95.bmp", 1104,960, true, RGB(255, 0, 255));
	_collisionMap =IMAGE->addImage("95ÇÈ¼¿", "images/map/!m95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95°¡¸²", "images/map/par95.bmp", 1104, 960, true, RGB(255, 0, 255));

}

Cmap::~Cmap()
{
}

HRESULT Cmap::init()
{
<<<<<<< HEAD
	_door._bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_door._topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_door._rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_door._leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);

	summonMon(4);
=======
	IMAGE->addImage("95¹è°æ", "images/map/ground95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95ÇÈ¼¿", "images/map/!m95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95°¡¸²", "images/map/par95.bmp", 1104, 960, true, RGB(255, 0, 255));
>>>>>>> origin/ì˜ˆê· ìž‘ì—…
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
	IMAGE->findImage("95ÇÈ¼¿")->render(getMemDC());
	IMAGE->findImage("95¹è°æ")->render(getMemDC());
	IMAGE->findImage("95°¡¸²")->render(getMemDC());


		 
	
	
}

Cmap2::Cmap2()
{
	IMAGE->addImage("57¹è°æ", "images/map/ground57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("57ÇÈ¼¿", "images/map/!m57.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("57°¡¸²", "images/map/par57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door._bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_door._topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_door._rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_door._leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{
	monpos[0] = { 445,570 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };
	summonMon(4);

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
	IMAGE->findImage("57ÇÈ¼¿")->render(getMemDC());
	IMAGE->findImage("57¹è°æ")->render(getMemDC());
	IMAGE->findImage("57°¡¸²")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap3::Cmap3()
{
	IMAGE->addImage("104¹è°æ", "images/map/ground104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("104ÇÈ¼¿", "images/map/!m104.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("104°¡¸²", "images/map/par104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door._bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_door._topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_door._rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_door._leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap3::~Cmap3()
{
}

HRESULT Cmap3::init()
{
	

	summonMon(4);
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
	IMAGE->findImage("104ÇÈ¼¿")->render(getMemDC());
	IMAGE->findImage("104¹è°æ")->render(getMemDC());
	IMAGE->findImage("104°¡¸²")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}
	

Cmap4::Cmap4()
{
	IMAGE->addImage("105¹è°æ", "images/map/ground105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("105ÇÈ¼¿", "images/map/!m105.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("105°¡¸²", "images/map/par105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door._bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_door._topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_door._rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_door._leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap4::~Cmap4()
{
}

HRESULT Cmap4::init()
{
	summonMon(4);

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
	IMAGE->findImage("105ÇÈ¼¿")->render(getMemDC());
	IMAGE->findImage("105¹è°æ")->render(getMemDC());
	IMAGE->findImage("105°¡¸²")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap5::Cmap5()
{
	IMAGE->addImage("115¹è°æ", "images/map/ground115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("115ÇÈ¼¿", "images/map/!m115.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("115°¡¸²", "images/map/par115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door._bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_door._topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_door._rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_door._leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}

Cmap5::~Cmap5()
{
}

HRESULT Cmap5::init()
{
	summonMon(4);
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

	IMAGE->findImage("115ÇÈ¼¿")->render(getMemDC());
	IMAGE->findImage("115¹è°æ")->render(getMemDC());
	IMAGE->findImage("115°¡¸²")->render(getMemDC());

	if (_isDebug) RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	if (_isDebug) RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	if (_isDebug) RectMakeCenter(0, WINSIZEY / 2, 200, 200);
}
