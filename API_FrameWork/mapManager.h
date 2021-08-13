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
	
public:
	

};