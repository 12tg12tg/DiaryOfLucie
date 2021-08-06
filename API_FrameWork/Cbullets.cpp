#include "framework.h"
#include "Cbullets.h"
#include "Cplayer.h"
/*
=================================================
	Find bullet class ctrl+F4 ("name!")
=================================================
	bulletname			imagename
1.	CpMagicBullet	/	¸¶¹ýÃÑ¾Ë
2.	CpArrowBullet	/	È­»ì
3.	CmTripleBullet	/	¸ó½ºÅÍÃÑ¾Ë
4.	CmCircleBulelt	/	¸ó½ºÅÍÃÑ¾Ë
5.	CmReturnBullet  /   Æä¾î¸®ÃÑ¾Ë1 , Æä¾î¸®ÃÑ¾Ë2
6.	CmWideBullet	/	¸ó½ºÅÍÃÑ¾Ë
7.	CmHomingBullet	/   ¸ó½ºÅÍÃÑ¾Ë2
8.	CmPoisonBullet /	µ¶ÃÑ¾Ë
9.	CmNiddleBullet /	°¡½Ã , °æ°í
10.	CmSBoss1Bullet /	¹öºí , ¸ó½ºÅÍÃÑ¾Ë1
11.	
*/
//////////////////////////////////////////////////////////////
/////	CpMagicBullet!	    	¸¶¹ýÃÑ¾Ë!	//////////////////
//////////////////////////////////////////////////////////////
CpMagicBullet::CpMagicBullet()
{
}

CpMagicBullet::~CpMagicBullet()
{
}

HRESULT CpMagicBullet::init()
{
	_range = 25.0f; //ÀÓ½Ã
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}
void CpMagicBullet::fire(float x, float y, float angle,int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("¸¶¹ýÃÑ¾Ë", "images/bullet_bmp/PBullet_magic.bmp", 26 , 26  , true);
	bullet.angle = angle;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
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

		if (_range < UTIL::getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
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
/////	CpMagicBullet!	    	È­»ì    !	//////////////////
//////////////////////////////////////////////////////////////

CpArrowBullet::CpArrowBullet()
{
}

CpArrowBullet::~CpArrowBullet()
{
}

HRESULT CpArrowBullet::init()
{
	_range = 3.0f; //ÀÓ½Ã
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
		_viBullet->bulletImage->rotateRender(getMemDC(), _viBullet->rc.right - (_viBullet->rc.right - _viBullet->rc.left) / 2, _viBullet->rc.bottom - (_viBullet->rc.bottom - _viBullet->rc.top) / 2, _viBullet->rotateangle);
	}
}

void CpArrowBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("È­»ì", "images/bullet_bmp/PBullet_arrow.bmp", 26  , 8  , true);
	bullet.angle = angle;
	bullet.rotateangle = angle + PI/2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
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

		if (_range < UTIL::getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
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
/////	CmTripleBullet	    	¸ó½ºÅÍÃÑ¾Ë	//////////////////
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,_viBullet->plussize);

	}
}

void CmTripleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.plussize = plussize;
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 12 , 12, true);
		bullet.angle = angle - 0.2 + 0.2 * i;
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth()+plussize,
			bullet.bulletImage->getHeight()+plussize);
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

		if (_viBullet->x < 0 || _viBullet->x > WINSIZEX || _viBullet->y <0 || _viBullet->y > WINSIZEY)
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
/////	CmCircleBullet	    	¸ó½ºÅÍÃÑ¾Ë	//////////////////
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmCircleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 12  , 12  , true);
		bullet.angle = angle + 0.628 * i;
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.isPlayerBullet = false;
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

		if (_viBullet->x < 0 || _viBullet->x > WINSIZEX || _viBullet->y <0 || _viBullet->y > WINSIZEY)
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
/////	CmReturnBullet Æä¾î¸®ÃÑ¾Ë1 Æä¾î¸®ÃÑ¾Ë2////////////////
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
		_viBullet->bulletImage->rotateRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->angle += 0.05 );
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		_viBullet2->bulletImage2->render(getMemDC(), _viBullet2->rc.left, _viBullet2->rc.top);
	}
}

void CmReturnBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("Æä¾î¸®ÃÑ¾Ë1", "images/bullet_bmp/fairy_bullet1.bmp", 20 , 20  , true);
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
		bullet2.bulletImage2 = IMAGE->addImage("Æä¾î¸®ÃÑ¾Ë2", "images/bullet_bmp/fairy_bullet2.bmp", 15 , 13 , true, RGB(255, 0, 255));

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
		}
		else if (_viBullet->count == 100 || _viBullet->iscollison)
		{
			fire2(_viBullet->fireX, _viBullet->fireY, UTIL::getAngle(WINSIZEX / 2, WINSIZEY / 2, m_ptMouse.x, m_ptMouse.y),  0);
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

		if ((_viBullet2->count >= 0) && _viBullet2->count < 250)
		{
			float omega = 0.02;

			_viBullet2->x += cosf(_viBullet2->angle += omega) * 2;
			_viBullet2->y -= sinf(_viBullet2->angle += omega) * 2;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());


		}
		else if (_viBullet2->count >= 250)
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
	_vBullet2.erase(_vBullet.begin() + arrNum);
}
//////////////////////////////////////////////////////////////
/////	CmWideBullet	    	¸ó½ºÅÍÃÑ¾Ë	//////////////////
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
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
			bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 12, 12, true);
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
			if (_viBullet->count >= 50)
			{
				_viBullet->angle = _viBullet->angle2;
				_viBullet->speed = _viBullet->speed2;
			}
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		if (_viBullet->x < 0 || _viBullet->x > WINSIZEX || _viBullet->y <0 || _viBullet->y > WINSIZEY)
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
/////	CmHomingBullet!	    	¸ó½ºÅÍÃÑ¾Ë2	//////////////////
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
		_viBullet->bulletImage->rotateRender(getMemDC(), _viBullet->rc.right - (_viBullet->rc.right - _viBullet->rc.left) / 2, _viBullet->rc.bottom - (_viBullet->rc.bottom - _viBullet->rc.top) / 2, _viBullet->angle + PI/2);
		if (_isDebug)
		{
		
			if (_isDebug) RectangleMake(getMemDC(), _viBullet->rc);
			_viBullet->bulletImage->rotateRender(getMemDC(), _viBullet->rc.right - (_viBullet->rc.right - _viBullet->rc.left) / 2, _viBullet->rc.bottom - (_viBullet->rc.bottom - _viBullet->rc.top) / 2, _viBullet->angle + PI / 2);
		}
	}

}

void CmHomingBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;


	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	
	bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë2", "images/bullet_bmp/MBullet_squar.bmp", 12  ,21  , true);
	bullet.angle = angle;
	bullet.rotateangle = angle + PI / 2;
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
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
		if (_viBullet->count < 100)
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
		else if (_viBullet->count >= 110)
		{
			_viBullet->x += cosf(_viBullet->angle) * 4;
			_viBullet->y -= sinf(_viBullet->angle) * 4;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}

		if (_viBullet->x < 0 || _viBullet->x > WINSIZEX || _viBullet->y <0 || _viBullet->y > WINSIZEY)
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
/////	CmPoisonBullet!	    	µ¶ÃÑ¾Ë    !	//////////////////
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmPoisonBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	for (int i = 0; i < 6; i++)
	{

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGE->addImage("µ¶ÃÑ¾Ë", "images/bullet_bmp/poison.bmp", 40  , 40  , true);
		bullet.angle = 1.046 * i;
		bullet.angle2 = PI / 2 + 1.046 * i;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.count = 0;

		_vBullet.push_back(bullet);
	}
	for (int i = 0; i < 6; i++)
	{

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGE->addImage("µ¶ÃÑ¾Ë", "images/bullet_bmp/poison.bmp", 40  , 40  , true);
		bullet.angle = 1.046 * i;
		bullet.angle2 = -PI / 2 + 1.046 * i;
		bullet.speed = 2.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
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
		if (_viBullet->count < 100)
		{
			_viBullet->x += cosf(_viBullet->angle) * 1;
			_viBullet->y -= sinf(_viBullet->angle) * 1;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 100 && _viBullet->count < 150)
		{


			_viBullet->x += cosf(_viBullet->angle) * 0;
			_viBullet->y -= sinf(_viBullet->angle) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 150 && _viBullet->count < 180)
		{


			_viBullet->x += cosf(_viBullet->angle2) * 1;
			_viBullet->y -= sinf(_viBullet->angle2) * 1;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 180 && _viBullet->count < 300)
		{


			_viBullet->x += cosf(_viBullet->angle2) * 0;
			_viBullet->y -= sinf(_viBullet->angle2) * 0;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());


		}
		else if (_viBullet->count >= 300)
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
/////	CmWarningBullet!			 °æ°í!	//////////////////
//////////////////////////////////////////////////////////////
CmWarningBullet::CmWarningBullet()
{
}

CmWarningBullet::~CmWarningBullet()
{
}

HRESULT CmWarningBullet::init()
{
	return S_OK;
}

void CmWarningBullet::release()
{
}

void CmWarningBullet::update()
{
	move();
}

void CmWarningBullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->alphaRender(getMemDC(), _viBullet->rc.right - (_viBullet->rc.right - _viBullet->rc.left) / 2, _viBullet->rc.bottom - (_viBullet->rc.bottom - _viBullet->rc.top) / 2, 30);
	}
}

void CmWarningBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("°æ°í", "images/bullet_bmp/warning.bmp", 81  , 61  , true);
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.count = 0;

	_vBullet.push_back(bullet);
}

void CmWarningBullet::move()
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
		}
		else if (_viBullet->count >= 50)
		{
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
	}
}

void CmWarningBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//////////////////////////////////////////////////////////////
/////	CmNiddleBullet!	    	°¡½Ã    !	//////////////////
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
		_viBullet->bulletImage->alphaRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);

	}

	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		_viBullet2->bulletImage2->render(getMemDC(), _viBullet2->rc.left, _viBullet2->rc.top);
		;
	}
}

void CmNiddleBullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("°æ°í", "images/bullet_bmp/warning.bmp", 50  , 55  , true);
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.alpha = 160;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.count = 0;

	_vBullet.push_back(bullet);
}

void CmNiddleBullet::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;

	ZeroMemory(&bullet2, sizeof(tagBullet));
	bullet2.bulletImage2 = new  image;
	bullet2.bulletImage2 = IMAGE->addImage("°¡½Ã", "images/bullet_bmp/niddle.bmp", 50, 55, true);
	bullet2.angle = angle;
	bullet2.x = bullet2.fireX = x;
	bullet2.y = bullet2.fireY = y;
	bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
		bullet2.bulletImage2->getWidth(),
		bullet2.bulletImage2->getHeight());
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
			fire2(_viBullet->fireX, _viBullet->fireY, UTIL::getAngle(WINSIZEX / 2, WINSIZEY / 2, m_ptMouse.x, m_ptMouse.y),  0);
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
/////	CmSBoss1Bullet!	 ¹öºí, ¸ó½ºÅÍÃÑ¾Ë1 !//////////////////
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
		_viBullet->bulletImage->alphaRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);
	}
	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		_viBullet2->bulletImage2->render(getMemDC(), _viBullet2->rc.left, _viBullet2->rc.top);
	}
}

void CmSBoss1Bullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int k = 0; k < 6; k++)
	{
			ZeroMemory(&bullet, sizeof(tagBullet));
			bullet.bulletImage = new  image;
			bullet.bulletImage = IMAGE->addImage("¹öºí", "images/bullet_bmp/bubble.bmp", 115  , 115  , true, RGB(255, 0, 255));
			
			bullet.angle2 = 1.049 * k;
			bullet.angle = 0.209;
			bullet.speed = 2.0f;
			bullet.alpha = 70;
			bullet.x = bullet.fireX = x;
			bullet.y = bullet.fireY = y;
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
		bullet2.bulletImage2 = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 20, 20, true, RGB(255, 0, 255));

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
		}
		else if ((_viBullet->count == 100) || _viBullet->iscollison)
		{
			fire2(_viBullet->fireX, _viBullet->fireY, UTIL::getAngle(WINSIZEX / 2, WINSIZEY / 2, m_ptMouse.x, m_ptMouse.y), 0);
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
		if ((_viBullet2->count >= 100) && _viBullet2->count < 250)
		{
			float omega = 0.02;

			_viBullet2->x += cosf(_viBullet2->angle += omega) * 2;
			_viBullet2->y -= sinf(_viBullet2->angle += omega) * 2;

			_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y,
				_viBullet2->bulletImage2->getWidth(),
				_viBullet2->bulletImage2->getHeight());


		}
		else if (_viBullet2->count >= 250)
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
}

void CmFBoss1Bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->alphaRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->alpha);

	}

	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		_viBullet2->bulletImage2->render(getMemDC(), _viBullet2->rc.left, _viBullet2->rc.top);
		;
	}
}

void CmFBoss1Bullet::fire(float x, float y, float angle, int plussize)
{
	tagBullet bullet;
	for (int k = 0; k < 6; k++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/warning.bmp", 50 + plussize, 55 + plussize, true, RGB(255, 0, 255));

		bullet.angle = angle;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.alpha = 40;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
		bullet.count = 0;

		_vBullet.push_back(bullet);
	}
}

void CmFBoss1Bullet::fire2(float x, float y, float angle, int plussize)
{
	tagBullet bullet2;
	for (int i = 0; i < 30; i++)
	{
		ZeroMemory(&bullet2, sizeof(tagBullet));
		bullet2.bulletImage2 = new  image;
		bullet2.bulletImage2 = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë2", "images/flower_skill.bmp", 50 + plussize, 55 + plussize, true, RGB(255, 0, 255));
		bullet2.angle = PI / 2;
		bullet2.x = bullet2.fireX = x;
		bullet2.y = bullet2.fireY = y;
		bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y,
			bullet2.bulletImage2->getWidth(),
			bullet2.bulletImage2->getHeight());
		bullet2.count = 50;

		_vBullet2.push_back(bullet2);
	}
}

void CmFBoss1Bullet::move()
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
			fire2(_viBullet->fireX, _viBullet->fireY, UTIL::getAngle(WINSIZEX / 2, WINSIZEY / 2, m_ptMouse.x, m_ptMouse.y), 0);
			_viBullet = _vBullet.erase(_viBullet);
			continue;
		}
		++_viBullet;
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

void CmFBoss1Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void CmFBoss1Bullet::removeBullet2(int arrNum)
{
	_vBullet2.erase(_vBullet2.begin() + arrNum);
}
