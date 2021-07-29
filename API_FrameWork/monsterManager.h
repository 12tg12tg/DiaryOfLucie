#pragma once
#include "gameNode.h"
#include "Cmonsters.h"
class monsterManager : public gameNode
{
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

	void setIsDebug(bool isDebug) {
		_isDebug = isDebug; 
		_snaby->setIsDebug(_isDebug);

	}
};

