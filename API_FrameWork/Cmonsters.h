#pragma once
#include "monster.h"
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
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
};
//////////////////////////////////////////////////////////////
class Cslime : public monster
{
private:
	//연습용더미
	RECT fackpy;




public:
	Cslime();
	~Cslime();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
};