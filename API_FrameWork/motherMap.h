#pragma once
#include "gameNode.h"
struct Monster {
	int monsterNum;
	POINT monserpos;
};
struct DungeonDoor {
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
};
class motherMap :public gameNode
{
private:
	bool _isDebug;
	DungeonDoor _door;
	image* _collisionMap;
	Monster _monster;
public:
	motherMap();
	~motherMap();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void setIsDebug(bool isDebug) { _isDebug = isDebug; }

	virtual image* getcolMap() { return _collisionMap; }
};

