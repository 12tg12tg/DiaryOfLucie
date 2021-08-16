#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("모루", "images/object/moru.bmp", 288, 384, 2, 4, true);
	IMAGE->addImage("이름상자", "images/object/moruNamebox.bmp", 250, 52, false);
	IMAGE->addImage("모루대화상자", "images/object/interactionBox.bmp", WINSIZEX*3/5, 150, false);
	IMAGE->addImage("모루이름", "images/object/moruName.bmp", 225, 42, true);
	IMAGE->addImage("모루멘트1", "images/object/morument1.bmp", 614, 160, true);
	IMAGE->addImage("모루멘트2", "images/object/morument2.bmp", 614, 160, true);
	IMAGE->addImage("모루멘트3", "images/object/morument3.bmp", 614, 160, true);
	IMAGE->addImage("모루멘트4", "images/object/morument4.bmp", 614, 160, true);
	but1 = BUTTON->addButton("모루-수리한다", 225, 475, 222, 35);
	but2 = BUTTON->addButton("모루-무시한다", 225, 516, 222, 35);
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
}

moru::~moru()
{
}

HRESULT moru::add(float centerx, float centery)
{
	_img = IMAGE->findImage("모루");
	_x = centerx - _img->getFrameWidth()/2;
	_y = centery - _img->getFrameHeight()/2;
	_hitRc = RectMake(_x + _img->getFrameWidth() / 9, _y + _img->getFrameHeight() / 4, 
		_img->getFrameWidth()*7/9, _img->getFrameHeight()*3/4);
	_footRc = RectMake(_hitRc.left, _hitRc.top + RecHeight(_hitRc) / 3, RecWidth(_hitRc), RecHeight(_hitRc) * 2 / 3);
	_interRc = RectMake(_footRc.left - 1,//RecWidth(PLAYER->getPlayerAddress().playerRect),
		_footRc.top - 1,//RecHeight(PLAYER->getPlayerAddress().playerRect),
		RecWidth(_footRc) + 2,//RecWidth(PLAYER->getPlayerAddress().playerRect)*2,
		RecHeight(_footRc) + 2);//RecHeight(PLAYER->getPlayerAddress().playerRect)*2);
	_state = MORUSTATE::NONE;
	int arr[] = { 0 };
	_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr)/sizeof(int), 5, true);
	_speakCount = 0;
	isConversation1 = false;
	isConversation2 = false;
	isConversation3 = false;
	isConversation4 = false;

	boxAlpha = 200;
	return S_OK;
}

void moru::release()
{
	BUTTON->removeButton("모루_수리한다");
	BUTTON->removeButton("모루_무시한다");
	SAFE_DELETE(mouseoverImg);
}

void moru::update(bulletManager* bm)
{
	bulletCollision(bm);
	playerCollision();
	giveFrame();
	checkRepair();
}

void moru::render()
{
	if (_isDebug) {
		ZORDER->ZorderRectangle(_interRc, ZFLOORMAP);
		ZORDER->ZorderRectangle(_hitRc, ZCOL1);
		ZORDER->ZorderRectangleColor(_footRc, ZCOL2, MINT);
	}
	ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);

	//할배 네임태그
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		IMAGE->findImage("이름상자")->alphaRender(getMemDC(), 188, 360, 200);
		IMAGE->findImage("모루이름")->render(getMemDC(), 200, 365);
		IMAGE->findImage("모루대화상자")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGE->findImage("모루대화상자")->getWidth() / 2,
			420, 200);
	}
	//대화상자 출력
	if (isConversation1)
	{
		//수리를 할거냐는 문구와 버튼 두개가 뜸.
		if (BUTTON->isMouseOver("모루-수리한다")) {
			mouseoverImg->alphaRender(getMemDC(), 225, 475, 100);
		}										
		if (BUTTON->isMouseOver("모루-무시한다")) {
			mouseoverImg->alphaRender(getMemDC(), 225, 516, 100);
		}
		IMAGE->findImage("모루멘트1")->render(getMemDC(), 190, 410);
	}
	else if (isConversation2)
	{
		IMAGE->findImage("모루멘트2")->render(getMemDC(), 190, 410);
	}
	else if (isConversation3)
	{
		IMAGE->findImage("모루멘트3")->render(getMemDC(), 190, 410);
	}
	else if (isConversation4)
	{
		IMAGE->findImage("모루멘트4")->render(getMemDC(), 190, 410);
	}
}

void moru::afterHit()
{

}

void moru::giveFrame()
{
	switch (_state)
	{
	case MORUSTATE::NONE:
		{
		int arr[] = { 0 };
		ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::SPEAK:
		if (_speakCount == 0) {
			int arr[] = { 0, 1 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::BROKEN:
		if (_speakCount == 0) {
			int arr[] = { 6, 3 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 120) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::NOMONEY:
		if (_speakCount == 0) {
			int arr[] = { 0, 4 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "모루", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	}
}

void moru::bulletCollision(bulletManager* bm)
{
	RECT temp;
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			bm->getMgcBulInstance()->removeBullet(i);
		}
	}
	//2. 플레이어 화살
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle, _hitRc, 0))
		{
			bm->getArwBulInstance()->removeBullet(i);
		}
	}
	//3. 검은 안해도 됨.
}

void moru::playerCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_footRc))
	{
		int fromtop, frombottom, fromleft, fromright;
		int centerx, centery;
		int min;
		centerx = temp.left + (temp.right - temp.left) / 2;
		centery = temp.top + (temp.bottom - temp.top) / 2;
		fromtop = centery - _footRc.top;
		frombottom = _footRc.bottom - centery;
		fromleft = centerx - _footRc.left;
		fromright = _footRc.right - centerx;

		min = (fromtop >= frombottom) ? frombottom : fromtop;
		min = (min >= fromleft) ? fromleft : min;
		min = (min >= fromright) ? fromright : min;
		if (min == fromtop && min <= 50)
		{
			PLAYER->getPlayerAddress().y = _footRc.top - (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == frombottom)
		{
			PLAYER->getPlayerAddress().y = _footRc.bottom + (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == fromleft)
		{
			PLAYER->getPlayerAddress().x = _footRc.left - (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
		else if (min == fromright)
		{
			PLAYER->getPlayerAddress().x = _footRc.right + (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
	}
	playerInterCollision();
}

void moru::playerInterCollision()
{
	RECT temp;
	if (!isConversation1 && !isConversation2 && !isConversation3 && !isConversation4) {
		if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_interRc))
		{
			if (PLAYER->getSTATEAddress() == STATE::IDLE && !isConversation1 && INPUT->isOnceKeyDown('E'))	//상호작용 버튼활성화
			{
				isConversation1 = true;
				BUTTON->buttonOn("모루-수리한다");
				BUTTON->buttonOn("모루-무시한다");
				_speakCount = 0;
				_state = MORUSTATE::SPEAK;

				PLAYER->playerStop();
			}
		}
	}
}

void moru::checkRepair()
{
	_speakCount++;
	//충돌매니저에서 inter상자 충돌시 e키가 눌리면 canInteraction이 true가 됨.
	if (isConversation1)
	{
		//수리한다 선택시
		if (BUTTON->isClick("모루-수리한다")) {
			BUTTON->buttonOff("모루-수리한다");
			BUTTON->buttonOff("모루-무시한다");
			isConversation1 = false;
			if (PLAYERDATA->changeGold(-30, true))//돈 비교. 차감 구문
			{
				PLAYERDATA->changeGold(-30, false);
				if (RND->getInt(2))
				{
					_speakCount = 0;
					isConversation2 = true;	//자 수리가 완료되었네.
				}
				else
				{
					_speakCount = 0;
					_state = MORUSTATE::BROKEN;
					isConversation3 = true;	//어이쿠 손이 미끄러졌네.
				}
			}
			else {
				_speakCount = 0;
				_state = MORUSTATE::NOMONEY;
				isConversation4 = true;	//자네는 돈이 부족해보이는구만.
			}
		}
		//무시한다 선택시
		else if (BUTTON->isClick("모루-무시한다"))
		{
			BUTTON->buttonOff("모루-수리한다");
			BUTTON->buttonOff("모루-무시한다");
			_state = MORUSTATE::NONE;
			isConversation1 = false;
			PLAYER->playerStop();
		}
	}
	if ((isConversation2 || isConversation4) && (_speakCount > 100))
	{
		isConversation2 = false;
		isConversation4 = false;
		PLAYER->playerStop();
	}
	if (isConversation3 && _speakCount > 120)
	{
		isConversation3 = false;
		PLAYER->playerStop();
	}
}
