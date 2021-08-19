#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
	IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("DOL_cursor", "images/UI/cursor.bmp", 32, 32, true);
	ShowCursor(false);					//Ä¿¼­¼û±è
	SetBkMode(getMemDC(), TRANSPARENT);	//±ÛÀÚ¹è°æ Åõ¸í
}

mainDOL::~mainDOL(){}

HRESULT mainDOL::init()
{
	gameInit();
	_DOLtitle = dynamic_cast<DOL_Title*>(SCENE->addScene("Å¸ÀÌÆ²", new DOL_Title, false));
	_loading = dynamic_cast<loading*>(SCENE->addScene("·Îµù", new loading(_mapm), false));
	SCENE->changeScene("Å¸ÀÌÆ²");
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
	//¹ÝÈ¯Çü¿¡ µû¸¥ DOLSTATEº¯°æ
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


	//»óÅÂº°·Î
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
<<<<<<< HEAD
		INVENTORY->update();
=======

>>>>>>> ìƒˆë¡œíƒœì–´ë‚˜ìžë¸Œëžœì¹˜
		ITEM->update();
		INVENTORY->update();
		CAMERA->FadeUpdate();
	}
		break;
	case mainDOL::DOLSTATE::GETSKILL:
		_sk->update();
		break;
	default:
		break;
	}
	SCENE->update();			//INMAP»óÅÂÀÏ¶§´Â mapManager¿¡¼­ ¾À¾÷µ¥ÀÌÆ®Áß.


}

void mainDOL::render()
{
	//»óÅÂº°·Î ZORDER¿¡ ´ãÀ» ÀÎ½ºÅÏ½º °áÁ¤.
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
		//¾Æ·¡·Î Âß Zorder¿¡ ÀúÀå
		_bm->render();
		_mm->render();
		_cm->render();
		_mapm->render();
		_sk->render();
		PLAYER->render(getDolDC());
		EFFECT->render();
		ITEM->render();
		//È­¸é °íÁ¤Çü UI ¿©±â¼­ºÎÅÍ ZORDER¿¡ ´ã±â.
		PLAYERDATA->render(getMemDC());
		BUTTON->render(getMemDC());
		INVENTORY->render(getMemDC());

		//------------------------------------½ÇÁ¦Ãâ·Â------------------------------------------
		//1. Zorder ÀÏ°ý "DolDC"¿¡Ãâ·Â
		ZORDER->ZorderTotalRender(getDolDC());
		//2. DolDC¸¦ Ä«¸Þ¶óÀû¿ëÇÏ¿© SCORPDC¿¡ Ãâ·Â
		_DOLBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
			RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
		//3. SCORPDC¸¦ È®´ëÇÏ¿© memDC¿¡ Ãâ·Â.
		IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);
		//--------------------------------------------------------------------------------------
	}
		break;
	default:
		break;
	}

	//Àü »óÅÂ °øÅëÃâ·Â
	//4. ZORDER UI Ãâ·Â
	ZORDER->ZorderUITotalRender(getMemDC());
	//5. ÆäÀÌµå È¿°ú Ãâ·Â - UI±îÁö µ¤¾î¹ö¸®±â.
	CAMERA->FadeRender(getMemDC());
	//6. Ä¿¼­ - ¸¶¿ì½º´Â ÃÖÈÄ¹Ý.
	IMAGE->findImage("DOL_cursor")->render(getMemDC(), m_ptMouse.x, m_ptMouse.y);

	//-----------------------------------------Å×½ºÆ®-----------------------------------------
	//TCHAR str[128];
	//wsprintf(str, "Ä«¸Þ¶ó ·¹ÇÁÆ®/Å¾ : %d, %d", CAMERA->getRect().left, CAMERA->getRect().top);
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
	ITEM->init();
	INVENTORY->init();

	_bm->init();
	_cm->init();
	_mm->init();
	_sk->init();
	_mm->setBulletManagerMemoryLink(_bm);		//¸ó½ºÅÍ¿¡¼­ ºí¸´¸µÅ©
	_cm->setBulletManagerMemoryLink(_bm);		//Ãæµ¹¿¡¼­ ºÒ¸´¸µÅ©
	_cm->setMonsterManagerMemoryLink(_mm);		//Ãæµ¹¿¡¼­ ¸ó½ºÅÍ¸µÅ©
	_cm->setmapManagerMemoryLink(_mapm);		//Ãæµ¹¿¡¼­ ¸Ê¸µÅ©
	_mapm->setMonsterManagerMemoryLink(_mm);	//¸Ê¿¡¼­ ¸ó½ºÅÍ¸µÅ©
	_mapm->setBulletManagerMemoryLink(_bm);		//¸Ê¿¡¼­ ºÒ¸´¸µÅ©
	PLAYER->setBulletManagerMemoryLink(_bm);
	_sk->setBulletManagerMemoryLink(_bm);

	//_mapm->init();		//·Îµù¿¡¼­ initµÇµµ·Ï ¸·À½.


	//CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
	//	1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	//CAMERA->FadeStart();
}
