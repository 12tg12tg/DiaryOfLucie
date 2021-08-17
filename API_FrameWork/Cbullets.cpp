#include "framework.h"
#include "Cbullets.h"
#include "Cplayer.h"
/*
=================================================
	Find bullet class ctrl+F4 ("name!")
=================================================
	bulletname			imagename
1.	CpMagicBullet	/	마법총알
2.	CpArrowBullet	/	화살
3.	CmTripleBullet	/	작은몬스터총알
4.	CmCircleBulelt	/	작은몬스터총알
5.	CmReturnBullet  /   페어리총알1 , 페어리총알2
6.	CmWideBullet	/	작은몬스터총알
7.	CmHomingBullet	/   몬스터총알2
8.	CmPoisonBullet  /	독총알
9.	CmNiddleBullet  /	가시 , 경고
10.	CmLongPoisonBullet /	독총알
11.	CmSBoss1Bullet  /	버블 , 몬스터총알
12.	CmFBoss1Bullet  /    투명,가시,경고
13. CmFBoss2Bullet	/	가시,경고
14. CmFBoss3Bullet	/	몬스터총알
15. CmTBoss1Bullet	/	브레스
16. CmTBoss2Bullet	/	나무보스총알
17. CmTBoss3Bullet	/	몬스터총알
*/
//////////////////////////////////////////////////////////////
/////	CpMagicBullet!	    	마법총알!	//////////////////
//////////////////////////////////////////////////////////////
CpMagicBullet::CpMagicBullet()
{
}

CpMagicBullet::~CpMagicBullet()
{
}

HRESULT CpMagicBullet::init()
{
	_range = 25.0f; //임시
	return S_OK;
}

void CpMagicBullet::release()
{
}

void CpMagicBullet::update()
{
	move();
}


void CpMagicBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug)
			ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}
void CpMagicBullet::fire(float x, float y, float angle,int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("마법총알", "images/bullet_bmp/PBullet_magic.bmp", 26 , 26  , true);
	bullet.angle = angle;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.isPlayerBullet = true;
	_vBullet.push_back(bullet);
}
void CpMagicBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}
void CpMagicBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CpMagicBullet!	    	화살    !	//////////////////
//////////////////////////////////////////////////////////////

CpArrowBullet::CpArrowBullet()
{
}

CpArrowBullet::~CpArrowBullet()
{
}

HRESULT CpArrowBullet::init()
{
	_range = 3.0f; //임시
	return S_OK;
}

void CpArrowBullet::release()
{
}

void CpArrowBullet::update()
{
	move();
}

void CpArrowBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->rotateangle);
	}
}

void CpArrowBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("화살", "images/bullet_bmp/PBullet_arrow.bmp", 26  , 8  , true);
	bullet.angle = angle;
	bullet.rotateangle = angle + PI/2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.isPlayerBullet = true;
	_vBullet.push_back(bullet);
}

void CpArrowBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void CpArrowBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmTripleBullet	    	몬스터총알	//////////////////
//////////////////////////////////////////////////////////////

CmTripleBullet::CmTripleBullet()
{
}

CmTripleBullet::~CmTripleBullet()
{
}

HRESULT CmTripleBullet::init()
{
	return S_OK;
}

void CmTripleBullet::release()
{
}

void CmTripleBullet::update()
{
	move();
}

void CmTripleBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug)
			ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderStretchRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->plussize);
	}
}

void CmTripleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("작은몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 12 , 12, true);
		bullet.plussize = 1 + (double)plussize/bullet.bulletImage->getWidth();
		bullet.angle = angle - 0.2 + 0.2 * i;
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth()+plussize,
			bullet.bulletImage->getHeight()+plussize);
		bullet.iscollison = false;
		bullet.isPlayerBullet = false;
		_vBullet.push_back(bullet);
	}
}

void CmTripleBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void CmTripleBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmCircleBullet	    	몬스터총알	//////////////////
//////////////////////////////////////////////////////////////

CmCircleBullet::CmCircleBullet()
{
}

CmCircleBullet::~CmCircleBullet()
{
}

HRESULT CmCircleBullet::init()
{
	return S_OK;
}

void CmCircleBullet::release()
{
}

void CmCircleBullet::update()
{
	move();
}

void CmCircleBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmCircleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("작은몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 12  , 12  , true);
		bullet.angle = angle + 0.628 * i;
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.isPlayerBullet = false;
		bullet.iscollison = false;
		_vBullet.push_back(bullet);
	}
}

void CmCircleBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;


	}
}

void CmCircleBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmReturnBullet 페어리총알1 페어리총알2////////////////
//////////////////////////////////////////////////////////////
CmReturnBullet::CmReturnBullet()
{
}

CmReturnBullet::~CmReturnBullet()
{
}

HRESULT CmReturnBullet::init()
{
	return S_OK;
}

void CmReturnBullet::release()
{
}

void CmReturnBullet::update()
{
	move();
	move2();
}

void CmReturnBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->angle += 0.05);
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet2->bulletImage2, ZUNIT, _viBullet2->rc.bottom,
			_viBullet2->rc.left, _viBullet2->rc.top);
	}
}

void CmReturnBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("페어리총알1", "images/bullet_bmp/fairy_bullet1.bmp", 20 , 20  , true);
		bullet.angle2 = angle;
		bullet.angle = angle ;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.iscollison = false;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.count = 0;
		bullet.isPlayerBullet = false;
		_vBullet.push_back(bullet);
	
}

void CmReturnBullet::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;
	for (int i = 0; i < 30; i++)
	{
		ZeroMemory(&bullet2, sizeof(tagBullet));
		bullet2.bulletImage2 = new  image;
		bullet2.bulletImage2 = IMAGE->addImage("페어리총알2", "images/bullet_bmp/fairy_bullet2.bmp", 15 , 13 , true, RGB(255, 0, 255));

		bullet2.angle2 = 1.049;
		bullet2.angle = 0.209 * i;
		bullet2.speed = 2.0f;
		bullet2.alpha = 255;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getWidth(),
			bullet2.bulletImage2->getHeight());
		bullet2.iscollison = false;
		bullet2.count = 100;

		_vBullet2.push_back(bullet2);
	}
}

void CmReturnBullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count < 100)
		{
			_viBullet->x += cosf(_viBullet->angle2) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle2) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());

			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
			if (_viBullet->iscollison)
			{
				_viBullet->count = 99;
			}
		}
		else if (_viBullet->count == 100 )
		{
				fire2(_viBullet->fireX, _viBullet->fireY, 0,0);
				_viBullet = _vBullet.erase(_viBullet);
				continue;
		}
		++_viBullet;
	}
}

void CmReturnBullet::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;

		if ((_viBullet2->count >= 0) && _viBullet2->count < 250 && !(_viBullet2->iscollison))
		{
			float omega = 0.02;

			_viBullet2->x += cosf(_viBullet2->angle += omega) * 2;
			_viBullet2->y -= sinf(_viBullet2->angle += omega) * 2;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());


		}
		else if (_viBullet2->count >= 250 || _viBullet2->iscollison)
		{

			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}


void CmReturnBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
void CmReturnBullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmWideBullet	    	몬스터총알	//////////////////
//////////////////////////////////////////////////////////////
CmWideBullet::CmWideBullet()
{
}

CmWideBullet::~CmWideBullet()
{
}

HRESULT CmWideBullet::init()
{

	return S_OK;
}

void CmWideBullet::release()
{
}

void CmWideBullet::update()
{
	move();
}

void CmWideBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmWideBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	Maxi = 13;
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < Maxi; i++)
		{
			ZeroMemory(&bullet, sizeof(tagBullet));
			bullet.bulletImage = new  image;
			bullet.bulletImage = IMAGE->addImage("작은몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 12, 12, true);
			bullet.angle = angle + 0.10 * (Maxi/2+1) - 0.10 * i;                                  
			bullet.speed = 3.0 -0.2*k;
			bullet.speed2 = 3.0;
			bullet.angle2 = angle;
			bullet.x = bullet.fireX = x;
			bullet.y = bullet.fireY = y;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y,                                   
				bullet.bulletImage->getWidth(),
				bullet.bulletImage->getHeight());
			bullet.count = 0;
			bullet.iscollison = false;
			bullet.isPlayerBullet = false;
			_vBullet.push_back(bullet);
		}
		if (Maxi > 10)
		{
			Maxi -= 2;
		}
		else
		{
			Maxi -= 4;
		}
	}
}

void CmWideBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{

		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;
			if (_viBullet->count >= 50 && !(_viBullet->iscollison))
			{
				_viBullet->angle = _viBullet->angle2;
				_viBullet->speed = _viBullet->speed2;
			}
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void CmWideBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmHomingBullet!	    	몬스터총알2	//////////////////
//////////////////////////////////////////////////////////////

CmHomingBullet::CmHomingBullet()
{
}

CmHomingBullet::~CmHomingBullet()
{
}

HRESULT CmHomingBullet::init()
{
	return S_OK;
}

void CmHomingBullet::release()
{
}

void CmHomingBullet::update()
{
	move();
}

void CmHomingBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangleRotate(_viBullet->rc, ZUNIT, _viBullet->angle + PI_2);
		ZORDER->ZorderRotateRender(_viBullet->bulletImage, ZUNIT, RotateRectBottom(_viBullet->rc, _viBullet->angle + PI_2),
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->angle + PI_2);
	}

}

void CmHomingBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;


	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	
	bullet.bulletImage = IMAGE->addImage("몬스터총알2", "images/bullet_bmp/MBullet_squar.bmp", 12  ,21  , true);
	bullet.angle = angle;
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);
}

void CmHomingBullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if ((_viBullet->count < 100) && !(_viBullet->iscollison))
		{
			_viBullet->x += cosf(_viBullet->angle) * 1;
			_viBullet->y -= sinf(_viBullet->angle) * 1;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;

		}
		else if (_viBullet->count >= 100 && _viBullet->count < 110)
		{
			_viBullet->angle = UTIL::getAngle(_viBullet->fireX, _viBullet->fireY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
			_viBullet->x += cosf(_viBullet->angle) * 4;
			_viBullet->y -= sinf(_viBullet->angle) * 4;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}
		else if (_viBullet->count >= 110 && !(_viBullet->iscollison))
		{
			_viBullet->x += cosf(_viBullet->angle) * 4;
			_viBullet->y -= sinf(_viBullet->angle) * 4;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void CmHomingBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmPoisonBullet!	    	독총알    !	//////////////////
//////////////////////////////////////////////////////////////
CmPoisonBullet::CmPoisonBullet()
{
}

CmPoisonBullet::~CmPoisonBullet()
{
}

HRESULT CmPoisonBullet::init()
{
	return S_OK;
}

void CmPoisonBullet::release()
{
}

void CmPoisonBullet::update()
{
	move();
}

void CmPoisonBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmPoisonBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	for (int i = 0; i < 6; i++)
	{

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGE->addImage("독총알", "images/bullet_bmp/poison.bmp", 40  , 40  , true);
		bullet.angle = 1.046 * i;
		bullet.angle2 = PI / 2 + 1.046 * i;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.iscollison = false;
		bullet.count = 0;

		_vBullet.push_back(bullet);
	}
	for (int i = 0; i < 6; i++)
	{

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGE->addImage("독총알", "images/bullet_bmp/poison.bmp", 40  , 40  , true);
		bullet.angle = 1.046 * i;
		bullet.angle2 = -PI / 2 + 1.046 * i;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.iscollison = false;
		bullet.count = 0;

		_vBullet.push_back(bullet);
	}
}

void CmPoisonBullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count < 100 && !(_viBullet->iscollison))
		{
			_viBullet->x += cosf(_viBullet->angle) * 1;
			_viBullet->y -= sinf(_viBullet->angle) * 1;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 100 && _viBullet->count < 150 && !(_viBullet->iscollison))
		{


			_viBullet->x += cosf(_viBullet->angle) * 0;
			_viBullet->y -= sinf(_viBullet->angle) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 150 && _viBullet->count < 180 && !(_viBullet->iscollison))
		{


			_viBullet->x += cosf(_viBullet->angle2) * 1;
			_viBullet->y -= sinf(_viBullet->angle2) * 1;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 180 && _viBullet->count < 300 && !(_viBullet->iscollison))
		{
			_viBullet->x += cosf(_viBullet->angle2) * 0;
			_viBullet->y -= sinf(_viBullet->angle2) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}

		else if (_viBullet->count >= 300 || _viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmPoisonBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//////////////////////////////////////////////////////////////
/////	CmNiddleBullet!	    	가시    !	//////////////////
//////////////////////////////////////////////////////////////


CmNiddleBullet::CmNiddleBullet()
{
}

CmNiddleBullet::~CmNiddleBullet()
{
}

HRESULT CmNiddleBullet::init()
{
	return S_OK;
}

void CmNiddleBullet::release()
{
}

void CmNiddleBullet::update()
{
	move();
	move2();
}

void CmNiddleBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		ZORDER->ZorderAlphaRender(_viBullet->bulletImage, ZCOL2, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
	}

	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet2->bulletImage2, ZUNIT, _viBullet2->rc.bottom,
			_viBullet2->rc.left, _viBullet2->rc.top);
		;
	}
}

void CmNiddleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("경고", "images/bullet_bmp/warning.bmp", 50  , 55  , true);
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;

	_vBullet.push_back(bullet);
}

void CmNiddleBullet::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;

	ZeroMemory(&bullet2, sizeof(tagBullet));
	bullet2.bulletImage2 = new  image;
	bullet2.bulletImage2 = IMAGE->addImage("가시", "images/bullet_bmp/niddle.bmp", 50, 55, true);
	bullet2.angle = angle;
	bullet2.x = bullet2.fireX = x;
	bullet2.y = bullet2.fireY = y;
	bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
		bullet2.bulletImage2->getWidth(),
		bullet2.bulletImage2->getHeight());
	bullet2.iscollison = false;
	bullet2.count = 50;

	_vBullet2.push_back(bullet2);
}

void CmNiddleBullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count > 0 && _viBullet->count < 50)
		{
			_viBullet->x += cosf(_viBullet->angle) * 0;
			_viBullet->y -= sinf(_viBullet->angle) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
		}
		else if (_viBullet->count == 50)
		{
			fire2(_viBullet->fireX, _viBullet->fireY, 0,  0);
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmNiddleBullet::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;
		if (_vBullet2.size() == 0)
		{
			_viBullet2->count = 0;
		}
		if (_viBullet2->count > 0 && _viBullet2->count < 200)
		{
			_viBullet2->x += cosf(_viBullet2->angle) * 0;
			_viBullet2->y -= sinf(_viBullet2->angle) * 0;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());
		}
		else if (_viBullet2->count >= 200)
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}

void CmNiddleBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CmNiddleBullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmLongPoisonBullet!			독총알 !//////////////////
//////////////////////////////////////////////////////////////

CmLongPoisonBullet::CmLongPoisonBullet()
{
}

CmLongPoisonBullet::~CmLongPoisonBullet()
{
}

HRESULT CmLongPoisonBullet::init()
{
	return S_OK;
}

void CmLongPoisonBullet::release()
{
}

void CmLongPoisonBullet::update()
{
	move();
}

void CmLongPoisonBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmLongPoisonBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	for (int i = 0; i < 6; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGE->addImage("독총알", "images/bullet_bmp/poison.bmp", 40, 40, true);
		bullet.angle = 1.046 * i;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.iscollison = false;
		bullet.count = 0;

		_vBullet.push_back(bullet);
	}
}

void CmLongPoisonBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;


	}
}

void CmLongPoisonBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmSBoss1Bullet!	 버블, 몬스터총알1 !//////////////////
//////////////////////////////////////////////////////////////
CmSBoss1Bullet::CmSBoss1Bullet()
{
}

CmSBoss1Bullet::~CmSBoss1Bullet()
{
}

HRESULT CmSBoss1Bullet::init()
{
	return S_OK;
}

void CmSBoss1Bullet::release()
{
}

void CmSBoss1Bullet::update()
{
	move();
	move2();
}

void CmSBoss1Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderAlphaRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if(_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet2->bulletImage2, ZUNIT, _viBullet2->rc.bottom,
			_viBullet2->rc.left, _viBullet2->rc.top);
	}
}

void CmSBoss1Bullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int k = 0; k < 6; k++)
	{
			ZeroMemory(&bullet, sizeof(tagBullet));
			bullet.bulletImage = new  image;
			bullet.bulletImage = IMAGE->addImage("버블", "images/bullet_bmp/bubble.bmp", 115  , 115  , true, RGB(255, 0, 255));
			
			bullet.angle2 = 1.049 * k;
			bullet.angle = 0.209;
			bullet.speed = 2.0f;
			bullet.alpha = 70;
			bullet.x = bullet.fireX = x;
			bullet.y = bullet.fireY = y;
			bullet.iscollison = false;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y,
				bullet.bulletImage->getWidth(),
				bullet.bulletImage->getHeight());
			bullet.count = 0;
			_vBullet.push_back(bullet);
		
	}
}

void CmSBoss1Bullet::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;
	for (int i = 0; i < 30; i++)
	{
		ZeroMemory(&bullet2, sizeof(tagBullet));
		bullet2.bulletImage2 = new image;
		bullet2.bulletImage2 = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));

		bullet2.angle2 = 1.049;
		bullet2.angle = 0.209 * i;
		bullet2.speed = 2.0f;
		bullet2.alpha = 255;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getWidth(),
			bullet2.bulletImage2->getHeight());
		bullet2.count = 100;

		_vBullet2.push_back(bullet2);
	}
}

void CmSBoss1Bullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{

		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count < 100)
		{
			_viBullet->x += cosf(_viBullet->angle2) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle2) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());

			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
			if (_viBullet->iscollison == true)
			{
				_viBullet->count = 99;
			}
		}
		else if ((_viBullet->count == 100))
		{
			fire2(_viBullet->fireX, _viBullet->fireY, 0, 0);
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmSBoss1Bullet::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;
		if (_vBullet2.size() == 0)
		{
			_viBullet2->count = 0;
		}
		if ((_viBullet2->count >= 100) && _viBullet2->count < 250 && !(_viBullet2->iscollison))
		{
			float omega = 0.02;

			_viBullet2->x += cosf(_viBullet2->angle += omega) * 2;
			_viBullet2->y -= sinf(_viBullet2->angle += omega) * 2;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());


		}
		else if (_viBullet2->count >= 250 || _viBullet2->iscollison)
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}


void CmSBoss1Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CmSBoss1Bullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmFBoss1Bullet!	 투명,경고,가시    !//////////////////
//////////////////////////////////////////////////////////////

CmFBoss1Bullet::CmFBoss1Bullet()
{
}

CmFBoss1Bullet::~CmFBoss1Bullet()
{
}

HRESULT CmFBoss1Bullet::init()
{
	return S_OK;
}

void CmFBoss1Bullet::release()
{
}

void CmFBoss1Bullet::update()
{
	move();
	move2();
	move3();
}

void CmFBoss1Bullet::render()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		ZORDER->ZorderAlphaRender(_viBullet2->bulletImage2, ZCOL2, _viBullet2->rc.bottom,
			_viBullet2->rc.left, _viBullet2->rc.top, _viBullet2->alpha);
	}

	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end(); ++_viBullet3)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet3->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet3->bulletImage3, ZUNIT, _viBullet3->rc.bottom,
			_viBullet3->rc.left, _viBullet3->rc.top);
	}

}

void CmFBoss1Bullet::fire(float x, float y,bool isleft, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 6; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("투명", "images/bullet_bmp/bubble.bmp", 50, 60 , true, RGB(255, 0, 255));
		bullet.angle = 1.046 * i;
		bullet.speed = 4.0;
		if (isleft)
		{
		bullet.omega = 0.007;
		}
		else
		{
		bullet.omega = -0.007;
		}
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.iscollison = false;
		bullet.count = 00;

		_vBullet.push_back(bullet);
	}
}

void CmFBoss1Bullet::fire2(float x, float y, int plussize)
{
	tagBullet bullet2;

		ZeroMemory(&bullet2, sizeof(tagBullet));
		bullet2.bulletImage2 = new  image;
		bullet2.bulletImage2 = IMAGE->addImage("경고", "images/bullet_bmp/warning.bmp", 50 , 55 , true, RGB(255, 0, 255));

		bullet2.angle = 0;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.alpha = 40;
		bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getWidth(),
			bullet2.bulletImage2->getHeight());
		bullet2.count = 0;

		_vBullet2.push_back(bullet2);
	
}

void CmFBoss1Bullet::fire3(float x, float y, int plussize)
{
	tagBullet bullet3;
	
		ZeroMemory(&bullet3, sizeof(tagBullet));
		bullet3.bulletImage3 = new  image;
		bullet3.bulletImage3 = IMAGE->addImage("가시", "images/bullet_bmp/niddle.bmp", 50 , 55 , true, RGB(255, 0, 255));
		bullet3.angle = PI / 2;
		bullet3.x = bullet3.fireX = x;
		bullet3.y = bullet3.fireY = y;
		bullet3.rc = RectMakeCenter(bullet3.x, bullet3.y,
			bullet3.bulletImage3->getWidth(),
			bullet3.bulletImage3->getHeight());
		bullet3.count = 50;

		_vBullet3.push_back(bullet3);
	
}

void CmFBoss1Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count >= 0 && !(_viBullet->iscollison))
		{
			
			_viBullet->x += cosf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
			if (_viBullet->count % 15 == 0)
			{
				fire2(_viBullet->fireX, _viBullet->fireY,0);
			}
			if (_viBullet->iscollison)
			{
				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}
	}
}

void CmFBoss1Bullet::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;
		if (_vBullet2.size() == 0)
		{
			_viBullet2->count = 0;
		}
		if (_viBullet2->count > 0 && _viBullet2->count < 50)
		{
			_viBullet2->x += cosf(_viBullet2->angle) * 0;
			_viBullet2->y -= sinf(_viBullet2->angle) * 0;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());
			_viBullet2->fireX = _viBullet2->x;
			_viBullet2->fireY = _viBullet2->y;
		}
		else if (_viBullet2->count == 50)
		{
			fire3(_viBullet2->fireX, _viBullet2->fireY, 0);
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}

void CmFBoss1Bullet::move3()
{
	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end();)
	{
		_viBullet3->count++;
		if (_vBullet3.size() == 0)
		{
			_viBullet3->count = 0;
		}
		if (_viBullet3->count > 0 && _viBullet3->count < 200)
		{
			_viBullet3->x += cosf(_viBullet3->angle) * 0;
			_viBullet3->y -= sinf(_viBullet3->angle) * 0;

			_viBullet3->rc = RectMakeCenter(_viBullet3->x, _viBullet3->y,
				_viBullet3->bulletImage3->getWidth(),
				_viBullet3->bulletImage3->getHeight());
		}
		else if (_viBullet3->count >= 200)
		{
			_viBullet3 = _vBullet3.erase(_viBullet3);
			continue;
		}
		++_viBullet3;
	}
}

void CmFBoss1Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CmFBoss1Bullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

void CmFBoss1Bullet::removeBullet3(int arrNum)
{
	_vBullet3.erase(_vBullet3.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmFBoss2Bullet!	 경고,가시    !//////////////////
//////////////////////////////////////////////////////////////
CmFBoss2Bullet::CmFBoss2Bullet()
{
}

CmFBoss2Bullet::~CmFBoss2Bullet()
{
}

HRESULT CmFBoss2Bullet::init()
{
	return S_OK;
}

void CmFBoss2Bullet::release()
{
}

void CmFBoss2Bullet::update()
{
	move();
	move2();
	
}

void CmFBoss2Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire)
		{
			ZORDER->ZorderAlphaRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
				_viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
		}
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet2->bulletImage2, ZUNIT, _viBullet2->rc.bottom,
			_viBullet2->rc.left, _viBullet2->rc.top);
		;
	}
}

void CmFBoss2Bullet::fire(float x, float y, int maxSize)
{
	tagBullet bullet;
	
	for (int i = 0; i < maxSize; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("경고", "images/bullet_bmp/warning.bmp", 50, 55, true, RGB(255, 0, 255));
		bullet.angle = PI * 2 / maxSize * i;
		bullet.speed = 0.4 * maxSize;;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.fire = false;
		bullet.alpha = 160;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.count = 0;

		_vBullet.push_back(bullet);

	}
}

void CmFBoss2Bullet::fire2(float x, float y, int plussize)
{
	tagBullet bullet2;

	ZeroMemory(&bullet2, sizeof(tagBullet));
	bullet2.bulletImage2 = new  image;
		bullet2.bulletImage2 = IMAGE->addImage("가시", "images/bullet_bmp/niddle.bmp", 50, 55, true, RGB(255, 0, 255));

		bullet2.angle = PI / 2;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getWidth(),
			bullet2.bulletImage2->getHeight());
		bullet2.count = 50;

		_vBullet2.push_back(bullet2);

}


void CmFBoss2Bullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count > 0 && _viBullet->count < 20)
		{

			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
		}
		if (_viBullet->count == 20)
		{
			_viBullet->speed = 0;
			_viBullet->fire = true;
		}
		else if (_viBullet->count == 80)
		{
			fire2(_viBullet->fireX, _viBullet->fireY, 0);
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmFBoss2Bullet::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;
		if (_vBullet2.size() == 0)
		{
			_viBullet2->count = 0;
		}
		if (_viBullet2->count > 0 && _viBullet2->count < 130)
		{
			_viBullet2->x += cosf(_viBullet2->angle) * 0;
			_viBullet2->y -= sinf(_viBullet2->angle) * 0;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());
		}
		else if (_viBullet2->count > 130)
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}



void CmFBoss2Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CmFBoss2Bullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

//////////////////////////////////////////////////////////////
/////	CmFBoss3Bullet!		 몬스터총알    !//////////////////
//////////////////////////////////////////////////////////////
CmFBoss3Bullet::CmFBoss3Bullet()
{
}

CmFBoss3Bullet::~CmFBoss3Bullet()
{
}

HRESULT CmFBoss3Bullet::init()
{
	return S_OK;
}

void CmFBoss3Bullet::release()
{
}

void CmFBoss3Bullet::update()
{
	move();
}

void CmFBoss3Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderAlphaRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
	}
}

void CmFBoss3Bullet::fire(float x, float y, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 0;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 0 + 1.046;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 2.092;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 3.138;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 4.184;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 5.23;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 0;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 0 + 1.046;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 2.092;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 3.138;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 4.184;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = 0.01;
	bullet.angle = 5.23;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 0;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 0 + 1.046;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 2.092;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x + 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 3.138;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y - 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 4.184;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 80;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.omega = -0.01;
	bullet.angle = 5.23;
	bullet.speed = 2;
	bullet.x = bullet.fireX = x - 50;
	bullet.y = bullet.fireY = y + 50;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.count = 0;
	_vBullet.push_back(bullet);

	
}

void CmFBoss3Bullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count >= 0 && _viBullet->count < 300 && !(_viBullet->iscollison))
		{
			_viBullet->x -= 2 * cosf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;
			_viBullet->y += 2 * sinf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}
		else if (_viBullet->count >= 300 || _viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;

	}
}

void CmFBoss3Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmTBoss1Bullet!		 브레스	       !//////////////////
//////////////////////////////////////////////////////////////
CmTBoss1Bullet::CmTBoss1Bullet()
{
}

CmTBoss1Bullet::~CmTBoss1Bullet()
{
}

HRESULT CmTBoss1Bullet::init()
{
	return S_OK;
}

void CmTBoss1Bullet::release()
{
}

void CmTBoss1Bullet::update()
{
	move();
}

void CmTBoss1Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderAlphaRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
	}
}

void CmTBoss1Bullet::fire(float x, float y, float angle, bool isLeft, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("나무브레스", "images/bullet_bmp/entskill.bmp", 96, 98, true, RGB(255, 0, 255));
	if (isLeft)
	{
		bullet.omega = 0.003;
	}
	else
	{
		bullet.omega = -0.003;
	}
	bullet.angle = angle;
	bullet.speed = 4;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.fire = false;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.count = 0;
	bullet.iscollison = false;
	_vBullet.push_back(bullet);

}

void CmTBoss1Bullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count >= 0 && _viBullet->count < 300 && !(_viBullet->iscollison))
		{
			_viBullet->x -= cosf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;
			_viBullet->y += sinf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}
		else if (_viBullet->count >= 300 || _viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmTBoss1Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmTBoss2Bullet!		나무보스총알   !//////////////////
//////////////////////////////////////////////////////////////
CmTBoss2Bullet::CmTBoss2Bullet()
{
}

CmTBoss2Bullet::~CmTBoss2Bullet()
{
}

HRESULT CmTBoss2Bullet::init()
{
	return S_OK;
}

void CmTBoss2Bullet::release()
{
}

void CmTBoss2Bullet::update()
{
	move();
}

void CmTBoss2Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		//_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->x - _viBullet->bulletImage->getFrameWidth()/2, _viBullet->y - _viBullet->bulletImage->getFrameHeight()/2, _viBullet->bulletImage->getFrameX(), 0);
		ZORDER->ZorderFrameRender(_viBullet->bulletImage, ZUNIT, _viBullet->y + _viBullet->bulletImage->getFrameHeight() / 2,
			_viBullet->x - _viBullet->bulletImage->getFrameWidth() / 2,
			_viBullet->y - _viBullet->bulletImage->getFrameHeight() / 2,
			_viBullet->bulletImage->getFrameX(), 0);
		_viBullet->rendercount++;

		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL3);

		if (_viBullet->rendercount % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->rendercount = 0;
		}
	}
}

void CmTBoss2Bullet::fire(float x, float y, float angle, bool isLeft, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addFrameImage("나무보스총알", "images/bullet_bmp/TBossBullet.bmp", 400, 48, 8, 1, true, RGB(255, 0, 255));
		if (isLeft)
		{
			bullet.omega = 0.0005;
		}
		bullet.angle = angle - 0.3 + 0.3 * i;
		bullet.speed = 4;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.fire = false;
		bullet.alpha = 160;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getFrameWidth()/2,
			bullet.bulletImage->getFrameHeight()/2);
		bullet.rendercount = 0;
		bullet.iscollison = false;
		bullet.count = 0;
		_vBullet.push_back(bullet);
	}
}

void CmTBoss2Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle += _viBullet->omega) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth()/2,
			_viBullet->bulletImage->getFrameHeight()/2);

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void CmTBoss2Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

CmTBoss3Bullet::CmTBoss3Bullet()
{
}

CmTBoss3Bullet::~CmTBoss3Bullet()
{
}

HRESULT CmTBoss3Bullet::init()
{
	return S_OK;
}

void CmTBoss3Bullet::release()
{
}

void CmTBoss3Bullet::update()
{
	move();
}

void CmTBoss3Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmTBoss3Bullet::fire(float x, float y, float angle, bool isLeft, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("몬스터총알", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet.angle2 = PI / 2 / 2 * RND->getFromInTo(0, 16);
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.count = 0;
	bullet.iscollison = false;
	_vBullet.push_back(bullet);
}

void CmTBoss3Bullet::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count < 100)
		{
			_viBullet->x += cosf(_viBullet->angle2) *0;
			_viBullet->y -= sinf(_viBullet->angle2) *0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getFrameWidth(),
				_viBullet->bulletImage->getFrameHeight());
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
		}
		else ++_viBullet;
	}
}

void CmTBoss3Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

CpSword::CpSword()
{
}

CpSword::~CpSword()
{
}

HRESULT CpSword::init()
{
	return S_OK;
}

void CpSword::release()
{
}

void CpSword::update()
{
	move();
	move2();
	move3();
}

void CpSword::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet->bulletImage, ZMAXLAYER, 1200, RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->angle-PI);
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet2->bulletImage2, ZMAXLAYER, 1200, RecCenX(_viBullet2->rc), RecCenY(_viBullet2->rc), _viBullet2->angle - PI/2);
	}
	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end(); ++_viBullet3)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet3->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet3->bulletImage3, ZMAXLAYER, 1200, RecCenX(_viBullet3->rc), RecCenY(_viBullet3->rc), _viBullet3->angle - PI/2);
	}
}

void CpSword::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("검1", "images/bullet_bmp/sword1.bmp", 192,192,true,RGB(255,0,255));
	bullet.angle = angle;
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.iscollison = false;
	bullet.isPlayerBullet = true;
	_vBullet.push_back(bullet);
}

void CpSword::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage2 = new  image;
	bullet.bulletImage2 = IMAGE->addImage("검2", "images/bullet_bmp/sword2.bmp", 192, 192, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage2->getWidth(),
		bullet.bulletImage2->getHeight());
	bullet.iscollison = false;
	bullet.isPlayerBullet = true;
	_vBullet2.push_back(bullet);
}

void CpSword::fire3(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage3 = new  image;
	bullet.bulletImage3 = IMAGE->addImage("검3", "images/bullet_bmp/sword3.bmp", 192, 192,true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage3->getWidth(),
		bullet.bulletImage3->getHeight());
	bullet.iscollison = false;
	bullet.isPlayerBullet = true;
	_vBullet3.push_back(bullet);
}

void CpSword::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count > 0 && _viBullet->count <10)
		{
			_viBullet->x += cosf(_viBullet->angle) * 0;
			_viBullet->y -= sinf(_viBullet->angle) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
		}
		else if (_viBullet->count ==10)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CpSword::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;
		if (_vBullet2.size() == 0)
		{
			_viBullet2->count = 0;
		}
		if (_viBullet2->count > 0 && _viBullet2->count < 10)
		{
			_viBullet2->x += cosf(_viBullet2->angle) * 0;
			_viBullet2->y -= sinf(_viBullet2->angle) * 0;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());
			_viBullet2->fireX = _viBullet2->x;
			_viBullet2->fireY = _viBullet2->y;
		}
		else if (_viBullet2->count == 10)
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}

void CpSword::move3()
{
	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end();)
	{
		_viBullet3->count++;
		if (_vBullet3.size() == 0)
		{
			_viBullet3->count = 0;
		}
		if (_viBullet3->count > 0 && _viBullet3->count < 10)
		{
			_viBullet3->x += cosf(_viBullet3->angle) * 0;
			_viBullet3->y -= sinf(_viBullet3->angle) * 0;

			_viBullet3->rc = RectMakeCenter(_viBullet3->x, _viBullet3->y,
				_viBullet3->bulletImage3->getWidth(),
				_viBullet3->bulletImage3->getHeight());
			_viBullet3->fireX = _viBullet3->x;
			_viBullet3->fireY = _viBullet3->y;
		}
		else if (_viBullet3->count == 10)
		{
			_viBullet3 = _vBullet3.erase(_viBullet3);
			continue;
		}
		++_viBullet3;
	}
}

void CpSword::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CpSword::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

void CpSword::removeBullet3(int arrNum)
{
	_vBullet3.erase(_vBullet3.begin() + arrNum);
}

CpSkil_LuckyStar::CpSkil_LuckyStar()
{
}

CpSkil_LuckyStar::~CpSkil_LuckyStar()
{
}

HRESULT CpSkil_LuckyStar::init()
{

	return S_OK;
}

void CpSkil_LuckyStar::release()
{
}

void CpSkil_LuckyStar::update()
{
	move();
}

void CpSkil_LuckyStar::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug)
			ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderStretchRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->plussize);
	}
}

void CpSkil_LuckyStar::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 5; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("별총알", "images/bullet_bmp/skill_ms_star.bmp",12,12, true);
		bullet.plussize = 1 + (double)plussize / bullet.bulletImage->getWidth();
		bullet.angle = angle - 0.4 + 0.2 * i;
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth() + plussize,
			bullet.bulletImage->getHeight() + plussize);
		bullet.iscollison = false;
		bullet.isPlayerBullet = false;
		_vBullet.push_back(bullet);
	}
}


void CpSkil_LuckyStar::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->iscollison)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void CpSkil_LuckyStar::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

CpSkil_Ice_spear::CpSkil_Ice_spear()
{
}

CpSkil_Ice_spear::~CpSkil_Ice_spear()
{
}

HRESULT CpSkil_Ice_spear::init()
{
	return S_OK;
}

void CpSkil_Ice_spear::release()
{
}

void CpSkil_Ice_spear::update()
{
	move();
	move2();
}

void CpSkil_Ice_spear::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderRotateRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom,
			RecCenX(_viBullet->rc), RecCenY(_viBullet->rc), _viBullet->angle);
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet2->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viBullet2->bulletImage2, ZUNIT, _viBullet2->rc.bottom,_viBullet2->rc.left, _viBullet2->rc.top, _viBullet2->bulletAni);
	}
}

void CpSkil_Ice_spear::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("얼음화살", "images/bullet_bmp/ice.bmp", 61, 21, true);
	bullet.angle2 = angle;
	bullet.angle = angle;
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.iscollison = false;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.count = 0;
	bullet.isPlayerBullet = false;
	_vBullet.push_back(bullet);
}
void CpSkil_Ice_spear::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;
		ZeroMemory(&bullet2, sizeof(tagBullet));
		bullet2.bulletImage2 = new  image;
		bullet2.bulletImage2 = IMAGE->addFrameImage("얼음폭발", "images/bullet_bmp/sk_iceSpear.bmp",800, 640,5,4, true, RGB(255, 0, 255));
		bullet2.bulletAni = new animation;
		bullet2.bulletAni = ANIMATION->addNoneKeyAnimation("얼음폭발", 20, false, true);
		bullet2.angle2 = 1.049;
		bullet2.angle = 0;
		bullet2.speed = 2.0f;
		bullet2.alpha = 255;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.rc = RectMake(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getFrameWidth(),
			bullet2.bulletImage2->getFrameHeight()-20);
		bullet2.iscollison = false;
		bullet2.count = 100;

		_vBullet2.push_back(bullet2);
}
void CpSkil_Ice_spear::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;
		if (_vBullet.size() == 0)
		{
			_viBullet->count = 0;
		}
		if (_viBullet->count < 100)
		{
			_viBullet->x += cosf(_viBullet->angle2) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle2) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());

			_viBullet->fireX = _viBullet->x;
			_viBullet->fireY = _viBullet->y;
			if (_viBullet->iscollison)
			{
				_viBullet->count = 99;
			}
		}
		else if (_viBullet->count == 100)
		{
			fire2(_viBullet->fireX, _viBullet->fireY, 0, 0);
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}
void CpSkil_Ice_spear::move2()
{
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->count++;

		if ((_viBullet2->count >= 0) && _viBullet2->count < 250 )
		{
			_viBullet2->x += cosf(_viBullet2->angle2) * 0;
			_viBullet2->y -= sinf(_viBullet2->angle2) * 0;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getFrameWidth(),
				_viBullet2->bulletImage2->getFrameHeight() - 20);
		}
		else if (_viBullet2->count >= 250)
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
			continue;
		}
		++_viBullet2;
	}
}
void CpSkil_Ice_spear::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
void CpSkil_Ice_spear::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}

CpSkil_Haste::CpSkil_Haste()
{
}

CpSkil_Haste::~CpSkil_Haste()
{
}

HRESULT CpSkil_Haste::init()
{
	return S_OK;
}

void CpSkil_Haste::release()
{
}

void CpSkil_Haste::update()
{
	move();
}

void CpSkil_Haste::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viBullet->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viBullet->bulletImage, ZUNIT, _viBullet->rc.bottom, _viBullet->rc.left, _viBullet->rc.top, _viBullet->bulletAni);
	}
}

void CpSkil_Haste::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addFrameImage("헤이스트", "images/bullet_bmp/sk_haste.bmp", 960,1536, 5, 8, true, RGB(255, 0, 255));
	bullet.bulletAni = new animation;
	bullet.bulletAni = ANIMATION->addNoneKeyAnimation("헤이스트", 50, false, true);
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y-40,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());
	bullet.iscollison = false;
	bullet.count = 100;

	_vBullet.push_back(bullet);
}


void CpSkil_Haste::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end();)
	{
		_viBullet->count++;

		if ((_viBullet->count >= 0) && _viBullet->count < 150)
		{
			_viBullet->x += cosf(_viBullet->angle) * 0;
			_viBullet->y -= sinf(_viBullet->angle) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y - 40,
				_viBullet->bulletImage->getFrameWidth(),
				_viBullet->bulletImage->getFrameHeight() - 20);
		}
		else if (_viBullet->count >=150)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}


void CpSkil_Haste::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

