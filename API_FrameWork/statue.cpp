#include "framework.h"
#include "statue.h"
#include "bulletManager.h"
statue::statue()
{
	IMAGE->addFrameImage("석상-레드", "images/object/statue-red.bmp", 288, 384, 3, 4, true);
	IMAGE->addFrameImage("석상-블루", "images/object/statue-blue.bmp", 288, 384, 3, 4, true);
}

statue::~statue()
{
}

HRESULT statue::add(float centerx, float centery)
{
	_img = IMAGE->findImage("석상-레드");
	_x = centerx - _img->getFrameWidth();
	_y = centery - _img->getFrameHeight()/2;
	_hitRc = RectMake(_x + _img->getFrameWidth() / 3, _y + _img->getFrameHeight() / 4,
		_img->getFrameWidth()/3, _img->getFrameHeight() * 3 / 4);
	_footRc = RectMake(_hitRc.left, _hitRc.top+ _img->getFrameHeight()*2/4,
		RecWidth(_hitRc) + 4, RecHeight(_hitRc)/3);
	_neverChangeX = _x;
	_neverChangeY = _y;

	_img2 = IMAGE->findImage("석상-블루");
	_x2 = centerx + _img2->getFrameWidth();
	_y2 = centery - _img2->getFrameHeight()/2;
	_hitRc2 = RectMake(_x2 + _img2->getFrameWidth() / 3, _y2 + _img2->getFrameHeight() / 4,
		_img2->getFrameWidth() / 3, _img2->getFrameHeight() * 3 / 4);
	_footRc2 = RectMake(_hitRc2.left, _hitRc2.top + _img2->getFrameHeight() * 2 / 4,
		RecWidth(_hitRc2) + 4, RecHeight(_hitRc2) / 3);
	_neverChangeX2 = _x2;
	_neverChangeY2 = _y2;

	(RND->getInt(2)) ? _plusIndex = 6 : _plusIndex = 0;
	if (_plusIndex == 6) _plusIndex2 = 0;
	else _plusIndex2 = 6;

	_ani = ANIMATION->addNoneKeyAnimation("석상-레드", 0 + _plusIndex, 2 + _plusIndex, 10, true, true);
	_ani2 = ANIMATION->addNoneKeyAnimation("석상-블루", 0 + _plusIndex2, 2 + _plusIndex2, 10, true, true);

	_isHit = false;
	_isHit2 = false;

	return S_OK;
}

void statue::release()
{

}

void statue::update(bulletManager* bm)
{
	_x = _neverChangeX;
	_y = _neverChangeY;
	_x2 = _neverChangeX2;
	_y2 = _neverChangeY2;
	bulletCollision(bm);
	giveFrame();
	playerCollision();
}

void statue::render()
{
	ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);
	ZORDER->ZorderAniRender(_img2, ZUNIT, _footRc2.bottom, _x2, _y2, _ani2);
}

void statue::playerCollision()
{
	//-------------------------------------------------------------------------레드석상
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
	//-------------------------------------------------------------------------블루석상
	if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_footRc2))
	{
		int fromtop, frombottom, fromleft, fromright;
		int centerx, centery;
		int min;
		centerx = temp.left + (temp.right - temp.left) / 2;
		centery = temp.top + (temp.bottom - temp.top) / 2;
		fromtop = centery - _footRc2.top;
		frombottom = _footRc2.bottom - centery;
		fromleft = centerx - _footRc2.left;
		fromright = _footRc2.right - centerx;

		min = (fromtop >= frombottom) ? frombottom : fromtop;
		min = (min >= fromleft) ? fromleft : min;
		min = (min >= fromright) ? fromright : min;
		if (min == fromtop && min <= 50)
		{
			PLAYER->getPlayerAddress().y = _footRc2.top - (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == frombottom)
		{
			PLAYER->getPlayerAddress().y = _footRc2.bottom + (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == fromleft)
		{
			PLAYER->getPlayerAddress().x = _footRc2.left - (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
		else if (min == fromright)
		{
			PLAYER->getPlayerAddress().x = _footRc2.right + (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
	}
}

void statue::bulletCollision(bulletManager* bm)
{
	//-------------------------------------------------------------------------레드석상
	RECT temp;
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			if (!_isHit && !_isHit2) {
				_isHit = true;
				float angle = UTIL::getAngle(bm->getMgcBulInstance()->getVBullet()[i].x,
					bm->getMgcBulInstance()->getVBullet()[i].y,
					_x + _img->getFrameWidth()/2, _y+_img->getFrameHeight()/2);
				_x += cosf(angle) * 5;
				_y -= sinf(angle) * 5;
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
			if (!_isHit && !_isHit2) {
				_isHit = true;
				float angle = UTIL::getAngle(bm->getArwBulInstance()->getVBullet()[i].x,
					bm->getArwBulInstance()->getVBullet()[i].y,
					_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2);
				_x += cosf(angle) * 5;
				_y -= sinf(angle) * 5;
			}
			bm->getArwBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//3. 검


	//-------------------------------------------------------------------------블루석상
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc2))
		{
			if (!_isHit && !_isHit2) {
				_isHit2 = true;
				float angle = UTIL::getAngle(bm->getMgcBulInstance()->getVBullet()[i].x,
					bm->getMgcBulInstance()->getVBullet()[i].y,
					_x2 + _img2->getFrameWidth() / 2, _y2 + _img2->getFrameHeight() / 2);
				_x2 += cosf(angle) * 5;
				_y2 -= sinf(angle) * 5;
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
			if (!_isHit && !_isHit2) {
				_isHit2 = true;
				float angle = UTIL::getAngle(bm->getArwBulInstance()->getVBullet()[i].x,
					bm->getArwBulInstance()->getVBullet()[i].y,
					_x2 + _img2->getFrameWidth() / 2, _y2 + _img2->getFrameHeight() / 2);
				_x2 += cosf(angle) * 5;
				_y2 -= sinf(angle) * 5;
			}
			bm->getArwBulInstance()->removeBullet(i);
			afterHit();
		}
	}
	//3. 검

}

void statue::afterHit()
{
	if (_isHit && _isHit2) {
	}
	else {
		_frameCount = 0;

		if (_isHit) {
			_isHit2 = true;
			if (RND->getInt(2)) {
				PLAYERDATA->hitPlayer(2);
			}
			else {
				PLAYERDATA->healPlayer(2);
			}
		}
		if (_isHit2) {
			_isHit = true;
			if (RND->getInt(2)) {
				PLAYERDATA->useMana(2);
			}
			else {
				PLAYERDATA->recoveryMana(2);
			}
		}
	}
}

void statue::giveFrame()
{
	if (_isHit && _isHit2) {
		if (_frameCount == 0) {
			int arr[] = { 4 + _plusIndex, 5 + _plusIndex, 3 + _plusIndex };
			ANIMATION->changeNonKeyAnimation(_ani, "석상-레드", arr, sizeof(arr)/sizeof(int), 5, false);
			int arr2[] = { 4 + _plusIndex2, 5 + _plusIndex2 , 3 + _plusIndex2 };
			ANIMATION->changeNonKeyAnimation(_ani2, "석상-블루", arr2, sizeof(arr2) / sizeof(int), 5, false);
		}
	}
	_frameCount++;
}
