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

	(RND->getInt(2)) ? plusIndex = 6 : plusIndex = 0;
	if (plusIndex == 6) plusIndex2 = 0;
	else plusIndex2 = 6;

	_ani = ANIMATION->addNoneKeyAnimation("석상-레드", 0 + plusIndex, 2 + plusIndex, 10, true, true);
	_ani2 = ANIMATION->addNoneKeyAnimation("석상-블루", 0 + plusIndex2, 2 + plusIndex2, 10, true, true);

	return S_OK;
}

void statue::release()
{
}

void statue::update(bulletManager* bm)
{
	bulletCollision(bm);
}

void statue::render()
{
	ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);
	ZORDER->ZorderAniRender(_img2, ZUNIT, _footRc2.bottom, _x2, _y2, _ani2);
}

void statue::playerCollision()
{
}

void statue::bulletCollision(bulletManager* bm)
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

void statue::afterHit()
{
}

void statue::giveFrame()
{

}
