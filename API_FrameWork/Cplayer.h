#pragma once
#include "singleton.h"

enum class PLACE {
	ROOM,
	DUNGEON
};

enum class STATE {
	IDLE,
	WALK,
	RUN,
	DASH,
	ATTSTAFF,
	STAFFCHARGE,
	PLAYERTALK,
	PLAYER_DIE
};

enum class WEAPONSTATE{
	EMPTY,
	SWORD,
	BOW,
	STAFF
};

struct tagAttackBox {
	RECT rc;
	bool isHit;
};

struct tagDamegeFont {
	int damage;
	bool isActivate;
};

enum DIRECTION
{
	UPLEFT=0,
	UP,
	UPRIGHT,
	RIGHT,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT
};

struct tagInputDirection {
	bool isRight;
	bool isDown;
	bool isLeft;
	bool isUp;
};

struct Player
{
	RECT playerRect;
	PLACE _place;
	tagAttackBox AttackBox;
	WEAPONSTATE weapon;
	float x, y;
	bool isATT;
	int HealthPoint;
};

//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////

class Cplayer : public Singleton<Cplayer>
{
private:
	bool _isDebug;
	bool _isAutoRun;
	bool _frameswitching;
private:
	vector<tagDamegeFont*> _damageFont;
private:
	int ManaPoint;
	int _walkspeed;
	STATE _state;
	Player _player;
	DIRECTION _direction;

	int _count;
	int _index;

	int _frameX;
	int _frameY;
	tagInputDirection _inputDirection;

	int _dashCount;
	int _dashIndex;
	float _dashAngle;

private:

	image* _walk_img;
	image* _run_img;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void imageInit();
	void inputCheck();
	void directionCheck();
	void stateCheck();
	void movePlayer();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	void setPlayerFrame();

	Player& getPlayerAddress() { return _player; }
};