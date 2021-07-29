#include "framework.h"
#include "screenManager.h"

screenManager::screenManager(){}

screenManager::~screenManager(){}

HRESULT screenManager::init()
{
	_bg1.img = IMAGE->addImage("bg1-1", "images/round1/background1-1.bmp", 1518, WINSIZEY);
	_bg1.alpha = 255;
	_bg1.count = 0;
	_bg1.frameX = 0;
	
	_bg2.img = IMAGE->addImage("bg1-2", "images/round1/background1-2.bmp", 1518, WINSIZEY);
	_bg2.alpha = 255;
	_bg2.count = 0;
	_bg2.frameX = 0;

	_bgSlow.img = IMAGE->addImage("´À¸°º°", "images/round1/backgroundstar1.bmp", 1518, WINSIZEY, true);
	_bgSlow.alpha = 255;
	_bgSlow.count = 0;
	_bgSlow.frameX = 0;

	_bgFast.img = IMAGE->addImage("ºü¸¥º°", "images/round1/faststar.bmp", 1518, WINSIZEY, true);
	_bgFast.alpha = 255;
	_bgFast.count = 0;
	_bgFast.frameX = 0;

	_fireWork1.img = IMAGE->addFrameImage("Å«¿øÆøÁ×", "images/round1/firework1.bmp", 1296, 162,8, 1, true);
	_fireWork1.alpha = 255;
	_fireWork1.count = 0;
	_fireWork1.frameX = 0;

	_fireWork2.img = IMAGE->addFrameImage("¿øºÐ¼öÆøÁ×", "images/round1/firework2.bmp", 816, 111, 7, 1, true);
	_fireWork2.alpha = 255;
	_fireWork2.count = 0;
	_fireWork2.frameX = 0;

	_fireWork3.img = IMAGE->addFrameImage("ÀÛÀº¿øÆøÁ×", "images/round1/firework3.bmp", 585, 111, 5, 1, true);
	_fireWork3.alpha = 255;
	_fireWork3.count = 0;
	_fireWork3.frameX = 0;

	_fireWork4.img = IMAGE->addFrameImage("¹Ù·ÎºÐ¼öÆøÁ×1", "images/round1/firework4.bmp", 384, 96, 4, 1, true);
	_fireWork4.alpha = 255;
	_fireWork4.count = 0;
	_fireWork4.frameX = 0;

	_fireWork5.img = IMAGE->addFrameImage("¹Ù·ÎºÐ¼öÆøÁ×2", "images/round1/firework5.bmp", 384, 96, 4, 1, true);
	_fireWork5.alpha = 255;
	_fireWork5.count = 0;
	_fireWork5.frameX = 0;

	_fadeOut1.img = IMAGE->addImage("¹àÀºÆäÀÌµå¾Æ¿ô", "images/screen/fadeout1.bmp", WINSIZEX, WINSIZEY);
	_fadeOut1.alpha = 255;
	_fadeOut1.count = 0;
	_fadeOut1.frameX = 0;

	_fadeOut2.img = IMAGE->addImage("ºí·¢ÆäÀÌµå¾Æ¿ô", "images/screen/fadeout2.bmp", WINSIZEX, WINSIZEY);
	_fadeOut2.alpha = 255;
	_fadeOut2.count = 0;
	_fadeOut2.frameX = 0;

	return S_OK;
}

void screenManager::release()
{
}

void screenManager::update()
{
}

void screenManager::render()
{
}

void screenManager::blackfadeOut()
{
	if (_fadeOut2.alpha != 0) {
		_fadeOut2.img->alphaRender(getMemDC(), _fadeOut2.alpha);
 		_fadeOut2.alpha -= 3;
	}
}

void screenManager::blackfadein()
{
	if (_fadeOut2.alpha != 255) {
		_fadeOut2.img->alphaRender(getMemDC(), _fadeOut2.alpha);
		_fadeOut2.alpha += 3;
	}
	else {
		_fadeOut2.img->alphaRender(getMemDC(), _fadeOut2.alpha);
	}
}

void screenManager::showFireWork1()
{
	if (_fireWork1.frameX <= _fireWork1.img->getMaxFrameX())
	{
		_fireWork1.count++;
		_fireWork1.img->frameRender(getMemDC(), 100, 400, _fireWork1.frameX, 0);
		if(_fireWork1.count%5==0)
			_fireWork1.frameX++;
	}
}

void screenManager::showFireWork2()
{
	if (_fireWork2.frameX <= _fireWork2.img->getMaxFrameX())
	{
		_fireWork2.count++;
		_fireWork2.img->frameRender(getMemDC(), 250, 400, _fireWork2.frameX, 0);
		if (_fireWork2.count % 5 == 0)
			_fireWork2.frameX++;
	}
}


void screenManager::showFireWork3()
{
	if (_fireWork3.frameX <= _fireWork2.img->getMaxFrameX())
	{
		_fireWork3.count++;
		_fireWork3.img->frameRender(getMemDC(), 400, 400, _fireWork3.frameX, 0);
		if (_fireWork3.count % 5 == 0)
			_fireWork3.frameX++;
	}
}

void screenManager::showFireWork4()
{
	if (_fireWork4.frameX <= _fireWork2.img->getMaxFrameX())
	{
		_fireWork4.count++;
		_fireWork4.img->frameRender(getMemDC(), 700, 350, _fireWork4.frameX, 0);
		if (_fireWork4.count % 5 == 0)
			_fireWork4.frameX++;
	}
}

void screenManager::showFireWork5()
{
	if (_fireWork5.frameX <= _fireWork2.img->getMaxFrameX())
	{
		_fireWork5.count++;
		_fireWork5.img->frameRender(getMemDC(), 800, 400, _fireWork5.frameX, 0);
		if (_fireWork5.count % 5 == 0)
			_fireWork5.frameX++;
	}
}
