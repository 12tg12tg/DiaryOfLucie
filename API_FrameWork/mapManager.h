#pragma once
#include"gameNode.h"
#include"Cmap.h"
#include<map>
#define MAXSIZE 9


enum MAPKIND
{
	NONE,
	CLEARROOM,
	START,
	NORMAL,
	SHOP,
	MORUROOM,
	statueROOM,
	CHESTROOM,
	BOSSROOM,
	NEXTSTAGE
};
struct MAP {
	motherMap* _motherMap;
	string sceneKey;
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
	Cmap6* _Cmap6;
	Cmap7* _Cmap7;
	Cmap8* _Cmap8;
	Cmap9* _Cmap9;
	Cmap10* _Cmap10;

	string currentMap;
	DungeonDoor _dgDoor;
	POINT currentIndex;
	monsterManager* mm;
	bulletManager* bm;
	int currentMonNum =0;

	int remainRoom = 12;
	int mapSize = 0;
	int remain_SHOP =1;
	int	remain_MORUROOM=1;
	int	remain_statueROOM=1;
	int	remain_CHESTROOM=1;

	bool topdoor_open;
	bool bottomdoor_open;
	bool rightdoor_open;
	bool leftdoor_open;

	bool checkright;
	bool checkleft;
	bool checktop;
	bool checkbottom;



	MAP stage1[MAXSIZE][MAXSIZE];

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

	image* getCurrentColMap()
	{

		if (_mStage1.find(currentMap) != _mStage1.end())
		{
			return	_mStage1.find(currentMap)->second->getcolMap();
		}
		else
		{
			return nullptr;
		}
	}
	DungeonDoor* getCurrentDoor()
	{
		if (_mStage1.find(currentMap) != _mStage1.end())
		{
			return	_mStage1.find(currentMap)->second->getDungeonDoor();
		}
		else
		{
			return nullptr;
		}
	}
public:
	void setrightdoor_state(bool rightdoor_open) { this->rightdoor_open = rightdoor_open; }
	void setleftdoor_state(bool leftdoor_open) { this->leftdoor_open = leftdoor_open; }
	void settopdoor_state(bool topdoor_open) { this->topdoor_open = topdoor_open; }
	void setbottomdoor_state(bool bottomdoor_open) { this->bottomdoor_open = bottomdoor_open; }

	void checkrightdoorcollison(bool checkrightdoorcollison) { checkright = checkrightdoorcollison; }
	void checkleftdoorcollison(bool checkleftdoorcollison) { checkleft = checkleftdoorcollison; }
	void checktopdoorcollison(bool checktopdoorcollison) { checktop = checktopdoorcollison; }
	void checkdowndoorcollison(bool checkdowndoorcollison) { checkbottom = checkdowndoorcollison; }

	void doorstate(monster* monster);
	void UseableDoor();
	void makestage1(int i, int k);
	void makeclear();


	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_Cmap1->setIsDebug(_isDebug);
		_Cmap2->setIsDebug(_isDebug);
		_Cmap3->setIsDebug(_isDebug);
		_Cmap4->setIsDebug(_isDebug);
		_Cmap5->setIsDebug(_isDebug);
		_Cmap6->setIsDebug(_isDebug);
		_Cmap7->setIsDebug(_isDebug);
		_Cmap8->setIsDebug(_isDebug);
		_Cmap9->setIsDebug(_isDebug);
		_Cmap10->setIsDebug(_isDebug);
	
	}

	bool setShopRoom();
	bool setMORURoom();
	bool setstatueRoom();
	bool setchestRoom();
	bool setBossRoom();
	bool setNextRoom();


};