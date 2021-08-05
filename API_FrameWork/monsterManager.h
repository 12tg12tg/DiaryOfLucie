#pragma once
#include "gameNode.h"
#include "Cmonsters.h"
class Cplayer;
class bulletManager;
class monsterManager : public gameNode
{
private:
	Cplayer* _py;
	bulletManager* _bm;
private:
	Csnaby* _snaby;
	Cslime* _slime;
	Cmushman* _mushman;
	Cmushman_mushroom* _mushman_mushroom;
	Cfairy* _fairy;


private:
	bool _isDebug;
public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayerMemoryLink(Cplayer* py) { _py = py; }
	void setBulletManagerMemoryLink(bulletManager* bm) { _bm = bm; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug; 
		_snaby->setIsDebug(_isDebug);
		_slime->setIsDebug(_isDebug);
		_mushman->setIsDebug(_isDebug);
		_mushman_mushroom->setIsDebug(_isDebug);
		_fairy->setIsDebug(_isDebug);
		
	}
};

