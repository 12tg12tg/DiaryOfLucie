#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
	IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("DOL_cursor", "images/UI/cursor.bmp", 32, 32, true);
	ShowCursor(false);					//커서숨김
	SetBkMode(getMemDC(), TRANSPARENT);	//글자배경 투명
}

mainDOL::~mainDOL(){}

HRESULT mainDOL::init()
{
	gameInit();
	_DOLtitle = dynamic_cast<DOL_Title*>(SCENE->addScene("타이틀", new DOL_Title, false));
	_loading = dynamic_cast<loading*>(SCENE->addScene("로딩", new loading(_mapm), false));
	SCENE->changeScene("타이틀");
	_state = DOLSTATE::LOADING;

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
	//반환형에 따른 DOLSTATE변경
	if (_state == DOLSTATE::LOADING && _loading->getIsLodingDone()) {
		_state = DOLSTATE::INMAP;
	}
	if (_state == DOLSTATE::INMAP && _mapm->getGoNextStage())
	{
		_state = DOLSTATE::LOADING;
	}
	if (_state != DOLSTATE::LOADING) {
		if (_sk->getIsSkillInfo()) {
			_state = DOLSTATE::GETSKILL;
		}
		else{
			_state = DOLSTATE::INMAP;
		}
	}


	//상태별로
	switch (_state)
	{
	case mainDOL::DOLSTATE::LOADING:
		SCENE->update();
		EFFECT->update();
		SCENE->update();
		BUTTON->update();
		break;
	case mainDOL::DOLSTATE::INMAP:
	{
		if (INPUT->isOnceKeyDown('K')) _sk->addSkill();

		_bm->update();
		_mm->update();
		_cm->update();
		_mapm->update();
		BUTTON->update();
		_sk->update();
		PLAYER->update();
		PLAYERDATA->update();
		EFFECT->update();
		CAMERA->FadeUpdate();
	}
		break;
	case mainDOL::DOLSTATE::GETSKILL:
		_sk->update();
		break;
	default:
		break;
	}
	SCENE->update();			//INMAP상태일때는 mapManager에서 씬업데이트중.


}

void mainDOL::render()
{
	//상태별로 ZORDER에 담을 인스턴스 결정.
	switch (_state)
	{
	case mainDOL::DOLSTATE::LOADING:
	{
		SCENE->render();
		BUTTON->render(getMemDC());
	}
		break;
	case mainDOL::DOLSTATE::INMAP:
	case mainDOL::DOLSTATE::GETSKILL:
	{
		//아래로 쭉 Zorder에 저장
		_bm->render();
		_mm->render();
		_cm->render();
		_mapm->render();
		_sk->render();
		PLAYER->render(getDolDC());
		EFFECT->render();

		//화면 고정형 UI 여기서부터 ZORDER에 담기.
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
	}
		break;
	default:
		break;
	}

	//전 상태 공통출력
	//4. ZORDER UI 출력
	ZORDER->ZorderUITotalRender(getMemDC());
	//5. 페이드 효과 출력 - UI까지 덮어버리기.
	CAMERA->FadeRender(getMemDC());
	//6. 커서 - 마우스는 최후반.
	IMAGE->findImage("DOL_cursor")->render(getMemDC(), m_ptMouse.x, m_ptMouse.y);

	//-----------------------------------------테스트-----------------------------------------
	//TCHAR str[128];
	//wsprintf(str, "카메라 레프트/탑 : %d, %d", CAMERA->getRect().left, CAMERA->getRect().top);
	//TextOut(getMemDC(),0, 0, str, lstrlen(str));
}

void mainDOL::gameInit()
{
	_bm = new bulletManager;
	_cm = new collisionManager;
	_mm = new monsterManager;
	_mapm = new mapManager;
	_sk = new Cskill;
	PLAYER->init();
	PLAYERDATA->init();
	_bm->init();
	_cm->init();
	_mm->init();
	_sk->init();
	_mm->setBulletManagerMemoryLink(_bm);		//몬스터에서 블릿링크
	_cm->setBulletManagerMemoryLink(_bm);		//충돌에서 불릿링크
	_cm->setMonsterManagerMemoryLink(_mm);		//충돌에서 몬스터링크
	_cm->setmapManagerMemoryLink(_mapm);		//충돌에서 맵링크
	_mapm->setMonsterManagerMemoryLink(_mm);	//맵에서 몬스터링크
	_mapm->setBulletManagerMemoryLink(_bm);		//맵에서 불릿링크
	PLAYER->setBulletManagerMemoryLink(_bm);
	_sk->setBulletManagerMemoryLink(_bm);

	//_mapm->init();		//로딩에서 init되도록 막음.


	//CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
	//	1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	//CAMERA->FadeStart();
}
