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
	CmSBoss1Bullet* _CmSBoss1Bullet;
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
	CmSBoss1Bullet* getSlmBosBullnstance() { return _CmSBoss1Bullet; }





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
		_CmSBoss1Bullet->setIsDebug(_isDebug);
	}
};

