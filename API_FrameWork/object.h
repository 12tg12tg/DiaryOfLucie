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
	int attackNum;	//20210805�߰� - ����Ƚ��ī��Ʈ�ʿ��� ���͸� ����.
	bool isHit;		//20210805�߰� - �¾����� �ڵ� �߰�����
	float neverchangeX, neverchangeY;	//20210808�߰� - ������ ������ �ǰݽ� �������� ����.
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
	bool isLeft;		//20210809 - �������ϱ���
	bool isNextPhase;	//20210809 - �������ϱ���
	bool oldPhase;		//20210809 - �������ϱ���
	bool isGraceperiod = false;			//20210809 - �ǰݽ� ª�� ���������߰�
	int gracePeriodCount = 0;
	MONSTERACTIVE activestate;
	MONSTERACTIVE oldactivestate;
	MONSTERMOVESTATE movestate;




	bool _isDebug;
public:

};

