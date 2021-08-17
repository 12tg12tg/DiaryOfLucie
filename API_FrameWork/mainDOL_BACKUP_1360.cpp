#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
	IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("DOL_cursor", "images/UI/cursor.bmp", 32, 32, true);
	ShowCursor(false);					//커서숨김
	SetBkMode(getMemDC(), TRANSPARENT);	//배경 투명
}

mainDOL::~mainDOL(){}

HRESULT mainDOL::init()
{
	gameInit();
	_DOLtitle = dynamic_cast<DOL_Title*>(SCENE->addScene("타이틀", new DOL_Title));
	_loading = dynamic_cast<loading*>(SCENE->addScene("로딩", new loading(_mapm)));
	SCENE->changeScene("타이틀");





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
	//로딩끝났는지확인
	if (_loading->getIsLodingDone()) {
		canUpdate = true;
	}
	//타이틀과 게임시작화면 & 로딩
	if (!canUpdate) {
		SCENE->update();
		EFFECT->update();
		SCENE->update();
		BUTTON->update();
	}
	//로딩준비가끝났을때부터 업데이트가능.
	else {
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
	}
	SCENE->update();
}

void mainDOL::render()
{
	if (!canUpdate) {
		//씬
		SCENE->render();
	}
	else {
		//아래로 쭉 Zorder에 저장
		_bm->render();
		_mm->render();
		_cm->render();
		_mapm->render();
		PLAYER->render(getDolDC());
		EFFECT->render();

		//화면 고정형 UI 여기서부터 출력.
		PLAYERDATA->render(getMemDC());
		BUTTON->render(getMemDC());

		//------------------------------------실제출력------------------------------------------
		//1. Zorder 일괄 "DolDC"에출력
		ZORDER->ZorderTotalRender(getDolDC());
		//2. DolDC를 카메라적용하여 SCORPDC에 출력
		_DOLBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
			RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
		//3. SCORPDC를 확대하여 memDC에 출력.
		IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);
		//--------------------------------------------------------------------------------------

		//테스트
		//TCHAR str[128];
		//wsprintf(str, "마우스좌표 : %d, %d", (int)CAMMOUSEX, (int)CAMMOUSEY);
		//TextOut(getMemDC(), 0, 60, str, lstrlen(str));
		//wsprintf(str, "플레이어좌표 : %d, %d", (int)PLAYER->getPlayerAddress().x, (int)PLAYER->getPlayerAddress().y);
		//TextOut(getMemDC(), 0, 80, str, lstrlen(str));
	}

	//실제 UI 출력
	ZORDER->ZorderUITotalRender(getMemDC());
	//페이드 효과 출력 - UI까지 덮어버리기.
	CAMERA->FadeRender(getMemDC());
	//커서 ZORDER에 담기 - 마우스는 최후반.
	IMAGE->findImage("DOL_cursor")->render(getMemDC(), m_ptMouse.x, m_ptMouse.y);
}

void mainDOL::gameInit()
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

	//_mapm->init();		//로딩에서 init되도록 막음.


<<<<<<< HEAD
=======
	_bm->render();
	_mm->render();
	_cm->render();
>>>>>>> mapbranch

	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	CAMERA->FadeStart();


<<<<<<< HEAD
}
=======
	PLAYERDATA->render(getMemDC());
	_mapm->render();
}
>>>>>>> mapbranch
