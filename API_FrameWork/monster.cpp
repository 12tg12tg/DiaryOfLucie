#include "framework.h"
#include "monster.h"
#include "Cplayer.h"
#include "bulletmanager.h"
monster::monster()
{
}

monster::~monster()
{
}

HRESULT monster::init()
{
	return S_OK;
}

void monster::release()
{
}

void monster::update(Cplayer* py, bulletManager* bm)
{
}

void monster::render()
{
}

void monster::addMonster(float x, float y)
{
}

void monster::move(bulletManager* bm)
{
}

void monster::checkAngle()
{
	if (_viMonster->angle > PI_8 && _viMonster->angle <= PI_8 * 3) {
		_viMonster->movestate = MONSTERMOVESTATE::RIGHTUP;
	}
	else if (_viMonster->angle > PI_8 * 3 && _viMonster->angle <= PI_8 * 5) {
		_viMonster->movestate = MONSTERMOVESTATE::UP;
	}
	else if (_viMonster->angle > PI_8 * 5 && _viMonster->angle <= PI_8 * 7) {
		_viMonster->movestate = MONSTERMOVESTATE::LEFTUP;
	}
	else if (_viMonster->angle > PI_8 * 7 && _viMonster->angle <= PI_8 * 9) {
		_viMonster->movestate = MONSTERMOVESTATE::LEFT;
	}
	else if (_viMonster->angle > PI_8 * 9 && _viMonster->angle <= PI_8 * 11) {
		_viMonster->movestate = MONSTERMOVESTATE::LEFTDOWN;
	}
	else if (_viMonster->angle > PI_8 * 11 && _viMonster->angle <= PI_8 * 13) {
		_viMonster->movestate = MONSTERMOVESTATE::DOWN;
	}
	else if (_viMonster->angle > PI_8 * 13 && _viMonster->angle <= PI_8 * 15) {
		_viMonster->movestate = MONSTERMOVESTATE::RIGHTDOWN;
	}
	else {
		_viMonster->movestate = MONSTERMOVESTATE::RIGHT;
	}
}

void monster::giveFrame()
{
}

void monster::deathCheck()
{
	if (_viMonster->activestate != MONSTERACTIVE::DEATH && _viMonster->hp <= 0) {
		_viMonster->hp = 0;
		_viMonster->activestate = MONSTERACTIVE::DEATH;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
	}
}

void monster::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
}

void monster::stuncheck()
{
}

void monster::checkPlayerXY(Cplayer* py)
{
}

void monster::goOrStay(float speed)
{
	//움직여보고
	_viMonster->x += cosf(_viMonster->angle) * speed;
	_viMonster->y -= sinf(_viMonster->angle) * speed;
	makeCollisionRect();
	//충돌됬다면 실행취소
	RECT temp;
	if (IntersectRect(&temp, &_viMonster->footRc, &PLAYER->getPlayerAddress().playerRect)) {
		_viMonster->x -= cosf(_viMonster->angle) * speed;
		_viMonster->y += sinf(_viMonster->angle) * speed;
		makeCollisionRect();
	}
}

void monster::makeCollisionRect()
{
}

void monster::checkInvincibility()
{
	//무적확인함수
	if (_viMonster->isGraceperiod) {
		_viMonster->gracePeriodCount++;
		if (_viMonster->gracePeriodCount > INVINTIME) {
			_viMonster->gracePeriodCount = 0;
			_viMonster->isGraceperiod = false;
		}
	}
}
