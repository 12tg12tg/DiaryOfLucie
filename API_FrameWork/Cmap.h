#pragma once
#include"gameNode.h"

struct tagMap
{

};
class Cmap : public gameNode
{
private:
	

public:
	Cmap();
	~Cmap();
	HRESULT init();
	void release();
	void update();
	void render();

};

