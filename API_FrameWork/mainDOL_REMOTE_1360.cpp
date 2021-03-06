#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL(){}
mainDOL::~mainDOL(){}

HRESULT mainDOL::init()
{
	_bm = new bulletManager;
	_cm = new collisionManager;
	_mm = new monsterManager;
	_mapm = new mapManager;

	PLAYER->init();
	PLAYERDATA->init();

	_bm->init();
	_cm->init();
	_mm->init();

	_mm->setBulletManagerMemoryLink(_bm);	//몬스터에서 블릿링크

	_cm->setBulletManagerMemoryLink(_bm);	//충돌에서 불릿링크
	_cm->setMonsterManagerMemoryLink(_mm);	//충돌에서 몬스터링크
	_cm->setmapManagerMemoryLink(_mapm);	//충돌에서 맵링크
	_mapm->setMonsterManagerMemoryLink(_mm);//맵에서 몬스터링크
	_mapm->setBulletManagerMemoryLink(_bm);//맵에서 불릿링크
	PLAYER->setBulletManagerMemoryLink(_bm);
	
	_mapm->init();




	return S_OK;
}

void mainDOL::release()
{
	_bm->release();
	_cm->release();
	_mm->release();
	_mapm->release();




	SAFE_DELETE(_bm);
	SAFE_DELETE(_cm);
	SAFE_DELETE(_mm);
	SAFE_DELETE(_mapm);




}

void mainDOL::update()
{
	_bm->update();
	_mm->update();
	_cm->update();
	_mapm->update();

	BUTTON->update();
	PLAYER->update();
	PLAYERDATA->update();
	EFFECT->update();




}

void mainDOL::render()
{

	_bm->render();
	_mm->render();
	_cm->render();

	BUTTON->render();
	PLAYER->render(getMemDC());

	EFFECT->render();
	ZORDER->ZorderTotalRender(getMemDC());

	PLAYERDATA->render(getMemDC());
	_mapm->render();
}