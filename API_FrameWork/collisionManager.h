#pragma once
#include "gameNode.h"
#include"OBBCollision.h"
class bulletManager;
class monsterManager;
class collisionManager : public gameNode
{
private:
	bulletManager* bm;
	monsterManager* mm;
	OBBCollision* obb;
	SHAPE a, b;
	RECT temprc;
private:
	bool _isDebug;
public:
	collisionManager();
	~collisionManager();

	HRESULT init();
	void release();
	void update();
	void bulletToplayer();
	void bulletTomon();
	void playerTomon();

	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

