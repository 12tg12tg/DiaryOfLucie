#pragma once
#include "gameNode.h"
class object
{
protected:
	RECT _rc;
	image* _img;
	int _hp;
	bool 

	animation* ani;
	int frameX, frameY;
	int framecount;
	RECT rc;
	RECT footRc;
	RECT bossRc[2];
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
	bool isLeft;		//20210809 - 보스패턴구현
	bool isNextPhase;	//20210809 - 보스패턴구현
	bool oldPhase;		//20210809 - 보스패턴구현
	bool isGraceperiod = false;			//20210809 - 피격시 짧은 무적상태추가
	int gracePeriodCount = 0;
	MONSTERACTIVE activestate;
	MONSTERACTIVE oldactivestate;
	MONSTERMOVESTATE movestate;




	bool _isDebug;
public:

};

