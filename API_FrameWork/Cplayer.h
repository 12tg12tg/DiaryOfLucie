#pragma once
#include "animation.h"
#include "singleton.h"

enum class PLACE {
	ROOM,
	DUNGEON
};

enum class STATE{
	IDLE,
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
	int count;
};

//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////

class Cplayer : public Singleton<Cplayer>
{
private:
	bool _isDebug;
private:
	vector<tagDamegeFont*> _damageFont;
private:
	int ManaPoint;
	int _speed;
	STATE _state;
	Player _player;
	DIRECTION _drection;

	int _frameX;
	int _frameY;
	tagInputDirection _inputDirection;

	int _dashCount;
	int _dashIndex;
	float _dashAngle;


private:

	image* _walk_img;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imageInit();
	void animation(DIRECTION direction);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};