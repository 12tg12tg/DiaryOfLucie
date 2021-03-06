#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include"bulletManager.h"
#include "chest.h"
#include"fountain.h"
#include"moru.h"
#include"statue.h"
#include"shop.h"
#include"coin.h"
enum MONKIND
{
	SNABY,
	SLIME,
	MUSHMAN,
	FAIRY,
	FLIME
};
enum BOSS
{
	SLIME_B,
	FLIME_B,
	MUSHMOM_B
};
struct DungeonDoor {
	RECT Door;
	bool isOpen = false;
};
struct MagicDoor {
	RECT Door;
};
class bulletManager;
class motherMap :public gameNode
{
protected:

	bool _isDebug;
	int stage = 1;
	int monNum = RND->getFromInTo(2, 4);
	bool isClear = false;
	bool isrightRoom = false;
	bool isleftRoom = false;
	bool istopRoom = false;
	bool isbotRoom = false;
	POINT monpos[4];
	POINT _current_point;
	DungeonDoor _door[4];
	MagicDoor goNextStage[1];
	image* _collisionMap;
	image* _portalImage;
	animation* _portal;
	monsterManager* mm;
	bulletManager* bm;
	goldCoin* _gold_coin;
	silverCoin* _silver_coin;
	bronzeCoin* _bronze_coin;
	int aniCount = 0;
	int chooseMon;
public:
	motherMap();
	~motherMap();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void summonMon(int x);
	virtual void summonBoss(int x);
	virtual DungeonDoor* getDungeonDoor() { return _door; }
	virtual MagicDoor* getMagicNextStage() { return goNextStage; }
	virtual image* getcolMap() { return _collisionMap; }
	virtual void setMonstermemoryLink(monsterManager* mm) { this->mm = mm; }
	virtual void setbulletmemoryLink(bulletManager* bm) { this->bm = bm; }
	virtual bool getClear() { return isClear; }
	virtual void setClear(bool isClear) { this->isClear = isClear; }
	virtual void setleftDoor(bool isleftRoom) { this->isleftRoom = isleftRoom; }
	virtual void setrightDoor(bool isrightRoom) { this->isrightRoom = isrightRoom; }
	virtual void setbotDoor(bool isbotRoom) { this->isbotRoom = isbotRoom; }
	virtual void settopDoor(bool istopRoom) { this->istopRoom = istopRoom; }
	virtual void dropCoin(int x, int y);
	virtual goldCoin* getGoldCoinInstance() { return _gold_coin; }
	virtual silverCoin* getSilverCoinInstance() { return _silver_coin; }
	virtual bronzeCoin* getBronzeCoinInstance() { return _bronze_coin; }
	virtual void setIsDebug(bool isDebug) { 
		_isDebug = isDebug;
		_gold_coin->setIsDebug(_isDebug);
		_silver_coin->setIsDebug(_isDebug);
		_bronze_coin->setIsDebug(_isDebug);

	}

};

