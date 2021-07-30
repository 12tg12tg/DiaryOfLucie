#pragma once
#include "gameNode.h"
#include "Cbullets.h"
class bulletManager : public gameNode
{
private:
	CplayerBullet* _playerBullet;


	 

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
		//_playerBullet->setIsDebug(_isDebug);
	}
};

