#include "framework.h"
#include "shop.h"

#define ADJUSTSHOPX	74
shop::shop()
{
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
	IMAGE->addImage("상점", "images/object/shop_shop.bmp", 352, 192, true);
	IMAGE->addImage("마리이름상자", "images/object/moruNamebox.bmp", 250, 52, false);
	IMAGE->addImage("상점대화상자", "images/object/interactionBox.bmp", WINSIZEX * 3 / 5, 150, false);
	but1 = BUTTON->addButton("수락", 225+ ADJUSTSHOPX, 516, 222, 35);
	but2 = BUTTON->addButton("거절", 225+ ADJUSTSHOPX, 557, 222, 35);
}

shop::~shop()
{
}

HRESULT shop::add(float centerx, float centery)
{
	_img = IMAGE->findImage("상점");
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

	talkRc = RectMake(WINSIZEX / 2 - IMAGE->findImage("상점대화상자")->getWidth() / 2,
		WINSIZEY*3/5,
		IMAGE->findImage("상점대화상자")->getWidth(),
		IMAGE->findImage("상점대화상자")->getHeight());

	/*아이템4개 랜덤 뽑기 함수*/
	for (int i = 0; i < 4; i++)
	{
		int random = 0;
		random = RND->getFromInTo(0,ITEM->getV_Item().size()-1);
		itemdata[i] = ITEM->getV_Item()[random];
		ITEM->removeitem(random);
	}
	
	//아이템 위치 : RecCenX(interRc[i]), RecCenY(interRc[i])


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
	
	//항상 ON 대화상자
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		ZORDER->UIAlphaRender(IMAGE->findImage("마리이름상자"), ZUISECOND, 0, 188 + ADJUSTSHOPX, talkRc.top - 5 - IMAGE->findImage("마리이름상자")->getHeight(), boxAlpha);
		ZORDER->UIAlphaRender(IMAGE->findImage("상점대화상자"), ZUISECOND, 0, talkRc.left, talkRc.top, boxAlpha);

		RECT txtRc = RectMake(188 + ADJUSTSHOPX+20,
			420, IMAGE->findImage("상점대화상자")->getWidth(), IMAGE->findImage("상점대화상자")->getHeight());
		string str = "마리";
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc, 
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
	}
	if (isConversation1) {
		RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
		string str ="이건 " + itemdata[currentItemIndex].item_name; /*아이템 이름*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		txtRc = RectMake(talkRc.left + 15, talkRc.top + 15 + 40, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30 - 40);
		str = itemdata[currentItemIndex].item_shopInfo; /*아이템 설명*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
	}
		if (isConversation2) {

			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "가격은 " + to_string(itemdata[currentItemIndex].price) + " 골드인데, 살래?"; /*아이템 가격*/
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

			txtRc = RectMake(but1->rc.left + 5, but1->rc.top + 5, RecWidth(but1->rc) - 10, RecHeight(but1->rc) - 10);
			str = "응";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

			txtRc = RectMake(but2->rc.left + 5, but2->rc.top + 5, RecWidth(but2->rc) - 10, RecHeight(but2->rc) - 10);
			str = "아니";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
		if (isConversation3) {
			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "고마워!";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
		if (isConversation4) {
			RECT txtRc = RectMake(talkRc.left + 15, talkRc.top + 15, RecWidth(talkRc) - 30, RecHeight(talkRc) - 30);
			string str = "돈이 모자란것 같은데?";
			ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
				CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
				RGB(255, 255, 255), DT_LEFT | DT_VCENTER);
		}
	//수리를 할거냐는 문구와 버튼 두개가 뜸.
	if (BUTTON->isMouseOver("수락")) {
		ZORDER->UIAlphaRender(mouseoverImg, ZUISECOND, 1, 225+ ADJUSTSHOPX, 516, 100);
	}
	if (BUTTON->isMouseOver("거절")) {
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
				if (PLAYER->getSTATEAddress() == STATE::IDLE && !isConversation1 && INPUT->isOnceKeyDown('E'))	//상호작용 버튼활성화
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
	//충돌매니저에서 inter상자 충돌시 e키가 눌리면 canInteraction이 true가 됨.
	if (isConversation1)	//그건 이름\n. 설명\n.
	{
			if (_speakCount > 200) {
				BUTTON->buttonOn("수락");
				BUTTON->buttonOn("거절");
				_speakCount = 0;
				isConversation1 = false;
				isConversation2 = true;
			}
	}
	
		if (isConversation2)		//가격은 가격 골드인데, 살래?
		{
			//산다 선택시
			if (!(itemdata[currentItemIndex].item_name == "팔렸어"))
			{
				if (BUTTON->isClick("수락")) {
					BUTTON->buttonOff("수락");
					BUTTON->buttonOff("거절");
					isConversation2 = false;
					if (PLAYERDATA->changeGold(/*가격*/-itemdata[currentItemIndex].price, true))//돈 비교. 차감 구문
					{
						PLAYERDATA->changeGold(/*가격*/-itemdata[currentItemIndex].price, false);
						_speakCount = 0;
						isConversation3 = true;	//고마워!
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
						isConversation4 = true;	//돈이 모자란 것 같은데?
					}
				}
				//안산다 선택시
				else if (BUTTON->isClick("거절"))
				{
					BUTTON->buttonOff("수락");
					BUTTON->buttonOff("거절");
					isConversation2 = false;
					PLAYER->playerStop();
				}
			}
			else
			{
				BUTTON->buttonOff("수락");
				BUTTON->buttonOff("거절");
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
