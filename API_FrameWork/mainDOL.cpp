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

	_mm->setBulletManagerMemoryLink(_bm);	//���Ϳ��� ����ũ

	_cm->setBulletManagerMemoryLink(_bm);	//�浹���� �Ҹ���ũ
	_cm->setMonsterManagerMemoryLink(_mm);	//�浹���� ���͸�ũ
	_cm->setmapManagerMemoryLink(_mapm);	//�浹���� �ʸ�ũ
	_mapm->setMonsterManagerMemoryLink(_mm);//�ʿ��� ���͸�ũ
	_mapm->setBulletManagerMemoryLink(_bm);//�ʿ��� �Ҹ���ũ
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
	_mapm->render();
	_bm->render();
	_mm->render();
	_cm->render();

	BUTTON->render();
	PLAYER->render(getMemDC());
	PLAYERDATA->render(getMemDC());

	EFFECT->render();
	ZORDER->ZorderTotalRender(getMemDC());

}