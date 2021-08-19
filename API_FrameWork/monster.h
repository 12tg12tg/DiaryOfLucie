#pragma once
#include "gameNode.h"
#define INVINTIME 8
#define STUNTIME 30

class Cplayer;
class bulletManager;
class motherMap;
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
	ATTACK3,
	DEATH,
};
struct tagMonster
{
	image* img;
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
	bool deathsoundplay = true;
	MONSTERACTIVE activestate;
	MONSTERACTIVE oldactivestate;
	MONSTERMOVESTATE movestate;
};
class monster : public gameNode
{
protected:
	vector<tagMonster> _vMonster;
	vector<tagMonster>::iterator _viMonster;
	motherMap* _motherm;	//20210819 - ���ζ����� �߰�

	bool _stop = true;		//20210819 - �����ǹ��������߰�
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
	virtual void knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun = false);
	virtual void stuncheck();
	virtual void checkPlayerXY(Cplayer* py);
	virtual void goOrStay(float speed);
	virtual void makeCollisionRect(vector<tagMonster>::iterator iter);

	virtual void checkInvincibility();
	virtual void setmotherMapMemoryLink(motherMap* motherMap) { _motherm = motherMap; }
	vector<tagMonster>& getVMonster() { return _vMonster; }
	void setStop(bool st) { _stop = st; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

