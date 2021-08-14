#pragma once
#include "gameNode.h"
#include "monster.h"
#include "OBBCollision.h"
#include"Cmap.h"
class bulletManager;
class monsterManager;
class collisionManager : public gameNode
{
private:
	bulletManager* bm;
	monsterManager* mm;
	OBBCollision* obb;
	Cmap* mapm;
	float _x;
	float _y;
	int _probeY;
	int _probeX;
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
	void mapToplayer();
	void mapTobullet();
	void mapTomon();

	//보조함수
	void checkMonsterRectColl(monster* monster, bool isBoss);
	void checkMonsterRectPlayer(monster* monster);

	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

