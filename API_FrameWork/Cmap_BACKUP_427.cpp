#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("211¹è°æ", "images/map/ground211.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("211ÇÈ¼¿", "images/map/!m211.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("211°¡¸²", "images/map/Par211.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	monpos[0] = { 350,350 };
	monpos[1] = { 495,446 };
	monpos[2] = { 477,544 };
	monpos[3] = { 760,437 };
}

Cmap::~Cmap()
{
}

HRESULT Cmap::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap::release()
{
}

void Cmap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap::render()
{


	ZORDER->ZorderRender(IMAGE->findImage("211¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("211°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("211ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap2::Cmap2()
{
	IMAGE->addImage("57¹è°æ", "images/map/ground57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("57ÇÈ¼¿", "images/map/!m57.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("57°¡¸²", "images/map/Par57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right 
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	monpos[0] = { 507,192 };
	monpos[1] = { 620,237 };
	monpos[2] = { 446,383 };
	monpos[3] = { 369,401 };
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;


}

void Cmap2::release()
{
}

void Cmap2::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap2::render()
{

	ZORDER->ZorderRender(IMAGE->findImage("57¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("57°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug) ZORDER->ZorderRender(IMAGE->findImage("57ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap3::Cmap3()
{
	IMAGE->addImage("104¹è°æ", "images/map/ground104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("104ÇÈ¼¿", "images/map/!m104.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("104°¡¸²", "images/map/Par104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 333, 20, 100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25, 110);//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom
	monpos[0] = { 350,350 };
	monpos[1] = { 495,446 };
	monpos[2] = { 477,544 };
	monpos[3] = { 760,437 };
}

Cmap3::~Cmap3()
{
}

HRESULT Cmap3::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 768, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap3::release()
{

}

void Cmap3::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap3::render()
{


	ZORDER->ZorderRender(IMAGE->findImage("104¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("104°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug) ZORDER->ZorderRender(IMAGE->findImage("104ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 280, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -130, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 250, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 580, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}


Cmap4::Cmap4()
{
	IMAGE->addImage("105¹è°æ", "images/map/ground105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("105ÇÈ¼¿", "images/map/!m105.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("105°¡¸²", "images/map/Par105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 333, 20, 100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25, 110);//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom
	monpos[0] = { 414,366 };
	monpos[1] = { 542,421 };
	monpos[2] = { 764,410 };
	monpos[3] = { 537,646 };
}

Cmap4::~Cmap4()
{
}

HRESULT Cmap4::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 768, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap4::release()
{
}

void Cmap4::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap4::render()
{

	ZORDER->ZorderRender(IMAGE->findImage("105¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("105°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("105ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 280, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -130, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 250, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 580, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap5::Cmap5()
{
	IMAGE->addImage("115¹è°æ", "images/map/ground115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("115ÇÈ¼¿", "images/map/!m115.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("115°¡¸²", "images/map/Par115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	monpos[0] = { 429,347 };
	monpos[1] = { 566,353 };
	monpos[2] = { 497,230 };
	monpos[3] = { 756,423 };
}

Cmap5::~Cmap5()
{
}

HRESULT Cmap5::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap5::release()
{

}

void Cmap5::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap5::render()
{


	ZORDER->ZorderRender(IMAGE->findImage("115¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("115°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("115ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap6::Cmap6()
{
	IMAGE->addImage("50¹è°æ", "images/map/ground50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("50ÇÈ¼¿", "images/map/!m50.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("50°¡¸²", "images/map/Par50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 333, 20, 100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25, 110);//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom
	monpos[0] = { 632,406 };
	monpos[1] = { 459,462 };
	monpos[2] = { 367,276 };
	monpos[3] = { 692,392 };
}

Cmap6::~Cmap6()
{
}

HRESULT Cmap6::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 768, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;

}

void Cmap6::release()
{
}

void Cmap6::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap6::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("50¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("50°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("50ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 280, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -130, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 250, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 580, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap7::Cmap7()
{
	IMAGE->addImage("51¹è°æ", "images/map/ground51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("51ÇÈ¼¿", "images/map/!m51.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("51°¡¸²", "images/map/Par51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	monpos[0] = { 507,192 };
	monpos[1] = { 620,237 };
	monpos[2] = { 406,383 };
	monpos[3] = { 369,401 };
}

Cmap7::~Cmap7()
{
}

HRESULT Cmap7::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap7::release()
{
}

void Cmap7::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap7::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("51¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("51°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("51ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap8::Cmap8()
{
	IMAGE->addImage("100¹è°æ", "images/map/ground100.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("100ÇÈ¼¿", "images/map/!m100.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("100°¡¸²", "images/map/Par100.bmp", 1008, 768, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 333, 20, 100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25, 110);//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom

	monpos[0] = { 662,402 };
	monpos[1] = { 606,480 };
	monpos[2] = { 351,272 };
	monpos[3] = { 593,260 };
}

Cmap8::~Cmap8()
{
}

HRESULT Cmap8::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 768, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap8::release()
{
}

void Cmap8::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap8::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("100¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("100°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("100ÇÈ¼¿"), ZCOLMAP, WINSIZEY, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 250, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -130, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 250, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 590, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap9::Cmap9()
{
	IMAGE->addImage("108¹è°æ", "images/map/ground108.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("108ÇÈ¼¿", "images/map/!m108.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("108°¡¸²", "images/map/Par108.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	monpos[0] = { 504,156 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };

}

Cmap9::~Cmap9()
{
}

HRESULT Cmap9::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	if (!(getClear()))
	{
		summonMon(4);
	}
	return S_OK;
}

void Cmap9::release()
{
}

void Cmap9::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	_gold_coin->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void Cmap9::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("108¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("108°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("108ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

Cmap10::Cmap10()
{
	IMAGE->addImage("114¹è°æ", "images/map/ground114.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("114ÇÈ¼¿", "images/map/!m114.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("114°¡¸²", "images/map/Par114.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

}

Cmap10::~Cmap10()
{
}

HRESULT Cmap10::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);

	return S_OK;
}

void Cmap10::release()
{

}

void Cmap10::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void Cmap10::render()
{

	ZORDER->ZorderRender(IMAGE->findImage("114¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("114°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("114ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
}

chestMap::chestMap()
{
	IMAGE->addImage("»óÀÚ¹æ¹è°æ", "images/map/chestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("»óÀÚ¹æÇÈ¼¿", "images/map/!mchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("»óÀÚ¹æ°¡¸²", "images/map/ParchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_chest = new chest;
	_chest->add(504, 336);
}

chestMap::~chestMap()
{
}

HRESULT chestMap::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void chestMap::release()
{
	SAFE_DELETE(_chest);
}

void chestMap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	_chest->update(bm);
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void chestMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("»óÀÚ¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("»óÀÚ¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("»óÀÚ¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_chest->render();
}

shopMap::shopMap()
{
	IMAGE->addImage("»óÁ¡¹æ¹è°æ", "images/map/ground103.bmp", 960, 576, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("»óÁ¡¹æÇÈ¼¿", "images/map/!m103.bmp", 960, 576, true, RGB(255, 0, 255));
	IMAGE->addImage("»óÁ¡¹æ°¡¸²", "images/map/Par103.bmp", 960, 576, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 364, 25, 140);//left

	_door[1].Door = RectMake(530, 0, 90, 25); //top

	_door[2].Door = RectMake(940, 310, 25, 115);//right

	_door[3].Door = RectMake(436, 560, 140, 25); //bottom

	_shop = new shop;
	_shop->add(534-14, 64+8 - 3);
}

shopMap::~shopMap()
{
}

HRESULT shopMap::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		960, 576, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void shopMap::release()
{
	SAFE_DELETE(_shop);
}

void shopMap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	_shop->update(bm);
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void shopMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("»óÁ¡¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("»óÁ¡¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("»óÁ¡¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 470, -140, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 870, 220, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 405, 430, _portal);
	}
	_shop->render();
}

statueMap::statueMap()
{
	IMAGE->addImage("¼®»ó¹æ¹è°æ", "images/map/statueMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("¼®»ó¹æÇÈ¼¿", "images/map/!mstatueMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("¼®»ó¹æ°¡¸²", "images/map/ParstatueMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	_statue = new statue;
	_statue->add(450, 336);
}

statueMap::~statueMap()
{
}

HRESULT statueMap::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void statueMap::release()
{
	SAFE_DELETE(_statue);
}

void statueMap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	_statue->update(bm);
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void statueMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("¼®»ó¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("¼®»ó¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("¼®»ó¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}

	_statue->render();
}

moruMap::moruMap()
{
	IMAGE->addImage("¸ð·ç¹æ¹è°æ", "images/map/moruMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("¸ð·ç¹æÇÈ¼¿", "images/map/!mmoruMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("¸ð·ç¹æ°¡¸²", "images/map/ParmoruMap.bmp", 1008, 672, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_moru = new moru;
	_moru->add(504, 336);
}

moruMap::~moruMap()
{
}

HRESULT moruMap::init()
{
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void moruMap::release()
{
	SAFE_DELETE(_moru);
}

void moruMap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}

	_moru->update(bm);
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void moruMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("¸ð·ç¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("¸ð·ç¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("¸ð·ç¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_moru->render();
}

stage1_Boss::stage1_Boss(int currentboss)
{
	stage = currentboss;
	IMAGE->addImage("º¸½º¹æ¹è°æ", "images/map/stage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("º¸½º¹æÇÈ¼¿", "images/map/!mstage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("º¸½º¹æ°¡¸²", "images/map/Parstage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom

	IMAGE->addImage("Å¸ÀÌÆ²_º¸½ºÇÃ¶óÀÓ", "images/bossUi/Boss_flime.bmp", WINSIZEX, WINSIZEY, true);
	IMAGE->addImage("Å¸ÀÌÆ²_º¸½º½½¶óÀÓ", "images/bossUi/Boss_slime.bmp", WINSIZEX, WINSIZEY, true);
	IMAGE->addImage("Å¸ÀÌÆ²_º¸½º¸Ó½¬¸¾", "images/bossUi/Boss_mushmam.bmp", WINSIZEX, WINSIZEY, true);

	IMAGE->addImage("º¸½ºhp_front", "images/bossUi/hp_front.bmp", 482, 22);
	IMAGE->addImage("º¸½ºhp_back", "images/bossUi/hp_back.bmp", 482, 22);
	IMAGE->addImage("º¸½ºhp_ÇÁ·¹ÀÓ", "images/bossUi/hpframe.bmp", 506, 32, true);
}

stage1_Boss::~stage1_Boss()
{
}

HRESULT stage1_Boss::init()
{
	//ÇÁ·Î±×·¡½º¹Ùinit
	hpbar = new progressBar;
	hpbar->init("images/bossUi/hp_front.bmp", "images/bossUi/hp_back.bmp", WINSIZEX / 2 - IMAGE->findImage("º¸½ºhp_front")->getWidth() / 2,
		50, 482, 22, true);
	//ÀÌ¸§ ¾ËÆÄ°ª
	alpha = 255;
	//ÇÇ¹þÃ¼ÀÎÁö¸¦À§ÇÑÄ«¿îÆ®
	changePivot = false;
	count = 0;
	shaketime = 0;
	isShake = false;
	//Ä«¸Þ¶óÇÇ¹þ
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1104, 960, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	//º¸½º¼ÒÈ¯ 1~3±îÁö.
	if (isClear == false)
	{
		summonBoss(stage);
		stage++;
	}
	//º¸½ºÃÊ±âhp¼³Á¤
	if (stage == 2) {
		totalhp = mm->getBoss_Slime()->getHp();
	}
	else if (stage == 3) {
		totalhp = mm->getBoss_Flime()->getHp();
	}
	else if (stage == 4) {
		totalhp = mm->getBoss_Mushmam()->getHp();
	}
	return S_OK;
}

void stage1_Boss::release()
{
	SAFE_DELETE(hpbar);
}

void stage1_Boss::update()
{
	//hp¹Ù¼³Á¤
	if (stage == 2) {
		currenthp = mm->getBoss_Slime()->getHp();
	}
	else if (stage == 3) {
		currenthp = mm->getBoss_Flime()->getHp();
	}
	else if (stage == 4) {
		currenthp = mm->getBoss_Mushmam()->getHp();
	}
	hpbar->setGauge(currenthp, totalhp);
	hpbar->update();
	//¾Ö´Ï¸ÞÀÌ¼ÇÄ«¿îÆ®
	aniCount++;
	//ÇÇ¹þÁ¶Á¤ º¸½º ´ë±â bool
	if (!isClear) {
		count++;
		if (count == 100) {
			PLAYER->playerStop();
			CAMERA->ChangePivot(552, 480 - 50, 2);		//º¸½ºÂÊÀ¸·Î Ä«¸Þ¶óÀÌµ¿
			changePivot = true;
		}
		if (!isShake && changePivot && CAMERA->getCMState() == CAMERASTATE::FOLLOWPIVOT)
		{
			CAMERA->movePivot(552, 480 - 50);			//Àá½Ã º¸½º°¡ Ä«¸Þ¶óÁß½É. Èçµé±â.
			CAMERA->setShake(10, 200, 15);
			isShake = true;
			changePivot = false;
		}
		if (isShake) {
			shaketime++;
			if (shaketime > 200) {
				isShake = false;						//150Ä«¿îÆ®µ¿¾È Èçµé±â
				PLAYER->playerStop();
			}
		}
	}
	if (!isShake && !changePivot) {	//Æ¯Á¤Á¶°ÇÀÌ ¾Æ´Ò¶§´Â ¹«Á¶°Ç ÇÃ·¹ÀÌ¾î°¡ Ä«¸Þ¶óÀÇ Áß½É.
		CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	}
	//º¸½ºµéÁ¤ÁöÇ®±â
	if (count == 450) {
		if (stage == 2)
			mm->getBoss_Slime()->setStop(false);
		if (stage == 3)
			mm->getBoss_Flime()->setStop(false);
		if (stage == 4)
			mm->getBoss_Mushmam()->setStop(false);
	}
	//Æ÷Å»
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	//Ä«¸Þ¶ó¾÷µ¥ÀÌÆ®
	//CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void stage1_Boss::render()
{
	//¸ÊÀÌ¹ÌÁö
	ZORDER->ZorderRender(IMAGE->findImage("º¸½º¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("º¸½º¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("º¸½º¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 390, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 450, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 1020, 390, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 450, 810, _portal);
	}
<<<<<<< HEAD
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
=======

	//hpÇÁ·¹ÀÓ & hp¹Ù
	if (count > 200 && currenthp != 0) {
		ZORDER->UIRender(IMAGE->findImage("º¸½ºhp_ÇÁ·¹ÀÓ"), ZUIFIRTH, 0, WINSIZEX / 2 - IMAGE->findImage("º¸½ºhp_ÇÁ·¹ÀÓ")->getWidth() / 2,
			50 - 5);
		hpbar->render();
	}

	//º¸½ºµîÀå¾À Ãâ·Â
	if (!isClear && count > 50 && count < 500) {
		if (count > 400) {
			alpha -= 2;
		}
		if (stage == 2) {
			ZORDER->UIAlphaRender(IMAGE->findImage("Å¸ÀÌÆ²_º¸½º½½¶óÀÓ"), ZUIFIRTH, 150, 0, 0, alpha);
		}
		else if (stage == 3) {
			ZORDER->UIAlphaRender(IMAGE->findImage("Å¸ÀÌÆ²_º¸½ºÇÃ¶óÀÓ"), ZUIFIRTH, 150, 0, 0, alpha);
		}
		else if (stage == 4) {
			ZORDER->UIAlphaRender(IMAGE->findImage("Å¸ÀÌÆ²_º¸½º¸Ó½¬¸¾"), ZUIFIRTH, 150, 0, 0, alpha);
		}
	}
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

nextStage::nextStage()
{
	IMAGE->addImage("´ÙÀ½Ãþ¹è°æ", "images/map/nextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("´ÙÀ½ÃþÇÈ¼¿", "images/map/!mnextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("´ÙÀ½Ãþ°¡¸²", "images/map/ParnextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("¸¶¹ýÁø", "images/map/portal.bmp", 162, 174, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	goNextStage[0].Door = RectMake(423, 279, 162, 174); //bottom
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));

}

nextStage::~nextStage()
{
}

HRESULT nextStage::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void nextStage::release()
{
}

void nextStage::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void nextStage::render()
{
	ZORDER->ZorderAlphaRender(IMAGE->findImage("¸¶¹ýÁø"), ZEFFECT1, WINSIZEY, 423, 279, 150);
	ZORDER->ZorderRender(IMAGE->findImage("´ÙÀ½Ãþ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("´ÙÀ½Ãþ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("´ÙÀ½ÃþÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	if (_isDebug)ZORDER->ZorderRectangle(goNextStage[0].Door, ZEFFECT1);


}

fountainMap::fountainMap()
{

	IMAGE->addImage("ºÐ¼ö¹æ¹è°æ", "images/map/fountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("ºÐ¼ö¹æÇÈ¼¿", "images/map/!mfountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("ºÐ¼ö¹æ°¡¸²", "images/map/ParfountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));

	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom

	monpos[0] = { 470,263 };
	monpos[1] = { 473,573 };
	monpos[2] = { 681,381 };
	monpos[3] = { 330,440 };
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_fountain = new fountain;
	_fountain->add(504, 362);
}

fountainMap::~fountainMap()
{
}

HRESULT fountainMap::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void fountainMap::release()
{
	SAFE_DELETE(_fountain);
}

void fountainMap::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	_fountain->update(bm);
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void fountainMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("ºÐ¼ö¹æ¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("ºÐ¼ö¹æ°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("ºÐ¼ö¹æÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (isleftRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, -90, 300, _portal);
	}
	if (istopRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 410, -120, _portal);
	}
	if (isrightRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 900, 290, _portal);
	}
	if (isbotRoom)
	{
		if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 400, 400, 530, _portal);
	}
	_fountain->render();
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();
}

before_Boss::before_Boss()
{
	IMAGE->addImage("º¸½ºÀü¹è°æ", "images/map/ground102.bmp", 1008, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("º¸½ºÀüÇÈ¼¿", "images/map/!m102.bmp", 1008, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("º¸½ºÀü°¡¸²", "images/map/Par102.bmp", 1008, 960, true, RGB(255, 0, 255));
	_portalImage = IMAGE->addFrameImage("Æ÷Å»", "images/map/portal2.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	_door[1].Door = RectMake(504,169,140,25); //top
}

before_Boss::~before_Boss()
{
}

HRESULT before_Boss::init()
{

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 960, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	return S_OK;
}

void before_Boss::release()
{
}

void before_Boss::update()
{
	aniCount++;
	if (aniCount == 1)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 5, false, false);
	}
	else if (aniCount == 53)
	{
		_portal = ANIMATION->addNoneKeyAnimation("Æ÷Å»", 6, 12, 7, true, true);
	}
	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
}

void before_Boss::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("º¸½ºÀü¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("º¸½ºÀü°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("º¸½ºÀüÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
		ZORDER->ZorderAniRender(_portalImage, ZEFFECT1, 504, 169, -120, _portal);
	
}

last_Boss::last_Boss()
{
	IMAGE->addImage("¶óº¸¹è°æ", "images/map/Ground55.bmp", 1344, 1200, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("¶óº¸ÇÈ¼¿", "images/map/!m55.bmp", 1344, 1200, true, RGB(255, 0, 255));
	IMAGE->addImage("¶óº¸°¡¸²", "images/map/Par55.bmp", 1344, 1200, true, RGB(255, 0, 255));
	_door[3].Door = RectMake(636, 1100, 160, 25); //bottom

	IMAGE->addImage("Å¸ÀÌÆ²_ÀÌ±×µå¶ó½Ç", "images/bossUi/Boss_Iggdrasil.bmp", WINSIZEX, WINSIZEY, true);
	IMAGE->addImage("º¸½ºhp_front", "images/bossUi/hp_front.bmp", 482, 22);
	IMAGE->addImage("º¸½ºhp_back", "images/bossUi/hp_back.bmp", 482, 22);
	IMAGE->addImage("º¸½ºhp_ÇÁ·¹ÀÓ", "images/bossUi/hpframe.bmp", 506, 32, true);
}

last_Boss::~last_Boss()
{
}

HRESULT last_Boss::init()
{
	//ÇÁ·Î±×·¡½º¹Ùinit
	hpbar = new progressBar;
	hpbar->init("images/bossUi/hp_front.bmp", "images/bossUi/hp_back.bmp", WINSIZEX / 2 - IMAGE->findImage("º¸½ºhp_front")->getWidth() / 2,
		50, 482, 22, true);
	//ÀÌ¸§ ¾ËÆÄ°ª
	alpha = 255;
	//ÇÇ¹þÃ¼ÀÎÁö¸¦À§ÇÑÄ«¿îÆ®
	changePivot = false;
	count = 0;
	shaketime = 0;
	isShake = false;
	if (!(getClear()))
	{
		summonBoss(4);
	}
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1344, 1200, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	
	//º¸½ºÃÊ±âhp¼³Á¤
	totalhp = mm->getYggdrasil()->getHp();
	//ÀÌ¹ÌÁöÄ«¿îÆ®
	imgCount = 0;
	return S_OK;

}

void last_Boss::release()
{
}

void last_Boss::update()
{
<<<<<<< HEAD
	_gold_coin->update(); _silver_coin->update(); _bronze_coin->update();
=======
	//hp¹Ù¼³Á¤
	currenthp = mm->getYggdrasil()->getHp();
	hpbar->setGauge(currenthp, totalhp);
	hpbar->update();

	//ÇÇ¹þÁ¶Á¤ º¸½º ´ë±â bool
	if (!isClear) {
		count++;
		if (!isWait && count == 100) {
			PLAYER->playerStop();
			CAMERA->ChangePivot(650, 349 + 110 + 15, 2);		//º¸½ºÂÊÀ¸·Î Ä«¸Þ¶óÀÌµ¿
			changePivot = true;
		}
		if (!isWait && !isShake && changePivot && CAMERA->getCMState() == CAMERASTATE::FOLLOWPIVOT)
		{
			CAMERA->movePivot(650, 349 + 110);			//Àá½Ã º¸½º°¡ Ä«¸Þ¶óÁß½É.
			mm->getYggdrasil()->setStop(false);			//º¸½º ½ºÅ¾ÇØÁ¦.
			isWait = true;
			count = 0;
		}
		if (isWait) {
			if (count > 300) {
				CAMERA->setShake(10, 200, 10);
				isShake = true;
				changePivot = false;
				isWait = false;
			}
		}
		if (isShake) {
			shaketime++;
			if (shaketime > 200) {
				isShake = false;						//150Ä«¿îÆ®µ¿¾È Èçµé±â
				PLAYER->playerStop();
			}
		}
	}
	if (!isWait && !isShake && !changePivot) {	//Æ¯Á¤Á¶°ÇÀÌ ¾Æ´Ò¶§´Â ¹«Á¶°Ç ÇÃ·¹ÀÌ¾î°¡ Ä«¸Þ¶óÀÇ Áß½É.
		float bossX = 650;
		float bossY = 349 + 110;
		POINT relativePivot;
		relativePivot.x = (bossX + PLAYER->getPlayerAddress().x * 2) / 3;
		relativePivot.y = (bossY + PLAYER->getPlayerAddress().y * 2) / 3;

		CAMERA->movePivot(relativePivot.x, relativePivot.y);
	}
	////º¸½ºµéÁ¤ÁöÇ®±â
	//if (count == 450) {
	//	mm->getYggdrasil()->setStop(false);
	//}
	//Ä«¸Þ¶ó¾÷µ¥ÀÌÆ®
	//CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();
>>>>>>> ì˜ˆê· ìƒˆìž‘ì—…
}

void last_Boss::render()
{
	imgCount++;
	ZORDER->ZorderRender(IMAGE->findImage("¶óº¸¹è°æ"), ZFLOORMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("¶óº¸ÇÈ¼¿"), ZCOLMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("¶óº¸°¡¸²"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	_gold_coin->render(); _silver_coin->render(); _bronze_coin->render();

	//hpÇÁ·¹ÀÓ & hp¹Ù
	if (imgCount > 200 && currenthp != 0) {
		ZORDER->UIRender(IMAGE->findImage("º¸½ºhp_ÇÁ·¹ÀÓ"), ZUIFIRTH, 0, WINSIZEX / 2 - IMAGE->findImage("º¸½ºhp_ÇÁ·¹ÀÓ")->getWidth() / 2,
			50 - 5);
		hpbar->render();
	}

	//º¸½ºµîÀå¾À Ãâ·Â
	if (!isClear && imgCount > 200 && imgCount < 500) {
		if (imgCount > 400) {
			alpha -= 2;
		}
		ZORDER->UIAlphaRender(IMAGE->findImage("Å¸ÀÌÆ²_ÀÌ±×µå¶ó½Ç"), ZUIFIRTH, 150, 0, 0, alpha);
	}
}
