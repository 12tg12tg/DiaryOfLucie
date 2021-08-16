#include "framework.h"
#include "shop.h"

shop::shop()
{
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
	IMAGE->addImage("상점", "images/object/shop_shop.bmp", 352, 192, true);
	IMAGE->addImage("상점대화상자", "images/object/interactionBox.bmp", WINSIZEX * 3 / 5, 150, false);
	but1 = BUTTON->addButton("수락", 225, 475, 222, 35);
	but1 = BUTTON->addButton("거절", 225, 516, 222, 35);
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

	interRc[0] = RectMake(_x+_img->getWidth()*3/14 + 5 , _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12+5);
	interRc[1] = RectMake(_x+_img->getWidth()*5/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);
	interRc[2] = RectMake(_x+_img->getWidth()*8/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);
	interRc[3] = RectMake(_x+_img->getWidth()*10/14 + 5, _y+ _img->getHeight()*6/12, _img->getWidth()/14, _img->getHeight()*4 / 12 + 5);

	/*아이템4개 랜덤 뽑기 함수*/
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
	ZORDER->ZorderRender(_img, ZUNIT, _y + _img->getHeight() / 2, _x, _y);
	if (_isDebug) {
		for (size_t i = 0; i < 4; i++)
		{
			ZORDER->ZorderRectangle(interRc[i], ZCOL1);
		}
	}
	//항상 ON 대화상자
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		//IMAGE->findImage("이름상자")->alphaRender(getMemDC(), 188, 360, 200);
		//IMAGE->findImage("모루이름")->render(getMemDC(), 200, 365);
		IMAGE->findImage("상점대화상자")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGE->findImage("상점대화상자")->getWidth() / 2,
			420, boxAlpha);
		HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕"));
		HFONT oFont = (HFONT)SelectObject(getMemDC(), hFont);
		RECT txtRc = RectMake(WINSIZEX / 2 - IMAGE->findImage("상점대화상자")->getWidth() / 2,
			420, IMAGE->findImage("상점대화상자")->getWidth(), IMAGE->findImage("상점대화상자")->getHeight());
		string str = "그건 빵";

		SetBkMode(getMemDC(), TRANSPARENT);	//배경 투명
		SetTextColor(getMemDC(), RGB(255, 255, 255));//글자 색
		DrawText(getMemDC(), str.c_str(), -1, &txtRc, DT_LEFT | DT_VCENTER);
		SelectObject(getMemDC(), oFont);
		DeleteObject(hFont);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
	}
	if (isConversation1) {

	}
	if (isConversation2) {

	}
	if (isConversation3) {

	}
	if (isConversation4) {

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
		if (_speakCount > 100) {
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
		if (BUTTON->isClick("수락")) {
			BUTTON->buttonOff("수락");
			BUTTON->buttonOff("거절");
			isConversation2 = false;
			if (PLAYERDATA->changeGold(/*가격*/-60, true))//돈 비교. 차감 구문
			{
				PLAYERDATA->changeGold(/*가격*/-60, false);
				_speakCount = 0;
				isConversation3 = true;	//고마워!
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
