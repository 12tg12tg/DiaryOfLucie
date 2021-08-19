#pragma once
#include"gameNode.h"
#include"Cmap.h"
#include"Cskill.h"
#define MAXSIZE 9


enum MAPKIND
{
	NONE,
	CLEARROOM,
	START,
	NORMAL,
	SHOP,
	MORUROOM,
	STATUEROOM,
	CHESTROOM,
	FOUNTAIN,
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
	
	Cmap10* _Cmap10;
	chestMap* _chestMap;
	shopMap* _shopMap;
	moruMap* _moruMap;
	statueMap* _statueMap;
	stage1_Boss* _stage1_Boss;
	nextStage* _nextStage;
	fountainMap* _fountainMap;
	before_Boss* _before_boss;
	last_Boss* _last_boss;
	motherMap* _motherMap2;
	image* _none;
	image* _start;
	image* _shop;
	image* _boss;
	image* _event;
	image* _goal;
	image* _fight;
	image* _chest;
	image* _back;
	

	string currentMap;
	
	POINT currentIndex;
	monsterManager* mm;
	bulletManager* bm;
	Cskill* sk;
	int currentMonNum =0;
	int remainRoom = 12;
	int mapSize;
	int _curstage;
	int remainNextStage = 1;
	bool topdoor_open;
	bool bottomdoor_open;
	bool rightdoor_open;
	bool leftdoor_open;
	bool goNextStage;
	bool checkright;
	bool checkleft;
	bool checktop;
	bool checkbottom;
	bool checkMagicDoor;


	MAP stage1[MAXSIZE][MAXSIZE];


	map<string,motherMap*> _mStage1;
	map<string, motherMap*>::iterator _imStage1;
	
	bool isAlphaDownward = true;
	BYTE alpha = 220;
	bool _isDebug;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	
	Cmap10* getCmap10Instance() { return _Cmap10; }
	before_Boss* getbefore_BossInstance() { return _before_boss; }
	last_Boss* getlast_BossInstance() { return _last_boss; }
	chestMap* getchestMapInstance() { return _chestMap; }
	shopMap* getshopMapInstance() { return _shopMap; }
	statueMap* getstatueMapInstance() { return _statueMap; }
	moruMap* getmoruMapInstance() { return _moruMap; }
	stage1_Boss* getstage1_BossInstance() {return _stage1_Boss;}
	nextStage* getnextStageInstance() { return _nextStage; }
	image* getCurrentColMap();
	DungeonDoor* getCurrentDoor();
	MagicDoor* getMagicDoor();
	mapManager();
	~mapManager();
	void setrightdoor_state(bool rightdoor_open) { this->rightdoor_open = rightdoor_open; }
	void setleftdoor_state(bool leftdoor_open) { this->leftdoor_open = leftdoor_open; }
	void settopdoor_state(bool topdoor_open) { this->topdoor_open = topdoor_open; }
	void setbottomdoor_state(bool bottomdoor_open) { this->bottomdoor_open = bottomdoor_open; }

	void checkrightdoorcollison(bool checkrightdoorcollison) { checkright = checkrightdoorcollison; }
	void checkleftdoorcollison(bool checkleftdoorcollison) { checkleft = checkleftdoorcollison; }
	void checktopdoorcollison(bool checktopdoorcollison) { checktop = checktopdoorcollison; }
	void checkdowndoorcollison(bool checkdowndoorcollison) { checkbottom = checkdowndoorcollison; }
	void checkMagicDoorCollison(bool magicDoorCollison) { checkMagicDoor = magicDoorCollison; }

	void doorstate(monster* monster);
	void UseableDoor();
	void makestage1(int i, int k);
	void makestage4(int i, int k);
	void makeclear();
	void makeclear2();
	bool getGoNextStage() {return goNextStage;}
	void clearbullet();

	bool setShopRoom();
	bool setMORURoom();
	bool setstatueRoom();
	bool setchestRoom();
	bool setBossRoom();
	bool setBossRoom2();
	void setNextRoom();
	bool setNormal();
	bool setfountainMap();
	bool checkNextStage();
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { mm = monsterManager; }
	void setBulletManagerMemoryLink(bulletManager* bulletManager) { bm = bulletManager; }
	void setSkillMemoryLink(Cskill* skill) { sk = skill; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		for (int i = 0; i < MAXSIZE; i++)
		{
			for (int k = 0; k < MAXSIZE; k++)
			{
				if (stage1[i][k].mapkind != NONE)
				{
					stage1[i][k]._motherMap->setIsDebug(_isDebug);
				}
			}
		}
		if (_curstage < 4)
		{
			_Cmap10->setIsDebug(_isDebug);
			_chestMap->setIsDebug(_isDebug);
			_moruMap->setIsDebug(_isDebug);
			_statueMap->setIsDebug(_isDebug);
			_shopMap->setIsDebug(_isDebug);
			_stage1_Boss->setIsDebug(_isDebug);
			_nextStage->setIsDebug(_isDebug);
			_fountainMap->setIsDebug(_isDebug);
		}
		else
		{
				_before_boss->setIsDebug(_isDebug);
				_last_boss->setIsDebug(_isDebug);
		}
	}



};