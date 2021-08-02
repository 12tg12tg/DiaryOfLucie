#pragma once
#include "gameNode.h"
#include "Cmonsters.h"
class Cplayer;
class monsterManager : public gameNode
{
private:
	Cplayer* _py;
private:
	Csnaby* _snaby;





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
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug; 
		_snaby->setIsDebug(_isDebug);

	}
};

