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
	_CmHomingBullet = new CmHomingBullet;
	_CmPoisonBullet = new CmPoisonBullet;
	_CmNiddleBullet = new CmNiddleBullet;
	_CmLongPoisonBullet = new CmLongPoisonBullet;
	_CmSBoss1Bullet = new CmSBoss1Bullet;
	_CmFBoss1Bullet = new CmFBoss1Bullet;
	_CmFBoss2Bullet = new CmFBoss2Bullet;
	_CmFBoss3Bullet = new CmFBoss3Bullet;
	_CmTBoss1Bullet = new CmTBoss1Bullet;
	_CmTBoss2Bullet = new CmTBoss2Bullet;
	_CmTBoss3Bullet = new CmTBoss3Bullet;
	_CpSword = new CpSword;
	_CpSkil_LuckyStar = new CpSkil_LuckyStar;
	_CpSkil_Ice_spear = new CpSkil_Ice_spear;
	_CpSkil_Haste = new CpSkil_Haste;
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
	SAFE_DELETE(_CmHomingBullet);
	SAFE_DELETE(_CmPoisonBullet);
	SAFE_DELETE(_CmNiddleBullet);
	SAFE_DELETE(_CmLongPoisonBullet);
	SAFE_DELETE(_CmSBoss1Bullet);
	SAFE_DELETE(_CmFBoss1Bullet);
	SAFE_DELETE(_CmFBoss2Bullet);
	SAFE_DELETE(_CmFBoss3Bullet);
	SAFE_DELETE(_CmTBoss1Bullet);
	SAFE_DELETE(_CmTBoss2Bullet);
	SAFE_DELETE(_CmTBoss3Bullet);
	SAFE_DELETE(_CpSword);
	SAFE_DELETE(_CpSkil_LuckyStar);
	SAFE_DELETE(_CpSkil_Ice_spear);
	SAFE_DELETE(_CpSkil_Haste);
}

void bulletManager::update()
{
	_CpMagicBullet->update();
	_CpArrowBullet->update();
	_CmTripleBullet->update();
	_CmCircleBullet->update();
	_CmReturnBullet->update();
	_CmWideBullet->update();
	_CmHomingBullet->update();
	_CmPoisonBullet->update();
	_CmNiddleBullet->update();
	_CmLongPoisonBullet->update();
	_CmSBoss1Bullet->update();
	_CmFBoss1Bullet->update();
	_CmFBoss2Bullet->update();
	_CmFBoss3Bullet->update();
	_CmTBoss1Bullet->update();
	_CmTBoss2Bullet->update();
	_CmTBoss3Bullet->update();
	_CpSword->update();
	_CpSkil_LuckyStar->update();
	_CpSkil_Ice_spear->update();
	_CpSkil_Haste->update();
} 

void bulletManager::render()
{
	_CpMagicBullet->render();
	_CpArrowBullet->render();
	_CmTripleBullet->render();
	_CmCircleBullet->render();
	_CmReturnBullet->render();
	_CmWideBullet->render();
	_CmHomingBullet->render();
	_CmPoisonBullet->render();
	_CmNiddleBullet->render();
	_CmLongPoisonBullet->render();
	_CmSBoss1Bullet->render();
	_CmFBoss1Bullet->render();
	_CmFBoss2Bullet->render();
	_CmFBoss3Bullet->render();
	_CmTBoss1Bullet->render();
	_CmTBoss2Bullet->render();
	_CmTBoss3Bullet->render();
	_CpSword->render();
	_CpSkil_LuckyStar->render();
	_CpSkil_Ice_spear->render();
	_CpSkil_Haste->render();
}
