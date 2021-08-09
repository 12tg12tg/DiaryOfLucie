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

	PLAYER->init();
	_bm->init();
	_cm->init();
	_mm->init();

	_mm->setBulletManagerMemoryLink(_bm);	//���Ϳ��� ����ũ
<<<<<<< HEAD
	_cm->setBulletManagerMemoryLink(_bm);	//�浹���� �Ҹ���ũ
	_cm->setMonsterManagerMemoryLink(_mm);	//�浹���� ���͸�ũ
=======
	PLAYER->setBulletManagerMemoryLink(_bm);
>>>>>>> 고성민의브런치(플레이어구현)





	return S_OK;
}

void mainDOL::release()
{
	_bm->release();
	_cm->release();
	_mm->release();





	SAFE_DELETE(_bm);
	SAFE_DELETE(_cm);
	SAFE_DELETE(_mm);




}

void mainDOL::update()
{
	_bm->update();
	_cm->update();
	_mm->update();

	PLAYER->update();





}

void mainDOL::render()
{
	_bm->render();
	_cm->render();
	_mm->render();

	PLAYER->render(getMemDC());





}