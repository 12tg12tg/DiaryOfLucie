#include "framework.h"
#include "chest.h"
#include "bulletManager.h"
chest::chest()
{
    IMAGE->addFrameImage("작은상자", "images/object/chest1.bmp", 50, 200, 1, 4, true);
    IMAGE->addFrameImage("큰상자", "images/object/chest2.bmp", 96, 384, 1, 4, true);
}

chest::~chest()
{
}

HRESULT chest::add(float centerx, float centery)
{
	if (_curBox = RND->getInt(2)) {
		_img = IMAGE->findImage("작은상자");
		_x = centerx - _img->getFrameWidth() / 2;
		_y = centery - _img->getFrameHeight() / 2;
		_hitRc = RectMake(_x + _img->getFrameWidth() / 5, _y + _img->getFrameHeight() * 4 / 13,
			_img->getFrameWidth() * 3 / 5, _img->getFrameHeight() * 8 / 13);
		_footRc = RectMake(_hitRc.left, _hitRc.top + RecHeight(_hitRc) / 2, RecWidth(_hitRc), RecHeight(_hitRc) / 2 + 10);
		_interRc = RectMake(_footRc.left - 1,
			_footRc.top - 1,
			RecWidth(_footRc) + 2,
			RecHeight(_footRc) + 2);
		int arr[] = { 0 };
		_ani = ANIMATION->addNoneKeyAnimation("작은상자", arr, sizeof(arr) / sizeof(int), false);
	}
	else {
		_img = IMAGE->findImage("큰상자");
		_x = centerx - _img->getFrameWidth() / 2;
		_y = centery - _img->getFrameHeight() / 2;
		_hitRc = RectMake(_x + _img->getFrameWidth() / 6, _y + _img->getFrameHeight() * 5 / 14,
			_img->getFrameWidth() * 4 / 6, _img->getFrameHeight() * 8 / 14);
		_footRc = RectMake(_hitRc.left, _hitRc.top + RecHeight(_hitRc)* 5 / 8, RecWidth(_hitRc), RecHeight(_hitRc)*3 /8 + 10);
		_interRc = RectMake(_footRc.left - 1,
			_footRc.top - 1,
			RecWidth(_footRc) + 2,
			RecHeight(_footRc) + 2);
		int arr[] = { 0 };
		_ani = ANIMATION->addNoneKeyAnimation("큰상자", arr, sizeof(arr) / sizeof(int), false);
	}
	
	_isOpen = false;
	return S_OK;
}

void chest::release()
{
}

void chest::update(bulletManager* bm)
{
	bulletCollision(bm);
	playerCollision();
	afterHit();
	giveFrame();
}

void chest::render()
{
	if (_isDebug) {
		ZORDER->ZorderRectangle(_interRc, ZCOL1);
		ZORDER->ZorderRectangle(_hitRc, ZCOL2);
		ZORDER->ZorderRectangleColor(_footRc, ZCOL2, MINT);
	}
	ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);
}

void chest::playerInterCollision()
{
	RECT temp;
	if (!_isOpen && IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_interRc))
	{
		if (PLAYER->getSTATEAddress() == STATE::IDLE && INPUT->isOnceKeyDown('E'))	//상호작용 버튼활성화
		{
			_isOpen = true;
			_openCount = 0;
		}
	}
}

void chest::playerCollision()
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

void chest::bulletCollision(bulletManager* bm)
{
	RECT temp;
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			bm->getMgcBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//2. 플레이어 화살
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle, _hitRc, 0))
		{
			bm->getArwBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//3. 검은 안해도됨.


}

void chest::afterHit()
{
	if (!_isOpen) return;
	if (_openCount == 0) {
		//작은상자
		if (_curBox == 0)
		{
			/*아이템뱉기*/
		}
		//큰상자
		else
		{
			/*아이템뱉기*/
		}
	}
}

void chest::giveFrame()
{
	if (!_isOpen) return;
	if (_openCount == 0) {
		//작은상자
		if (_curBox == 1)
		{
			ANIMATION->changeNonKeyAnimation(_ani, "작은상자", 0, 3, 5, false, false);
		}
		//큰상자
		else
		{
			ANIMATION->changeNonKeyAnimation(_ani, "큰상자", 0, 3, 5, false, false);
		}
	}
	_openCount++;
}
