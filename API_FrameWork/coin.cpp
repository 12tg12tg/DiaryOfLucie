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
	coin.x = x;
	coin.y = y;
	coin.howmuch = 100;
	coin.rc = RectMakeCenter(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void goldCoin::move()
{
}

void goldCoin::removecoin(int arrNum)
{
	_vCoin.erase(_vCoin.begin() + arrNum);
}

sliverCoin::sliverCoin()
{
}

sliverCoin::~sliverCoin()
{
}

HRESULT sliverCoin::init()
{
	return S_OK;
}

void sliverCoin::release()
{
}

void sliverCoin::update()
{
}

void sliverCoin::render()
{
	_viCoin = _vCoin.begin();
	for (_viCoin; _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_isDebug) ZORDER->ZorderRectangle(_viCoin->rc, ZCOL1);
		ZORDER->ZorderAniRender(_viCoin->coinImage, ZUNIT, _viCoin->rc.bottom, _viCoin->rc.left, _viCoin->rc.top, _viCoin->coinAni);
	}
}

void sliverCoin::drop(float x, float y)
{
	tagcoin coin;
	ZeroMemory(&coin, sizeof(tagcoin));
	coin.coinImage = new  image;
	coin.coinImage = IMAGE->addFrameImage("금화", "images/item/gold_coin.bmp", 128, 16, 8, 1, true);
	coin.coinAni = new animation;
	coin.coinAni = ANIMATION->addNoneKeyAnimation("금화", 10, false, true);
	coin.x = x;
	coin.y = y;
	coin.howmuch = 50;
	coin.rc = RectMakeCenter(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void sliverCoin::move()
{
}

void sliverCoin::removecoin(int arrNum)
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
	coin.coinImage = IMAGE->addFrameImage("금화", "images/item/gold_coin.bmp", 128, 16, 8, 1, true);
	coin.coinAni = new animation;
	coin.coinAni = ANIMATION->addNoneKeyAnimation("금화", 10, false, true);
	coin.x = x;
	coin.y = y;
	coin.howmuch = 10;
	coin.rc = RectMakeCenter(coin.x, coin.y,
		coin.coinImage->getFrameWidth(),
		coin.coinImage->getFrameHeight());
	_vCoin.push_back(coin);
}

void bronzeCoin::move()
{
}

void bronzeCoin::removecoin(int arrNum)
{
	_vCoin.erase(_vCoin.begin() + arrNum);
}
