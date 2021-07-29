#pragma once
#include "gameNode.h"
class tack : public gameNode
{
private:
	struct tagTack
	{
		float x, y;
		RECT rc;
	};
private:
	vector<tagTack> vTack;
	vector<tagTack>::iterator viTack;
	bool isDebug;
public:
	tack();
	~tack();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	vector<tagTack> getVector() { return vTack; }
	void setIsDebug(bool isdebug) { isDebug = isdebug; }
};

