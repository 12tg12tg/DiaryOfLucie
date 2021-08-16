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

	_mm->setBulletManagerMemoryLink(_bm);		//몬스터에서 블릿링크

	_cm->setBulletManagerMemoryLink(_bm);		//충돌에서 불릿링크
	_cm->setMonsterManagerMemoryLink(_mm);		//충돌에서 몬스터링크
	_cm->setmapManagerMemoryLink(_mapm);		//충돌에서 맵링크
	_mapm->setMonsterManagerMemoryLink(_mm);	//맵에서 몬스터링크
	_mapm->setBulletManagerMemoryLink(_bm);		//맵에서 불릿링크
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
	//아래로 쭉 Zorder에 저장
	_mapm->render();
	_bm->render();
	_mm->render();
	_cm->render();
	PLAYER->render(getDolDC());
	EFFECT->render();
	
	//Zorder 일괄 DolDC에출력
	ZORDER->ZorderTotalRender(getDolDC());

	//DolDC를 카메라적용하여 SCORPDC에 출력
	_DOLBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
	

	IMAGE->findImage("SCORPDC")->render(getMemDC());


	//SCORPDC를 확대하여 memDC에 출력.
	IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);

	//화면 고정형 UI 여기서부터 출력.
	PLAYERDATA->render(getMemDC());
	BUTTON->render(getMemDC());

	//페이드 효과 출력 - 알아서 멈춤
	CAMERA->FadeRender(getMemDC());

	//테스트
	//TCHAR str[128];
	//wsprintf(str, "마우스좌표 : %d, %d", (int)CAMMOUSEX, (int)CAMMOUSEY);
	//TextOut(getMemDC(), 0, 60, str, lstrlen(str));
	//wsprintf(str, "플레이어좌표 : %d, %d", (int)PLAYER->getPlayerAddress().x, (int)PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 0, 80, str, lstrlen(str));

	_sp->render();
}