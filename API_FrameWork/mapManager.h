#pragma once
#include"gameNode.h"
#include"Cmap.h"
class mapManager
{




public:
	
	HRESULT init();
	void release();
	void update();
	void render();
};

