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
	//�ε���������Ȯ��
	if (_loading->getIsLodingDone()) {
		canUpdate = true;
	}
	if (_mapm->getGoNextStage())
	{
		canUpdate = false;
	}
	//Ÿ��Ʋ�� ���ӽ���ȭ�� & �ε�
	if (!canUpdate) {
		SCENE->update();
		EFFECT->update();
		SCENE->update();
		BUTTON->update();
	}
	//�ε��غ񰡳����������� ������Ʈ����.
	else {
		_bm->update();
		_mm->update();
		_cm->update();
		_mapm->update();
		BUTTON->update();
		PLAYER->update();
		PLAYERDATA->update();
		EFFECT->update();

		INVENTORY->update();
		ITEM->update();
		CAMERA->FadeUpdate();
	}
	SCENE->update();
}

void mainDOL::render()
{
	if (!canUpdate) {
		//��
		SCENE->render();
		BUTTON->render(getMemDC());
	}
	else {
		//�Ʒ��� �� Zorder�� ����
		_bm->render();
		_mm->render();
		_cm->render();
		_mapm->render();
		PLAYER->render(getDolDC());
		EFFECT->render();
		ITEM->render();
		//ȭ�� ������ UI ���⼭���� ���.
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

	//���� UI ���
	ZORDER->ZorderUITotalRender(getMemDC());
	//���̵� ȿ�� ��� - UI���� ���������.
	CAMERA->FadeRender(getMemDC());
	//Ŀ�� - ���콺�� ���Ĺ�.
	IMAGE->findImage("DOL_cursor")->render(getMemDC(), m_ptMouse.x, m_ptMouse.y);
	TCHAR str[128];
	wsprintf(str, "ī�޶� ����Ʈ/ž : %d, %d", CAMERA->getRect().left, CAMERA->getRect().top);
	TextOut(getMemDC(),0, 0, str, lstrlen(str));
}

void mainDOL::gameInit()
{
	_bm = new bulletManager;
	_cm = new collisionManager;
	_mm = new monsterManager;
	_mapm = new mapManager;

	PLAYER->init();
	PLAYERDATA->init();
	ITEM->init();
	INVENTORY->init();

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

	//_mapm->init();		//�ε����� init�ǵ��� ����.



	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
		1008, 672, 0, 0, CAMERASIZEX / 2, CAMERASIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	CAMERA->FadeStart();

}
