#pragma once
#include "gameNode.h"
class DOL_Title : public gameNode
{
private:
	image* bg;
	image* title;
	image* startimg;
	image* optiontimg;
	image* exitimg;

	Button* start;
	Button* option;
	Button* maker;
	Button* exit;

	bool _fadeOut;
	bool _isStart;

	int _particleCount;
public:
	DOL_Title();
	~DOL_Title();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart() { return _isStart; }
};

