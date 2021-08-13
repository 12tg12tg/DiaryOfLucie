#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
}

mainDOL::~mainDOL()
{
}

HRESULT mainDOL::init()
{
	_bm = new bulletManager;
	_cm = new collisionManager;
	_mm = new monsterManager;
	_mapm = new mapManager;

	PLAYER->init();
	_bm->init();
	_cm->init();
	_mm->init();
	_mapm->init();

	_mm->setBulletManagerMemoryLink(_bm);	//���Ϳ��� ����ũ

	_cm->setBulletManagerMemoryLink(_bm);	//�浹���� �Ҹ���ũ
	_cm->setMonsterManagerMemoryLink(_mm);	//�浹���� ���͸�ũ
	_cm->setmapManagerMemoryLink(_mapm);
	PLAYER->setBulletManagerMemoryLink(_bm);
	




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

	PLAYER->update();
	EFFECT->update();




}

void mainDOL::render()
{
	_mapm->render();
	_bm->render();
	_mm->render();
	_cm->render();

	PLAYER->render(getMemDC());
	EFFECT->render();
	ZORDER->ZorderTotalRender(getMemDC());



}