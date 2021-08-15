#include "framework.h"
#include "fountain.h"
#include "bulletManager.h"
fountain::fountain()
{
	IMAGE->addFrameImage("분수대", "images/object/fountain.bmp", 192, 720, 2, 5, true);
}

fountain::~fountain()
{
}

HRESULT fountain::add(float centerx, float centery)
{
	_img = IMAGE->findImage("분수대");
	_x = centerx - _img->getFrameWidth();
	_y = centery - _img->getFrameHeight();
	_hitRc = RectMake(_x, _y + _img->getFrameHeight()*2 / 5,
		_img->getFrameWidth(), _img->getFrameHeight() * 3 / 5);
	_footRc = RectMake(_hitRc.left-2,_hitRc.top, RecWidth(_hitRc)+4,  RecHeight(_hitRc));
	_interRc = RectMake(_footRc.left - 1,
		_footRc.top - 1,
		RecWidth(_footRc) + 2,
		RecHeight(_footRc) + 2);
	_neverChangeX = _x;
	_neverChangeY = _y;
	_hp = 10;
	_ani = ANIMATION->addNoneKeyAnimation("분수대", 0, 7, 10, false, true);



	boxAlpha = 200;

	return S_OK;
}

void fountain::release()
{
}

void fountain::update(bulletManager* bm)
{
	_x = _neverChangeX;
	_y = _neverChangeY;
	setBox();
	bulletCollision(bm);
	playerCollision();
}

void fountain::render()
{
	if (_isDebug) {
		ZORDER->ZorderRectangle(_interRc, ZCOL1);
		//ZORDER->ZorderRectangle(_hitRc, ZCOL2);
		ZORDER->ZorderRectangleColor(_footRc, ZCOL2, MINT);
	}
	if (_hp > 0) {
		ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);
	}
	else {
		ZORDER->ZorderFrameRender(_img, ZUNIT, _footRc.bottom, _x, _y, 0, 4);
	}
}

void fountain::bulletCollision(bulletManager* bm)
{
	RECT temp;
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			if (_hp > 0) {
				float angle = UTIL::getAngle(bm->getMgcBulInstance()->getVBullet()[i].x,
					bm->getMgcBulInstance()->getVBullet()[i].y, _x, _y);
				_x += cosf(angle) * 10;
				_y -= sinf(angle) * 10;
			}
			bm->getMgcBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//2. 플레이어 화살
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle, _hitRc, 0))
		{
			if (_hp > 0) {
				float angle = UTIL::getAngle(bm->getArwBulInstance()->getVBullet()[i].x,
					bm->getArwBulInstance()->getVBullet()[i].y, _x, _y);
				_x += cosf(angle) * 5;
				_y -= sinf(angle) * 5;
			}
			bm->getArwBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//3. 검은 안해도 됨.
}

void fountain::playerCollision()
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
}

void fountain::afterHit()
{
	/*동전 투척*/
	_hp--;
}

void fountain::giveFrame()
{
}

void fountain::setBox()
{
	_hitRc = RectMake(_x, _y + _img->getFrameHeight() * 2 / 5,_img->getFrameWidth(), _img->getFrameHeight() * 3 / 5);
	_footRc = RectMake(_hitRc.left - 2, _hitRc.top, RecWidth(_hitRc) + 4, RecHeight(_hitRc));
	_interRc = RectMake(_footRc.left - 1, _footRc.top - 1, RecWidth(_footRc) + 2, RecHeight(_footRc) + 2);
}
