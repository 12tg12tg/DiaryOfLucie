#pragma once
#include "gameNode.h"
//////////////////////////���漱�𿵿�/////////////////////////
			

//////////////////////////////////////////////////////////////
class Csnaby : public gameNode
{
private:






private:
	bool _isDebug;
public:
	Csnaby();
	~Csnaby();

	HRESULT init();
	void release();
	void update();
	void render();

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
//////////////////////////////////////////////////////////////

