#pragma once
#include"gameNode.h"
#include"Cmap.h"
#include<map>
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
	motherMap* _motherMap;
	string sceneKey;
	bool isMake = false;
	bool canMake = true;
	MAPKIND mapkind = NONE;

};
class bulletManager;
class monsterManager;
class mapManager :public gameNode
{
private:
	Cmap* _Cmap1;
	Cmap2* _Cmap2;
	Cmap3* _Cmap3;
	Cmap4* _Cmap4;
	Cmap5* _Cmap5;
	string currentMap;
	DungeonDoor _dgDoor;

	monsterManager* mm;
	bulletManager* bm;

	map<string,motherMap*> _mStage1;
	map<string, motherMap*>::iterator _imStage1;
	

	bool _isDebug;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	Cmap* getCmapInstance() { return _Cmap1; }
	Cmap2* getCmap2Instance() { return _Cmap2; }
	Cmap3* getCmap3Instance() { return _Cmap3; }
	Cmap4* getCmap4Instance() { return _Cmap4; }
	Cmap5* getCmap5Instance() { return _Cmap5; }

	image* getCurrentColMap() {

		if (_mStage1.find(currentMap) != _mStage1.end())
		{
			return	_mStage1.find(currentMap)->second->getcolMap();
		}
		else
		{
			return nullptr;
		}
	}

	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
};