#pragma once
#include "gameNode.h"
#include "monster.h"
#include "OBBCollision.h"
#include "coin.h"
class bulletManager;
class monsterManager;
class mapManager;
class collisionManager : public gameNode
{
private:
	bulletManager* bm;
	monsterManager* mm;
	OBBCollision* obb;
	mapManager* mapm;
	goldCoin* gcoin;
	silverCoin* scoin;
	bronzeCoin* bcoin;

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
	void checkUp();
	void checkRight();
	void checkLeft();
	void checkDown();
	void checkMonUp(monster* monster);
	void checkMonDown(monster* monster);
	void checkMonLeft(monster* monster);
	void checkMonRight(monster* monster);
	void mapTomon();
	void playerToDoor();
	void bulletToMap();
	void bulletTobullet();
	void playerToCoin();
	//보조함수
	void checkMonsterRectColl(monster* monster, bool isBoss);
	void checkMonsterRectPlayer(monster* monster);

	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setmapManagerMemoryLink(mapManager* mapManager) { mapm = mapManager; }
	void setGoldCoinMemoryLink(goldCoin* goldCoin) { gcoin = goldCoin; }
	void setSilverCoinMemoryLink(silverCoin* silverCoin) { scoin = silverCoin; }
	void setBronzeCoinMemoryLink(bronzeCoin* bronzeCoin) { bcoin = bronzeCoin; }
	//void setMonsterManagerMemoryLink(mapManager* mapManager) { mapm = mapManager; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

