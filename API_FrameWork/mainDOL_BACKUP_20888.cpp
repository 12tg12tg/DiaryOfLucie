#include "framework.h"
#include "mainDOL.h"

mainDOL::mainDOL()
{
	IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("DOL_cursor", "images/UI/cursor.bmp", 32, 32, true);
	ShowCursor(false);					//Ŀ������
	SetBkMode(getMemDC(), TRANSPARENT);	//���ڹ�� ����

}

mainDOL::~mainDOL(){}

HRESULT mainDOL::init()
{
	gameInit();
	_DOLtitle = dynamic_cast<DOL_Title*>(SCENE->addScene("Ÿ��Ʋ", new DOL_Title, false));
	_loading = dynamic_cast<loading*>(SCENE->addScene("�ε�", new loading(_mapm), false));
	SCENE->changeScene("Ÿ��Ʋ");
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
	//��ȯ���� ���� DOLSTATE����
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


	//���º���
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

		_bm->update();
		_mm->update();
		_cm->update();
		_mapm->update();
		BUTTON->update();
		INVENTORY->update();
		_sk->update();
		PLAYER->update();
		PLAYERDATA->update();
		EFFECT->update();
		INVENTORY->update();
		ITEM->update();
		SOUND->update();
		CAMERA->FadeUpdate();
	}
		break;
	case mainDOL::DOLSTATE::GETSKILL:
		_sk->update();
		break;
	default:
		break;
	}
	SCENE->update();			//INMAP�����϶��� mapManager���� ��������Ʈ��.

<<<<<<< HEAD
=======
	if (INPUT->isOnceKeyDown(VK_F5)) {
		_mapm->clearMonster();
	}
>>>>>>> origin/예균새작업
}

void mainDOL::render()
{
	//���º��� ZORDER�� ���� �ν��Ͻ� ����.
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
		//�Ʒ��� �� Zorder�� ����
		_bm->render();
		_mm->render();
		_cm->render();
		_mapm->render();
		_sk->render();
		PLAYER->render(getDolDC());
		EFFECT->render();
		ITEM->render();
		//ȭ�� ������ UI ���⼭���� ZORDER�� ���.
		PLAYERDATA->render(getMemDC());
		BUTTON->render(getMemDC());
		INVENTORY->render(getMemDC());

		//------------------------------------�������------------------------------------------
		//1. Zorder �ϰ� "DolDC"�����
		ZORDER->ZorderTotalRender(getDolDC());
		//2. DolDC�� ī�޶������Ͽ� SCORPDC�� ���
		_DOLBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
			RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
		//3. SCORPDC�� Ȯ���Ͽ� memDC�� ���.
		IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);
		//--------------------------------------------------------------------------------------
	}
		break;
	default:
		break;
	}

	//�� ���� �������
	//4. ZORDER UI ���
	ZORDER->ZorderUITotalRender(getMemDC());
	//5. ���̵� ȿ�� ��� - UI���� ���������.
	CAMERA->FadeRender(getMemDC());
	//6. Ŀ�� - ���콺�� ���Ĺ�.
	IMAGE->findImage("DOL_cursor")->render(getMemDC(), m_ptMouse.x, m_ptMouse.y);

	//-----------------------------------------�׽�Ʈ-----------------------------------------
	//TCHAR str[128];
	//wsprintf(str, "ī�޶� ����Ʈ/ž : %d, %d", CAMERA->getRect().left, CAMERA->getRect().top);
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
	_mm->setBulletManagerMemoryLink(_bm);		//���Ϳ��� ������ũ
	_cm->setBulletManagerMemoryLink(_bm);		//�浹���� �Ҹ���ũ
	_cm->setMonsterManagerMemoryLink(_mm);		//�浹���� ���͸�ũ
	_cm->setmapManagerMemoryLink(_mapm);		//�浹���� �ʸ�ũ
	_mapm->setMonsterManagerMemoryLink(_mm);	//�ʿ��� ���͸�ũ
	_mapm->setBulletManagerMemoryLink(_bm);		//�ʿ��� �Ҹ���ũ
	_mapm->setSkillMemoryLink(_sk);				//�ʿ��� ��ų
	PLAYER->setBulletManagerMemoryLink(_bm);
	_sk->setBulletManagerMemoryLink(_bm);
	initForsound();
	//_mapm->init();		//�ε����� init�ǵ��� ����.


	//CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
	//	1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	//CAMERA->FadeStart();
}

void mainDOL::initForsound()
{
	SOUND->addSound("�������", "sound/stage_forest.ogg", true, true);
	SOUND->addSound("��������", "sound/boss_forest.ogg", true, true);
	SOUND->addSound("��������������", "sound/lastboss.ogg", true, true);
	
	SOUND->addSound("�޸��¼Ҹ�", "sound/footstep_grass_run_01.ogg", false, false);
	SOUND->addSound("�ȴ¼Ҹ�", "sound/footstep_grass_walk_04.ogg", false, false);

	SOUND->addSound("�����ӼҸ�", "sound/slime1.ogg", false, false);
	SOUND->addSound("�������״¼Ҹ�", "sound/slime_dead.ogg", false, false);
	SOUND->addSound("���״¼Ҹ�", "sound/snaby_dead.ogg", false, false);
	SOUND->addSound("��Ҹ�", "sound/snaby1.ogg", false, false);
	SOUND->addSound("�����״¼Ҹ�", "sound/mushman_dead.ogg", false, false);
	SOUND->addSound("�����״¼Ҹ�", "sound/fairy_dead.ogg", false, false);
	SOUND->addSound("���״¼Ҹ�", "sound/se_dead1.ogg", false, false);
	SOUND->addSound("�����Ҹ�", "sound/mushman1.ogg", false, false);

	SOUND->addSound("Į�Ҹ�", "sound/se_sword1.ogg", false, false);
	SOUND->addSound("Ȱ�Ҹ�", "sound/bow1.ogg", false, false);
	SOUND->addSound("���ݼҸ�", "sound/atk602.ogg", false, false);

	SOUND->addSound("����", "sound/Coin.ogg", false, false);
	SOUND->play("�������",0.05);
}