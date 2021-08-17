#include "framework.h"
#include "shop.h"

shop::shop()
{
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
	IMAGE->addImage("����", "images/object/shop_shop.bmp", 352, 192, true);
	IMAGE->addImage("�����̸�����", "images/object/moruNamebox.bmp", 250, 52, false);
	IMAGE->addImage("������ȭ����", "images/object/interactionBox.bmp", WINSIZEX * 3 / 5, 150, false);
	but1 = BUTTON->addButton("����", 225, 516, 222, 35);
	but2 = BUTTON->addButton("����", 225, 557, 222, 35);
}

shop::~shop()
{
}

HRESULT shop::add(float centerx, float centery)
{
	_img = IMAGE->findImage("����");
	_x = centerx - _img->getFrameWidth() / 2;
	_y = centery - _img->getFrameHeight() / 2;

	_speakCount = 0;
	isConversation1 = false;
	isConversation2 = false;
	isConversation3 = false;
	isConversation4 = false;

	boxAlpha = 200;

	interRc[0] = RectMake(_x+_img->getWidth()*3/14 + 5 , _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12+5);
	interRc[1] = RectMake(_x+_img->getWidth()*5/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);
	interRc[2] = RectMake(_x+_img->getWidth()*8/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);
	interRc[3] = RectMake(_x+_img->getWidth()*10/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);

	talkRc = RectMake(WINSIZEX / 2 - IMAGE->findImage("������ȭ����")->getWidth() / 2,
		WINSIZEY*3/5,
		IMAGE->findImage("������ȭ����")->getWidth(),
		IMAGE->findImage("������ȭ����")->getHeight());

	/*������4�� ���� �̱� �Լ�*/
	//������ ��ġ : RecCenX(interRc[i]), RecCenY(interRc[i])

	
	//usableBt = BUTTON->addFixableRect("�簢1", MINT);
	return S_OK;
}

void shop::release()
{
}

void shop::update(bulletManager* bm)
{
	playerInterCollision();
	soldItem();
}

void shop::render()
{
	ZORDER->ZorderRender(_img, ZUNIT, _y + _img->getHeight() / 2, _x, _y);
	if (_isDebug) {
		for (size_t i = 0; i < 4; i++)
		{
			ZORDER->ZorderRectangle(interRc[i], ZCOL1);
		}
	}
	//��Ʈ����
	HFONT hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰���"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), hFont);
	SetBkMode(getMemDC(), TRANSPARENT);	//��� ����
	SetTextColor(getMemDC(), RGB(255, 255, 255));//���� ��
	//�׻� ON ��ȭ����
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		IMAGE->findImage("�����̸�����")->alphaRender(getMemDC(), 188, talkRc.top-5-IMAGE->findImage("�����̸�����")->getHeight(), 200);
		IMAGE->findImage("������ȭ����")->alphaRender(getMemDC(), talkRc.left, talkRc.top, boxAlpha);
		RECT txtRc = RectMake(WINSIZEX / 2 - IMAGE->findImage("������ȭ����")->getWidth() / 2,
			420, IMAGE->findImage("������ȭ����")->getWidth(), IMAGE->findImage("������ȭ����")->getHeight());
		string str = "����";
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);
	}
	if (isConversation1) {

		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str = "�װ� ��"; /*������ �̸�*/
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);

		txtRc = RectMake(talkRc.left + 15, talkRc.top + 15 + 40, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30 - 40);
		str = "���� ��ħ�� �԰� �����ž�."; /*������ ����*/
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);

	}
	if (isConversation2) {

		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str = "������ " + to_string(100) + "����ε�, �췡?"; /*������ ����*/
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);

		txtRc = RectMake(but1->rc.left + 5, but1->rc.top + 5, RecWidth(but1->rc) - 10, RecHeight(but1->rc) - 10);
		str = "��";
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);

		txtRc = RectMake(but2->rc.left + 5, but2->rc.top + 5, RecWidth(but2->rc) - 10, RecHeight(but2->rc) - 10);
		str = "�ƴ�";
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);
	}
	if (isConversation3) {
		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str = "������!";
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);
	}
	if (isConversation4) {
		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str = "���� ���ڶ��� ������?";
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);
	}

	//��Ʈ����
	SelectObject(getMemDC(), oFont);
	DeleteObject(hFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
	if (BUTTON->isMouseOver("����")) {
		mouseoverImg->alphaRender(getMemDC(), 225, 516, 100);
	}
	if (BUTTON->isMouseOver("����")) {
		mouseoverImg->alphaRender(getMemDC(), 225, 557, 100);
	}
}

void shop::playerInterCollision()
{
	RECT temp;
	if (!isConversation1 && !isConversation2 && !isConversation3 && !isConversation4) {
		for (size_t i = 0; i < 4; i++)
		{
			if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &interRc[i]))
			{
				if (PLAYER->getSTATEAddress() == STATE::IDLE && !isConversation1 && INPUT->isOnceKeyDown('E'))	//��ȣ�ۿ� ��ưȰ��ȭ
				{
					currentItemIndex = i;
					isConversation1 = true;
					_speakCount = 0;
					PLAYER->playerStop();
				}
			}

		}
	}
}

void shop::soldItem()
{
	_speakCount++;
	//�浹�Ŵ������� inter���� �浹�� eŰ�� ������ canInteraction�� true�� ��.
	if (isConversation1)	//�װ� �̸�\n. ����\n.
	{
		if (_speakCount > 100) {
			BUTTON->buttonOn("����");
			BUTTON->buttonOn("����");
			_speakCount = 0;
			isConversation1 = false;
			isConversation2 = true;
		}
	}
	if (isConversation2)		//������ ���� ����ε�, �췡?
	{
		//��� ���ý�
		if (BUTTON->isClick("����")) {
			BUTTON->buttonOff("����");
			BUTTON->buttonOff("����");
			isConversation2 = false;
			if (PLAYERDATA->changeGold(/*����*/-60, true))//�� ��. ���� ����
			{
				PLAYERDATA->changeGold(/*����*/-60, false);
				_speakCount = 0;
				isConversation3 = true;	//������!
			}
			else {
				_speakCount = 0;
				isConversation4 = true;	//���� ���ڶ� �� ������?
			}
		}
		//�Ȼ�� ���ý�
		else if (BUTTON->isClick("����"))
		{
			BUTTON->buttonOff("����");
			BUTTON->buttonOff("����");
			isConversation2 = false;
			PLAYER->playerStop();
		}
	}
	if (isConversation3 || isConversation4)
	{
		if (_speakCount > 80) {
			_speakCount = 0;
			isConversation3 = false;
			isConversation4 = false;
			PLAYER->playerStop();
		}
	}
}