#pragma once
#include "gameNode.h"
class mapManager;
class loading : public gameNode
{
private:
	image* bg;
	image* loadingbar;

	int barX, barY;
	int loadingCount;

	mapManager* mm;

	int loadingTime;
	bool _isLodingDone = false;
public:
	loading(mapManager* mm);
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsLodingDone() { return _isLodingDone; }
};

