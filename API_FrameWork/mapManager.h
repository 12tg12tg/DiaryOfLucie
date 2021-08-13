#pragma once
#include"gameNode.h"
#include"Cmap.h"
#include"monsterManager.h"
#define MAXSIZE 8
enum DUNGEONDOOR
{
	DOOR_OPEN,DOOR_CLOSE
};

enum MAPKIND
{
	NONE,
	START,
	NORMAL,
	CLEARROOM,
	SHOP,
	EVENTROOM,
	CHESTROOM,
	BOSSROOM,
	NEXTSTAGE
};
struct MAP {
	int positionNum =0;

	bool isMake = false;
	bool canMake = true;
	MAPKIND mapkind = NONE;

};
class mapManager :public gameNode
{
private:
	Cmap* _Cmap1;
	Cmap2* _Cmap2;
	Cmap3* _Cmap3;
	Cmap4* _Cmap4;
	Cmap5* _Cmap5;
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _leftDoor;
	RECT _rightDoor;


	MAP stage1[8][8] = { {0,false,true,NONE},{1,false,true,NONE}, };
	bool _isDebug;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	RECT getBottomDoor() { return _bottomDoor; }
	RECT getTopDoor() { return _topDoor; }
	RECT getLeftDoor() { return _leftDoor; }
	RECT getRightDoor() { return _rightDoor; }

	Cmap* getCmapInstance() { return _Cmap1; }
	Cmap2* getCmap2Instance() { return _Cmap2; }
	Cmap3* getCmap3Instance() { return _Cmap3; }
	Cmap4* getCmap4Instance() { return _Cmap4; }
	Cmap5* getCmap5Instance() { return _Cmap5; }
	MAP _map;
	
	int getPosNum() { return _map.positionNum; }
	void setPosNum(int positionNum) { _map.positionNum = positionNum; }

};