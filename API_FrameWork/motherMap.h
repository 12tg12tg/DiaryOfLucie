#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include"bulletManager.h"
#include "chest.h"
#include"fountain.h"
#include"moru.h"
#include"statue.h"
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
	int monNum = RND->getFromInTo(2, 4);
	bool isClear = false;
	POINT monpos[4];
	POINT _current_point;
	DungeonDoor _door[4];
	MagicDoor goNextStage[1];
	image* _collisionMap;
	image* _portalImage;
	animation* _portal;
	monsterManager* mm;
	bulletManager* bm;
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
	virtual void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	virtual DungeonDoor* getDungeonDoor() { return _door; }
	virtual MagicDoor* getMagicNextStage() { return goNextStage; }
	virtual image* getcolMap() { return _collisionMap; }
	virtual void setMonstermemoryLink(monsterManager* mm) { this->mm = mm; }
	virtual void setbulletmemoryLink(bulletManager* bm) { this->bm = bm; }
	virtual bool getClear() { return isClear; }
	virtual void setClear(bool isClear) { this->isClear = isClear; }
	/*virtual POINT getPoint() { return _current_point; }
	virtual void setPoint(POINT _current_point) { this->_current_point = _current_point; }
	virtual void setMapArea() { this->_current_point = _current_point; }*/

};

