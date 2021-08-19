#include "framework.h"
#include "shop.h"

#define ADJUSTSHOPX	74
shop::shop()
{
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
	IMAGE->addImage("����", "images/object/shop_shop.bmp", 352, 192, true);
	IMAGE->addImage("�����̸�����", "images/object/moruNamebox.bmp", 250, 52, false);
	IMAGE->addImage("������ȭ����", "images/object/interactionBox.bmp", WINSIZEX * 3 / 5, 150, false);
	but1 = BUTTON->addButton("����", 225+ ADJUSTSHOPX, 516, 222, 35);
	but2 = BUTTON->addButton("����", 225+ ADJUSTSHOPX, 557, 222, 35);
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

	interRc[0] = RectMake(_x+_img->getWidth()*3/14 + 5 , _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12+20);
	interRc[1] = RectMake(_x+_img->getWidth()*5/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 20);
	interRc[2] = RectMake(_x+_img->getWidth()*8/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 20);
	interRc[3] = RectMake(_x+_img->getWidth()*10/14 - 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 20);

	talkRc = RectMake(WINSIZEX / 2 - IMAGE->findImage("������ȭ����")->getWidth() / 2,
		WINSIZEY*3/5,
		IMAGE->findImage("������ȭ����")->getWidth(),
		IMAGE->findImage("������ȭ����")->getHeight());

	/*������4�� ���� �̱� �Լ�*/
	for (int i = 0; i < 4; i++)
	{
		int random = 0;
		random = RND->getFromInTo(0,ITEM->getV_Item().size()-1);
		itemdata[i] = ITEM->getV_Item()[random];
		ITEM->removeitem(random);
	}
	
	//������ ��ġ : RecCenX(interRc[i]), RecCenY(interRc[i])


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
	
	ZORDER->ZorderRender(_img, ZUNIT, _y + _img->getHeight() / 2 + 10, _x, _y);
	if (_isDebug) {
		for (size_t i = 0; i < 4; i++)
		{
			ZORDER->ZorderRectangle(interRc[i], ZCOL1);
			ZORDER->ZorderRender(itemdata[i].item_image, ZUNIT, _y + _img->getHeight() / 2 + 10, RecCenX(interRc[i]), interRc[i].top);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		ZORDER->ZorderRender(itemdata[i].item_image, ZUNIT, _y + _img->getHeight() / 2 + 10, RecCenX(interRc[i]), interRc[i].top);
	}
	
	//�׻� ON ��ȭ����
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		ZORDER->UIAlphaRender(IMAGE->findImage("�����̸�����"), ZUISECOND, 0, 188 + ADJUSTSHOPX, talkRc.top - 5 - IMAGE->findImage("�����̸�����")->getHeight(), boxAlpha);
		ZORDER->UIAlphaRender(IMAGE->findImage("������ȭ����"), ZUISECOND, 0, talkRc.left, talkRc.top, boxAlpha);

		RECT txtRc = RectMake(188 + ADJUSTSHOPX+20,
			420, IMAGE->findImage("������ȭ����")->getWidth(), IMAGE->findImage("������ȭ����")->getHeight());
		string str = "����";
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc, 
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
	}
	if (isConversation1) {
		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str ="�̰� " + itemdata[currentItemIndex].item_name; /*������ �̸�*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		txtRc = RectMake(talkRc.left + 15, talkRc.top + 15 + 40, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30 - 40);
		str = itemdata[currentItemIndex].item_shopInfo; /*������ ����*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
	}
		if (isConversation2) {

			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "������ " + to_string(itemdata[currentItemIndex].price) + " ����ε�, �췡?"; /*������ ����*/
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

			txtRc = RectMake(but1->rc.left + 5, but1->rc.top + 5, RecWidth(but1->rc) - 10, RecHeight(but1->rc) - 10);
			str = "��";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

			txtRc = RectMake(but2->rc.left + 5, but2->rc.top + 5, RecWidth(but2->rc) - 10, RecHeight(but2->rc) - 10);
			str = "�ƴ�";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
		if (isConversation3) {
			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "����!";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
		if (isConversation4) {
			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "���� ���ڶ��� ������?";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
	//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
	if (BUTTON->isMouseOver("����")) {
		ZORDER->UIAlphaRender(mouseoverImg, ZUISECOND, 1, 225+ ADJUSTSHOPX, 516, 100);
	}
	if (BUTTON->isMouseOver("����")) {
		ZORDER->UIAlphaRender(mouseoverImg, ZUISECOND, 1, 225+ ADJUSTSHOPX, 557, 100);
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
			if (_speakCount > 200) {
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
			if (!(itemdata[currentItemIndex].item_name == "�ȷȾ�"))
			{
				if (BUTTON->isClick("����")) {
					BUTTON->buttonOff("����");
					BUTTON->buttonOff("����");
					isConversation2 = false;
					if (PLAYERDATA->changeGold(/*����*/-itemdata[currentItemIndex].price, true))//�� ��. ���� ����
					{
						PLAYERDATA->changeGold(/*����*/-itemdata[currentItemIndex].price, false);
						_speakCount = 0;
						isConversation3 = true;	//����!
						if (itemdata[currentItemIndex].itemType == ITEMTYPE::accesory)
						{
							;
						}
						else
						{
						INVENTORY->InventoryDataPushBack(itemdata[currentItemIndex].item_name, itemdata[currentItemIndex].equipHP, itemdata[currentItemIndex].equipMP);
						}
						emptyitem(currentItemIndex);
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
			else
			{
				BUTTON->buttonOff("����");
				BUTTON->buttonOff("����");
				isConversation2 = false;
				PLAYER->playerStop();
			}
		}
	

		if (isConversation3 || isConversation4)
		{
			if (_speakCount > 140) {
				_speakCount = 0;
				isConversation3 = false;
				isConversation4 = false;
				PLAYER->playerStop();
			}
		}
	
	
}
