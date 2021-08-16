#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
	IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
}

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

	_mm->setBulletManagerMemoryLink(_bm);		//���Ϳ��� ����ũ

	_cm->setBulletManagerMemoryLink(_bm);		//�浹���� �Ҹ���ũ
	_cm->setMonsterManagerMemoryLink(_mm);		//�浹���� ���͸�ũ
	_cm->setmapManagerMemoryLink(_mapm);		//�浹���� �ʸ�ũ
	_mapm->setMonsterManagerMemoryLink(_mm);	//�ʿ��� ���͸�ũ
	_mapm->setBulletManagerMemoryLink(_bm);		//�ʿ��� �Ҹ���ũ
	PLAYER->setBulletManagerMemoryLink(_bm);
	
	_mapm->init();



	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX /2, CAMERASIZEY /2, CAMERASIZEX, CAMERASIZEY);
	CAMERA->FadeInit(80, FADE_IN);
	CAMERA->FadeStart();


	_sp = new shop;
	_sp->add(WINSIZEX/2, WINSIZEY/2);
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


	SAFE_DELETE(_sp);

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
	CAMERA->FadeUpdate();

	CAMERA->movePivot(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	CAMERA->update();


	_sp->update(_bm);
}

void mainDOL::render()
{
	//�Ʒ��� �� Zorder�� ����
	_mapm->render();
	_bm->render();
	_mm->render();
	_cm->render();
	PLAYER->render(getDolDC());
	EFFECT->render();
	
	//Zorder �ϰ� DolDC�����
	ZORDER->ZorderTotalRender(getDolDC());

	//DolDC�� ī�޶������Ͽ� SCORPDC�� ���
	_DOLBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
	

	IMAGE->findImage("SCORPDC")->render(getMemDC());


	//SCORPDC�� Ȯ���Ͽ� memDC�� ���.
	IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);

	//ȭ�� ������ UI ���⼭���� ���.
	PLAYERDATA->render(getMemDC());
	BUTTON->render(getMemDC());

	//���̵� ȿ�� ��� - �˾Ƽ� ����
	CAMERA->FadeRender(getMemDC());

	//�׽�Ʈ
	//TCHAR str[128];
	//wsprintf(str, "���콺��ǥ : %d, %d", (int)CAMMOUSEX, (int)CAMMOUSEY);
	//TextOut(getMemDC(), 0, 60, str, lstrlen(str));
	//wsprintf(str, "�÷��̾���ǥ : %d, %d", (int)PLAYER->getPlayerAddress().x, (int)PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 0, 80, str, lstrlen(str));

	_sp->render();
}