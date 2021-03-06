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
	virtual void giveFrame();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
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
	virtual void giveFrame();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
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
	virtual void giveFrame();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
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
	virtual void giveFrame();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
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
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	virtual void giveFrame();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cflime : public monster
{
private:




public:
	Cflime();
	~Cflime();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Csemiboss_slime : public monster
{
private:




public:
	Csemiboss_slime();
	~Csemiboss_slime();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Cslime* slm);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm, Cslime* slm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cboss_slime : public monster
{
private:
	int hp = 220;



public:
	Cboss_slime();
	~Cboss_slime();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Csemiboss_slime* ss);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm, Csemiboss_slime* ss);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
	int getHp() { return hp; }
};
//////////////////////////////////////////////////////////////
class Cboss_flime : public monster
{
private:
	int hp = 450;


public:
	Cboss_flime();
	~Cboss_flime();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
	int getHp() { return hp; }
};
//////////////////////////////////////////////////////////////
class Cmushmam_mushroom_G : public monster
{
private:


public:
	Cmushmam_mushroom_G();
	~Cmushmam_mushroom_G();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cmushmam_mushroom_P : public monster
{
private:


public:
	Cmushmam_mushroom_P();
	~Cmushmam_mushroom_P();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cmushmam_mushroom_B : public monster
{
private:


public:
	Cmushmam_mushroom_B();
	~Cmushmam_mushroom_B();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float x, float y);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cboss_mushmam : public monster
{
private:
	int color;
	int hp = 450;

public:
	Cboss_mushmam();
	~Cboss_mushmam();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Cmushmam_mushroom_G* mrG, Cmushmam_mushroom_P* mrP, Cmushmam_mushroom_B* mrB, Cmushman_mushroom* smr);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm, Cmushmam_mushroom_G* mrG, Cmushmam_mushroom_P* mrP, Cmushmam_mushroom_B* mrB, Cmushman_mushroom* smr);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
	int getHp() { return hp; }
};
//////////////////////////////////////////////////////////////
class Cyggdrasil_bomb: public monster
{
private:


public:
	Cyggdrasil_bomb();
	~Cyggdrasil_bomb();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
};
//////////////////////////////////////////////////////////////
class Cyggdrasil : public monster
{
private:
	int hp = 900;

public:
	Cyggdrasil();
	~Cyggdrasil();

	HRESULT init();
	void release();
	void update(Cplayer* py, bulletManager* bm, Cyggdrasil_bomb* bomb);
	void render();

	virtual void addMonster(float centerx, float centery);
	virtual void move(bulletManager* bm, Cyggdrasil_bomb* bomb);
	//virtual void checkAngle();
	virtual void giveFrame();
	//virtual void deathCheck();
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);
	void checkPhase();
	int getHp() { return hp; }
};


