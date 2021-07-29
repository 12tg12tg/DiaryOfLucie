#pragma once
#include "gameNode.h"
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////
class Cplayer : public gameNode
{
private:







private:
	bool _isDebug;
public:
	Cplayer();
	~Cplayer();

	HRESULT init();
	void release();
	void update();
	void render();







	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

