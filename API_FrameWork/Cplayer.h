#pragma once
#include "singleton.h"

class bulletManager;

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
	TALK,
	DIE
};
enum class WEAPONTYPE{
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
	WEAPONTYPE weapon;
	tagAttackBox AttackBox;
	float x, y;
	bool isATT;
	int HealthPoint;
	int ManaPoint;
	int isHit;
};

struct DashEffect {
	image* dashEffect;
	int x, y;
	int dashFrameX;
	DIRECTION direction;
	int dashAlpha;
};

/////////////////////////////////////////////////////////

class Cplayer : public Singleton<Cplayer>
{
private:
	bool _isDebug;
	bool _isAutoRun;
	bool _frameswitching;
private:
	vector<tagDamegeFont*> _damageFont;
private:
	float _walkspeed;
	Player _player;
	tagInputDirection _inputDirection;
	DIRECTION _direction;
	DIRECTION _moveDirection;
	STATE _state;

	int _hitCount;
	int _count;
	int _index;

	int _frameX;
	int _frameY;

	int _dashCount;
	int _dashIndex;
	float _dashAngle;
	int _attCount;
	int _attIndex;
	float _attAngle;

private:

	image* _walk_img;
	image* _run_img;
	image* _dash_img;
	image* _attstaff_img;
	vector<DashEffect> _vectDashEffect;
	vector<DashEffect>::iterator _iterDashEffect;

	bulletManager* _Cbullet;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void imageInit();
	void inputCheck();
	void inputDirectionCheck();
	void stateCheck();
	void movePlayer();
	void setPlayerFrame();
	void angleCheckDirection(float angle);

	void pushbackDashEffect(int x,int y, int FrameX,DIRECTION direction);
	void renderDashEffecct(HDC hdc);

	void hitCheck();

	Player& getPlayerAddress() { return _player; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	void setBulletManagerMemoryLink(bulletManager* BM) { _Cbullet = BM; }
	STATE& getSTATEAddress() { return _state; }
};