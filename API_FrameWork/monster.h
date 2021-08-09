#pragma once
#include "gameNode.h"
class Cplayer;
class bulletManager;

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
	ATTACK2,
	DEATH,
};
struct tagMonster
{
	image* img;
	animation* ani;
	int frameX, frameY;
	int framecount;
	RECT rc;
	float x, y;
	int width;
	int height;
	float speed;
	int hp;
	int attackNum;	//20210805추가 - 공격횟수카운트필요한 몬스터를 위함.
	bool isHit;		//20210805추가 - 맞았을때 자동 추격위함
	float neverchangeX, neverchangeY;	//20210808추가 - 고정형 보스의 피격시 움직임을 위함.
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
	MONSTERACTIVE oldactivestate;
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


	vector<tagMonster>& getVMonster() { return _vMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

