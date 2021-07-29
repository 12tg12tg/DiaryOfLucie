#pragma once
#include "gameNode.h"
class clear : public gameNode
{
private:
	int frameCount;
public:
	clear();
	~clear();

	HRESULT init();
	void release();
	void update();
	void render();
};

