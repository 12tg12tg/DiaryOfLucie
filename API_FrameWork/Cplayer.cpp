#include "framework.h"
#include "Cplayer.h"

HRESULT Cplayer::init()
{
	this->imageInit();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_speed = 5;
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	_drection = DIRECTION::DOWN;
	_player.weapon = WEAPONSTATE::EMPTY;
	
	return S_OK;
}

void Cplayer::release()
{
}

void Cplayer::update()
{
}

void Cplayer::render()
{
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("°È±â", "images/Player/°È±â.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
}
