#include"framework.h"
#include"coin.h"

goldCoin::goldCoin()
{
}

goldCoin::~goldCoin()
{
}

HRESULT goldCoin::init()
{
	return S_OK;
}

void goldCoin::release()
{
}

void goldCoin::update()
{
	move();

}

void goldCoin::render()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viCoin->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viCoin->coinImage, ZUNIT, _viCoin->rc.bottom, _viCoin->rc.left, _viCoin->rc.top, _viCoin->coinAni);
	}
}

void goldCoin::drop(float x, float y)
{
	tagcoin coin;
	ZeroMemory(&coin, sizeof(tagcoin));
	coin.coinImage = new  image;
	coin.coinImage = IMAGE->addFrameImage("금화", "images/item/gold_coin.bmp", 128, 16,8,1, true);
	coin.coinAni = new animation;
	coin.coinAni = ANIMATION->addNoneKeyAnimation("금화", 10, false, true);
	coin.x =coin.realX= x;
	coin.y =coin.realY= y;
	coin.angle = UTIL::getAngle(coin.realX, coin.realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	coin.howmuch = 100;
	coin.range = 100;
	coin.rc = RectMake(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void goldCoin::move()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end();++_viCoin)
	{
		_viCoin->x += cosf(_viCoin->angle) * 0;
		_viCoin->y -= sinf(_viCoin->angle) * 0;

		_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
			_viCoin->coinImage->getFrameWidth(),
			_viCoin->coinImage->getFrameHeight());

		if (_viCoin->range >= UTIL::getDistance(_viCoin->x,_viCoin->y,PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y))
		{
			_viCoin->angle = UTIL::getAngle(_viCoin->realX, _viCoin->realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
			_viCoin->x += cosf(_viCoin->angle) * 1;
			_viCoin->y -= sinf(_viCoin->angle) * 1;

			_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
				_viCoin->coinImage->getFrameWidth(),
				_viCoin->coinImage->getFrameHeight());
			_viCoin->realX = _viCoin->x;
			_viCoin->realY = _viCoin->y;
		}
	}
}


void goldCoin::removecoin(int arrNum)
{
	_vCoin.erase(_vCoin.begin() + arrNum);
}

silverCoin::silverCoin()
{
}

silverCoin::~silverCoin()
{
}

HRESULT silverCoin::init()
{
	return S_OK;
}

void silverCoin::release()
{
}

void silverCoin::update()
{
	move();

}

void silverCoin::render()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viCoin->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viCoin->coinImage, ZUNIT, _viCoin->rc.bottom, _viCoin->rc.left, _viCoin->rc.top, _viCoin->coinAni);
	}
}

void silverCoin::drop(float x, float y)
{
	tagcoin coin;
	ZeroMemory(&coin, sizeof(tagcoin));
	coin.coinImage = new  image;
	coin.coinImage = IMAGE->addFrameImage("은화", "images/item/silver_coin.bmp", 128, 16, 8, 1, true);
	coin.coinAni = new animation;
	coin.coinAni = ANIMATION->addNoneKeyAnimation("은화", 10, false, true);
	coin.x = x;
	coin.y = y;
	coin.angle = UTIL::getAngle(coin.realX, coin.realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	coin.range = 100;
	coin.howmuch = 50;
	coin.rc = RectMakeCenter(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void silverCoin::move()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		_viCoin->x += cosf(_viCoin->angle) * 0;
		_viCoin->y -= sinf(_viCoin->angle) * 0;

		_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
			_viCoin->coinImage->getFrameWidth(),
			_viCoin->coinImage->getFrameHeight());

		if (_viCoin->range >= UTIL::getDistance(_viCoin->x, _viCoin->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y))
		{
			_viCoin->angle = UTIL::getAngle(_viCoin->realX, _viCoin->realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
			_viCoin->x += cosf(_viCoin->angle) * 1;
			_viCoin->y -= sinf(_viCoin->angle) * 1;

			_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
				_viCoin->coinImage->getFrameWidth(),
				_viCoin->coinImage->getFrameHeight());
			_viCoin->realX = _viCoin->x;
			_viCoin->realY = _viCoin->y;
		}
	}
}

void silverCoin::removecoin(int arrNum)
{
	_vCoin.erase(_vCoin.begin() + arrNum);
}

bronzeCoin::bronzeCoin()
{
}

bronzeCoin::~bronzeCoin()
{
}

HRESULT bronzeCoin::init()
{
	return S_OK;
}

void bronzeCoin::release()
{
}

void bronzeCoin::update()
{
	move();
	
}

void bronzeCoin::render()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viCoin->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viCoin->coinImage, ZUNIT, _viCoin->rc.bottom, _viCoin->rc.left, _viCoin->rc.top, _viCoin->coinAni);
	}
}

void bronzeCoin::drop(float x, float y)
{
	tagcoin coin;
	ZeroMemory(&coin, sizeof(tagcoin));
	coin.coinImage = new  image;
	coin.coinImage = IMAGE->addFrameImage("동화", "images/item/bronze_coin.bmp", 128, 16, 8, 1, true);
	coin.coinAni = new animation;
	coin.coinAni = ANIMATION->addNoneKeyAnimation("동화", 10, false, true);
	coin.x = x;
	coin.y = y;
	coin.angle = UTIL::getAngle(coin.realX, coin.realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	coin.range = 100;
	coin.howmuch = 10;
	coin.rc = RectMakeCenter(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void bronzeCoin::move()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		_viCoin->x += cosf(_viCoin->angle) * 0;
		_viCoin->y -= sinf(_viCoin->angle) * 0;

		_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
			_viCoin->coinImage->getFrameWidth(),
			_viCoin->coinImage->getFrameHeight());

		if (_viCoin->range >= UTIL::getDistance(_viCoin->x, _viCoin->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y))
		{
			_viCoin->angle = UTIL::getAngle(_viCoin->realX, _viCoin->realY, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
			_viCoin->x += cosf(_viCoin->angle) * 1;
			_viCoin->y -= sinf(_viCoin->angle) * 1;

			_viCoin->rc = RectMake(_viCoin->x, _viCoin->y,
				_viCoin->coinImage->getFrameWidth(),
				_viCoin->coinImage->getFrameHeight());
			_viCoin->realX = _viCoin->x;
			_viCoin->realY = _viCoin->y;
		}
	}
}

void bronzeCoin::removecoin(int arrNum)
{
	_vCoin.erase(_vCoin.begin() + arrNum);
}
