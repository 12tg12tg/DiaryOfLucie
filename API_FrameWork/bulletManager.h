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

	 

private:
	bool _isDebug;
public:
	bulletManager();
	~bulletManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
<<<<<<< HEAD
		//_playerBullet->setIsDebug(_isDebug);
=======
		_CpMagicBullet->setIsDebug(_isDebug);
>>>>>>> 965137fac9d5407bcc3c4986dd0a6e2ce77899f1
	}
};

