#pragma once
#include "gameNode.h"
#include "Cbullets.h"
class bulletManager : public gameNode
{
private:
	CpMagicBullet* _CpMagicBullet;
	CpArrowBullet* _CpArrowBullet;
	CmTripleBullet* _CmTripleBullet;
	CmCircleBullet* _CmCircleBullet;
	CmReturnBullet* _CmReturnBullet;
	CmWideBullet* _CmWideBullet;
	CmHomingBullet* _CmHomingBullet;
	CmPoisonBullet* _CmPoisonBullet;
	CmNiddleBullet* _CmNiddleBullet;
	CmLongPoisonBullet* _CmLongPoisonBullet;
	CmSBoss1Bullet* _CmSBoss1Bullet;
	CmFBoss1Bullet* _CmFBoss1Bullet;
	CmFBoss2Bullet* _CmFBoss2Bullet;
	CmFBoss3Bullet* _CmFBoss3Bullet;
	CmTBoss1Bullet* _CmTBoss1Bullet;
	CmTBoss2Bullet* _CmTBoss2Bullet;
	CmTBoss3Bullet* _CmTBoss3Bullet;
	CpSword* _CpSword;
	CpSkil_LuckyStar* _CpSkil_LuckyStar;
	CpSkil_Ice_spear* _CpSkil_Ice_spear;

private:
	bool _isDebug;
public:
	bulletManager();
	~bulletManager();

	HRESULT init();
	void release();
	void update();
	void render();



	CpMagicBullet* getMgcBulInstance() { return _CpMagicBullet; }
	CpArrowBullet* getArwBulInstance() { return _CpArrowBullet; }
	CmTripleBullet* getTriBulInstance() { return _CmTripleBullet; }
	CmCircleBullet* getCirBulInstance() { return _CmCircleBullet; }
	CmReturnBullet* getRtnBulInstance() { return _CmReturnBullet; }
	CmWideBullet* getWidBulInstance() { return _CmWideBullet; }
	CmHomingBullet* getHomBulInstance() { return _CmHomingBullet; }
	CmPoisonBullet* getPsnBulInstance() { return _CmPoisonBullet; }
	CmNiddleBullet* getnidBulInstance() { return _CmNiddleBullet; }
	CmLongPoisonBullet* getLPsnBulInstance() { return _CmLongPoisonBullet; }
	CmSBoss1Bullet* getSlmBos1Bullnstance() { return _CmSBoss1Bullet; }
	CmFBoss1Bullet* getFlwBos1Bullnstance() { return _CmFBoss1Bullet; }
	CmFBoss2Bullet* getFlwBos2Bullnstance() { return _CmFBoss2Bullet; }
	CmFBoss3Bullet* getFlwBos3Bullnstance() { return _CmFBoss3Bullet; }
	CmTBoss1Bullet* getTreBos1Bullnstance() { return _CmTBoss1Bullet; }
	CmTBoss2Bullet* getTreBos2Bullnstance() { return _CmTBoss2Bullet; }
	CmTBoss3Bullet* getTreBos3Bullnstance() { return _CmTBoss3Bullet; }
	CpSword* getSwordInstance() { return _CpSword; }
	CpSkil_LuckyStar* getLucky_starInstance() { return _CpSkil_LuckyStar; }
	CpSkil_Ice_spear* getIce_spearInstance() { return  _CpSkil_Ice_spear; }



	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_CpMagicBullet->setIsDebug(_isDebug);
		_CpArrowBullet->setIsDebug(_isDebug);
		_CmTripleBullet->setIsDebug(_isDebug);
		_CmCircleBullet->setIsDebug(_isDebug);
		_CmReturnBullet->setIsDebug(_isDebug);
		_CmWideBullet->setIsDebug(_isDebug);
		_CmHomingBullet->setIsDebug(_isDebug);
		_CmPoisonBullet->setIsDebug(_isDebug);
		_CmNiddleBullet->setIsDebug(_isDebug);
		_CmLongPoisonBullet->setIsDebug(_isDebug);
		_CmSBoss1Bullet->setIsDebug(_isDebug);
		_CmFBoss1Bullet->setIsDebug(_isDebug);
		_CmFBoss2Bullet->setIsDebug(_isDebug);
		_CmFBoss3Bullet->setIsDebug(_isDebug);
		_CmTBoss1Bullet->setIsDebug(_isDebug);
		_CmTBoss2Bullet->setIsDebug(_isDebug);
		_CmTBoss3Bullet->setIsDebug(_isDebug);
		_CpSword->setIsDebug(_isDebug);
		_CpSkil_LuckyStar->setIsDebug(_isDebug);
		_CpSkil_Ice_spear->setIsDebug(_isDebug);
	}
};

