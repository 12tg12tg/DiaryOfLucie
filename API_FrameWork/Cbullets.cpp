#include "framework.h"
#include "Cbullets.h"
/*
=================================================
	Find bullet class ctrl+F4 ("name!")
=================================================
	bulletname			imagename
1.	CpMagicBullet	/	¸¶¹ýÃÑ¾Ë
2.	CpArrowBullet	/	È­»ì
3.	CmTripleBullet	/	¸ó½ºÅÍÃÑ¾Ë
4.	CmCircleBulelt	/	¸ó½ºÅÍÃÑ¾Ë
5.					/
6.					/
7.					/
8.					/
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
void CpMagicBullet::fire(float x, float y, float angle)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("¸¶¹ýÃÑ¾Ë", "images/bullet_bmp/PBullet_magic.bmp", 26, 26, true);
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void CpArrowBullet::fire(float x, float y, float angle)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new  image;
	bullet.bulletImage = IMAGE->addImage("È­»ì", "images/bullet_bmp/PBullet_arrow.bmp", 26, 8, true);
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
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void CmTripleBullet::fire(float x, float y, float angle)
{
	tagBullet bullet;
	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 26, 8, true);
		bullet.angle = angle -0.2 + 0.2 * i;
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

void CmTripleBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_viBullet->x < 0  && _viBullet->x > WINSIZEX && _viBullet->y <0 && _viBullet->y > WINSIZEY)
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

void CmCircleBullet::fire(float x, float y, float angle)
{
	tagBullet bullet;
	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new  image;
		bullet.bulletImage = IMAGE->addImage("¸ó½ºÅÍÃÑ¾Ë", "images/bullet_bmp/MBullet_normal.bmp", 26, 8, true);
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

		if (_viBullet->x < 0 && _viBullet->x > WINSIZEX && _viBullet->y <0 && _viBullet->y > WINSIZEY)
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
