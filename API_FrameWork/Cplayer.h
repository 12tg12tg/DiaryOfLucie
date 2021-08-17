#pragma once
#include "singleton.h"

class bulletManager;
class progressBar;

//////////////////////////////////////////////////

struct tagDamegeFont {
	int damage;
	bool isActivate;
};

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
	ATTSWORD,
	ATTBOWIDLE,
	ATTBOWWALK,
	STAFFCHARGE,
	KNOCKBACK,
	DIE,
	STOP
};
enum class WEAPONTYPE{
	EMPTY,
	SWORD,
	BOW,
	STAFF
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
	LEFT=7
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
	PLACE place;
	WEAPONTYPE weapon;
	float x, y;
	int isHit;
	int isDashHit;
};

struct DashEffect {
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
	Player _player;
	STATE _state;
	tagInputDirection _inputDirection;
	DIRECTION _direction;
	DIRECTION _moveDirection;
	
	float _speed;

	int _knockBackTime;
	int _gracePeriod;
	int _hitCount;
	float _knockBackAngle;
	int _knockBackIndex;

	int _count;
	int _index;

	int _dashCount;
	int _dashIndex;
	float _dashAngle;

	int _attCount;
	int _attIndex;
	float _attAngle;
	int _chargeShotCount;

	int shootingCorrection;

private:
	int imageLeftCorrection;
	int imageTopCorrection;

	image* _walk_img;
	image* _run_img;
	image* _dash_img;
	image* _attStaff_img;
	image* _knockBack_img;
	image* _die_img;
	float _dieAlpha;
	vector<DashEffect> _vectDashEffect;
	vector<DashEffect>::iterator _iterDashEffect;
	
	progressBar* _chargeshotBar;


private:
	bulletManager* _Cbullet;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

private:
	void imageInit();

private:
	void inputCheck();
	void inputDirectionCheck();

private:
	void stateCheck();
	void movePlayer();
	void setPlayerFrame();

private:
	void angleCheckDirection(float angle);

private:
	void pushbackDashEffect(int x,int y, int FrameX,DIRECTION direction);
	void renderDashEffecct(HDC hdc);

	void hitStateCheck();
public:
	void hitDash();
	void hitPlayer(int bulletX, int bulletY);

	void playerStop();

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	void setBulletManagerMemoryLink(bulletManager* BM) { _Cbullet = BM; }
	int getcharge() { return _chargeShotCount; }
	WEAPONTYPE getweapone() { return _player.weapon; }
	Player& getPlayerAddress() { return _player; }
	STATE& getSTATEAddress() { return _state; }
};