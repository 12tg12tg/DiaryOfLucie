#pragma once
#include "monster.h"
class Csnaby : public monster
{
private:




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
//////////////////////////////////////////////////////////////
class Cmushman_mushroom : public monster
{
private:




public:
	Cmushman_mushroom();
	~Cmushman_mushroom();

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
class Cmushman : public monster
{
private:




public:
	Cmushman();
	~Cmushman();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Cmushman_mushroom* _mushroom);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm, Cmushman_mushroom* _mushroom);
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
};
//////////////////////////////////////////////////////////////
class Cfairy : public monster
{
private:




public:
	Cfairy();
	~Cfairy();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Cmushman_mushroom* _mushroom);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm, Cmushman_mushroom* _mushroom);
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
};
