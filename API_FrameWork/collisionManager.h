#pragma once
#include "gameNode.h"
class collisionManager : public gameNode
{
private:




private:
	bool _isDebug;
public:
	collisionManager();
	~collisionManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

