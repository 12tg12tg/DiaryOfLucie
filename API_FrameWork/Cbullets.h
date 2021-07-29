#pragma once
#include "gameNode.h"
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////
class CplayerBullet : public gameNode
{
private:






private:
	bool _isDebug;
public:
	CplayerBullet();
	~CplayerBullet();

	HRESULT init();
	void release();
	void update();
	void render();






	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

