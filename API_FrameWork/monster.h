#pragma once
#include "gameNode.h"
enum class MONSTERMOVESTATE
{
	NONE,
	RIGHTUP,
	UP,
	LEFTUP,
	LEFT,
	LEFTDOWN,
	DOWN,
	RIGHTDOWN,
	RIGHT
};
enum class MONSTERACTIVE
{
	NONE,
	FINDING,
	RNDMOVE,
	ATTACK,
	DEATH,
};
struct tagMonster
{
	image* img;
	int frameX, frameY;
	int framecount;
	RECT rc;
	float x, y;
	int width;
	int height;
	float speed;
	int hp;
	bool isStun;
	bool isDeath;
	bool afterDeath;
	bool findPlayer;
	float targetX;
	float targetY;
	float angle;
	float range;
	int stunCount;
	int patternCount;
	int deathalpha;
	MONSTERACTIVE activestate;
	MONSTERMOVESTATE movestate;
};
class monster : public gameNode
{
protected:
	vector<tagMonster> _vMonster;
	vector<tagMonster>::iterator _viMonster;
	bool _isDebug;
public:
	monster();
	~monster();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void addMonster(float x, float y);
	virtual void move();
	virtual void checkAngle();
	virtual void giveFrame();
	virtual void deathCheck();
	virtual void knockback(float x, float y, bool stun = false);
	virtual void stuncheck();

	vector<tagMonster>& getVMonster() { return _vMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

