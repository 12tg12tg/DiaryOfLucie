#pragma once
#include "gameNode.h"
#include"monsterManager.h"

enum MONKIND
{
	SNABY,
	SLIME,
	MUSHMAN,
	FAIRY,
	FLIME
};
struct DungeonDoor {
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
};

class motherMap :public gameNode
{
protected:
	bool _isDebug;
	int monNum = RND->getFromInTo(2, 4);
	POINT monpos[4];
	DungeonDoor _door;
	image* _collisionMap;
	monsterManager* mm;
	int chooseMon;
public:
	motherMap();
	~motherMap();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void summonMon(int x);
	virtual void setIsDebug(bool isDebug) { _isDebug = isDebug; }

	virtual image* getcolMap() { return _collisionMap; }
	virtual void setMonstermemoryLink(monsterManager* mm) { this->mm = mm; }
};

