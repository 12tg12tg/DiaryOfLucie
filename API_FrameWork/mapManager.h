#pragma once
#include"gameNode.h"
#include"Cmap.h"
#include"monsterManager.h"
#include<queue>
enum DUNGEONDOOR
{
	DOOR_OPEN,DOOR_CLOSE
};

enum MAPKIND
{
	START,
	NORMAL,
	CLEARROOM,
	SHOP,
	EVENTROOM,
	CHESTROOM,
	BOSSROOM,
	NEXTSTAGE
};

class mapManager :public gameNode
{
private:
	string _fileName;
	string _backImg;
	int _x, _y;
	bool isCheck;
	bool isClear;
	vector<tagMap> _vMap;
	vector<monster*> _vMonster;

	mapManager* _leftDg;
	mapManager* _rightDg;
	mapManager* _topDg;
	mapManager* _bottomDg;

	int _floor;

	vector<mapManager*> _vMaps;
	queue<mapManager*> qTemp;
	queue<mapManager*> _qDfs;
	POINT _pTemp;
	int _mapSize;
	// bool _checkLoadTile;
	bool _checkLoadImage;

	DUNGEONDOOR _doorState;
	MAPKIND _mapKind;
public:
	mapManager(int x, int y, int floor);
	mapManager(){}


	HRESULT init();
	void release();
	void update();
	void render();

	void setStartMap();
	void setRandomMap(mapManager** map);
	void connectMap(mapManager** map);
	void bossMapDfs();
	void setBossMap(mapManager** map, int percent);
	//void loadTiles(mapManager** map);
	
	void dgDoorRender();
	void dgDoorUpdate();
	void dgDoorOpen();
	void dgDoorClose();
	void enemyUpdate();
	void popEnemy(int arr);

	void checkColiMoveBen();
	void checkColiHole();
	void checkCollisionSpa();

	void checkColiArrow();

	void setCurrentFloor(int floor) { _floor = floor; }

	mapManager* findMap(POINT pos);
	bool isFindMap(POINT pos);

	mapManager* getLeftDG() { return _leftDg; }
	mapManager* getRightDG() { return _rightDg; }
	mapManager* getTopDG() { return _topDg; }
	mapManager* getBottomDG() { return _bottomDg; }
	POINT getDungeonXY() { return PointMake(_x, _y); }

	vector<tagMap>& getMap() { return _vMap; }
	mapManager* moveDungeon(RECT rc);
	bool isMoveBen(RECT rc);
	//bool isTSHOLE(RECT rc);
	RECT getMoveBenTile(RECT rc);
	RECT getHoleTile(RECT rc);
	//vector<tagMap> getMap() { return _vMap; }
	DUNGEONDOOR getDungeonDoorState() { return _doorState; }
	MAPKIND getMapKind() { return _mapKind; }

};