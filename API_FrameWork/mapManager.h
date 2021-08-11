#pragma once
#include"gameNode.h"
#include"Cmap.h"
class mapManager
{




public:
	vector<Cmap*>_cMap;
	HRESULT init();
	void release();
	void update();
	void render();
};

