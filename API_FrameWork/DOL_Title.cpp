#include "framework.h"
#include "DOL_Title.h"
#define ADJUSTTITLE 15
DOL_Title::DOL_Title()
{
	bg = IMAGE->addImage("Ÿ��Ʋ���", "images/title/titlebg2.bmp", WINSIZEX, WINSIZEY);
	title = IMAGE->addImage("Ÿ��Ʋ����", "images/title/title.bmp", WINSIZEX, WINSIZEY, true, RGB(20, 26, 28));
	startimg = IMAGE->addFrameImage("����", "images/title/startimg2.bmp", 130*1.4, 60 * 1.4, 1, 2, true, RGB(15, 17, 18));
	optiontimg = IMAGE->addFrameImage("�ɼ�", "images/title/optionimg.bmp", 130 * 1.4, 60 * 1.4, 1, 2, true, RGB(15, 17, 18));
	exitimg = IMAGE->addFrameImage("����", "images/title/exitimg.bmp", 130 * 1.4, 60 * 1.4, 1, 2, true, RGB(15, 17, 18));
	startimg->setFrameY(1);
	optiontimg->setFrameY(1);
	exitimg->setFrameY(1);
	_isStart = false;
	_fadeOut = false;
	IMAGE->addImage("����ȭ����ƼŬ1", "images/title/Particles8.bmp", 32, 32, true, RGB(15, 17, 18));
	CAMERA->FadeInit(80, FADE_IN);
	CAMERA->FadeStart();
}

DOL_Title::~DOL_Title()
{
}

HRESULT DOL_Title::init()
{
	start = BUTTON->addButton("start", 590, 514 - 54 * 3, 182, 42);
	option = BUTTON->addButton("option", 590, 514 - 54 * 2, 182, 42);
	maker = BUTTON->addButton("maker", 590, 514 - 54, 182, 42);
	exit = BUTTON->addButton("exit", 590, 514, 182, 42);
	BUTTON->buttonOn("start");
	BUTTON->buttonOn("option");
	BUTTON->buttonOn("maker");
	BUTTON->buttonOn("exit");
	return S_OK;
}

void DOL_Title::release()
{
}

void DOL_Title::update()
{
	_particleCount++;
	//���콺������ �����Ӻ���
	if (BUTTON->isMouseOver("start")) startimg->setFrameY(0);
	else startimg->setFrameY(1);
	if (BUTTON->isMouseOver("option")) optiontimg->setFrameY(0);
	else optiontimg->setFrameY(1);
	if (BUTTON->isMouseOver("exit")) exitimg->setFrameY(0);
	else exitimg->setFrameY(1);

	//Ŭ���� ����
	if (BUTTON->isClick("start"))
	{
		BUTTON->buttonOff("start");
		BUTTON->buttonOff("option");
		BUTTON->buttonOff("maker");
		BUTTON->buttonOff("exit");
		CAMERA->FadeInit(80, FADE_OUT);
		CAMERA->FadeStart();
		_fadeOut = true;
	}
	if (BUTTON->isClick("exit"))
	{
		PostQuitMessage(0);
	}

	//���̵�ƿ������� ���ο��� gameinit() �����ϵ���.
	if(_fadeOut && !CAMERA->getFadeIsStart())
		SCENE->changeScene("�ε�");
	//���̵������Ʈ
	CAMERA->FadeUpdate();
}

void DOL_Title::render()
{
	ZORDER->ZorderRender(bg, ZFLOORMAP, 0, 0, 0);

	//��ư����
	ZORDER->UIFrameRender(startimg, ZUIFIRST, start->rc.bottom, start->rc.left, start->rc.top,
		startimg->getFrameX(), startimg->getFrameY());
	ZORDER->UIFrameRender(optiontimg, ZUIFIRST, option->rc.bottom, option->rc.left, option->rc.top,
		optiontimg->getFrameX(), optiontimg->getFrameY());
	ZORDER->UIFrameRender(exitimg, ZUIFIRST, exit->rc.bottom, exit->rc.left, exit->rc.top,
		exitimg->getFrameX(), exitimg->getFrameY());


	//��ƼŬ ���
	if (_particleCount % 60 == 0) {
		EFFECT->addParticle("����ȭ����ƼŬ1", ZEFFECT1, RND->getInt(WINSIZEX), WINSIZEY-50-RND->getInt(100), DEGREE(90), 200, true, 150);
	}

	////�׽�Ʈ
	//TCHAR str[128];
	//wsprintf(str, "���콺��ǥ : %d, %d", m_ptMouse.x, m_ptMouse.y);
	//TextOut(getMemDC(), 0, 0, str, lstrlen(str));

	//����Ʈ����
	EFFECT->render();

	//ZORDER
	ZORDER->ZorderTotalRender(getMemDC());

	//���̵巣��
	CAMERA->FadeRender(getMemDC());

	//�׽�Ʈ
	TCHAR str[128];
	wsprintf(str, "���콺��ǥ : %d, %d", m_ptMouse.x, m_ptMouse.y);
	ZORDER->UITextOut(str, ZMAXLAYER, 0, 60, MINT);
}
