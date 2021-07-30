#pragma once
#include "monster.h"
class Cplayer;
class Csnaby : public monster
{
private:
	//연습용더미
	RECT fackpy;




public:
	Csnaby();
	~Csnaby();

	HRESULT init();
	void release();
	void update(Cplayer* py);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move();
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();

	void checkPlayerXY(Cplayer* py);
};
//////////////////////////////////////////////////////////////