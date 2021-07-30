#include "framework.h"
#include "bulletManager.h"

bulletManager::bulletManager()
{
}

bulletManager::~bulletManager()
{
}

HRESULT bulletManager::init()
{
	_CpMagicBullet = new CpMagicBullet;
	_CpArrowBullet = new CpArrowBullet;
	_CmTripleBullet = new CmTripleBullet;
	_CmCircleBullet = new CmCircleBullet;
	_CmReturnBullet = new CmReturnBullet;
	_CmWideBullet = new CmWideBullet;
	return S_OK;
}

void bulletManager::release()
{
	SAFE_DELETE(_CpMagicBullet);
	SAFE_DELETE(_CpArrowBullet);
	SAFE_DELETE(_CmTripleBullet);
	SAFE_DELETE(_CmCircleBullet);
	SAFE_DELETE(_CmReturnBullet);
	SAFE_DELETE(_CmWideBullet);
}

void bulletManager::update()
{
	_CpMagicBullet->update();
	_CpArrowBullet->update();
	_CmTripleBullet->update();
	_CmCircleBullet->update();
	_CmReturnBullet->update();
	_CmWideBullet->update();
} 

void bulletManager::render()
{
	_CpMagicBullet->render();
	_CpArrowBullet->render();
	_CmTripleBullet->render();
	_CmCircleBullet->render();
	_CmReturnBullet->render();
	_CmWideBullet->render();
}
