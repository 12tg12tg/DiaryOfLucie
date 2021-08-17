#include "framework.h"
#include "Cmonsters.h"
#include "Cplayer.h"
#include "bulletManager.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername					imagename
1.		Csnaby			/		뱀
2.		Cslime			/		슬라임
3.		Cmushman		/		머쉬맨
4	Cmushman_mushroom!	/		머쉬맨_머쉬룸		
5.		Cfairy			/		페어리
6.		Cflime			/		꽃
7.	Cboss_slime			/		보스슬라임
8.	Csemiboss_slime		/		준보스슬라임
9.	Cboss_flime			/		보스플라임
10. Cboss_mushmam		/		보스머쉬맘
11. Cmushmam_mushroom_G	/		머쉬맘_녹색머쉬룸
12. Cmushmam_mushroom2_P/		머쉬맘_보라머쉬룸
13. Cmushmam_mushroom3_B/		머쉬맘_파랑머쉬룸
14.	Cyggdrasil_bomb		/		이그드라실_폭탄
15.		Cyggdrasil		/		이그드라실
16.
17.
*/
//////////////////////////////////////////////////////////////
//////////////////////Csnaby!	뱀!//////////////////////////
//////////////////////////////////////////////////////////////
Csnaby::Csnaby()
{
	IMAGE->addFrameImage("뱀", "images/monsters/snaby-snaby.bmp", 144, 624, 3, 13, true);
}

Csnaby::~Csnaby()
{
}

HRESULT Csnaby::init()
{
	return S_OK;
}

void Csnaby::release()
{
}

void Csnaby::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Csnaby::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}		
	}
	//TCHAR str[128];
	//_stprintf_s(str, "벡터의 갯수 : %d", _vMonster.size());
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	//RectangleMake(getMemDC(), fackpy);
}

void Csnaby::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("뱀");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth()/3 * 2;
	newMonster.height = newMonster.img->getFrameHeight();
	newMonster.rc = RectMake(x+ newMonster.img->getFrameWidth()/6, y, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top+ newMonster.height*2/3, newMonster.width, newMonster.height/3);
	newMonster.speed = 2;
	newMonster.hp = 40;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI*3/2;
	newMonster.range = 350;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Csnaby::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount >= 100) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		if (_viMonster->patternCount < 110) {
			//1씩 움직여보고 충돌됬다면 실행취소
			goOrStay(1);
			//3방향블릿발사
			if (_viMonster->patternCount % 30 == 0) {
				bm->getTriBulInstance()->fire(
					_viMonster->x + _viMonster->img->getFrameWidth()/2,
					_viMonster->y + _viMonster->img->getFrameHeight()/2,
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		if (_viMonster->patternCount < 40) {
			goOrStay(_viMonster->speed);
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha-=2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Csnaby::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 11;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 9;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 8;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 10;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 8; //디폴트
			break;
		}
		maxFrameX = 1;
		break;

	case MONSTERACTIVE::ATTACK:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 7;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 5;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 4;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 6;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 4; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::RNDMOVE:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 12;
		maxFrameX = 0;
		break;
	}

	//X프레임 굴리기
	int currentX = _viMonster->frameX;
	if (_viMonster->framecount % 12 == 0) {
		currentX++;
		if (currentX > maxFrameX) {
			currentX = 0;
		}
		_viMonster->frameX = currentX;
	}
}

void Csnaby::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
	if (stun) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Csnaby::stuncheck()
{
	if (_viMonster->isStun && _viMonster->activestate != MONSTERACTIVE::DEATH) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > STUNTIME) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->isStun = false;
		}
	}
}

void Csnaby::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Csnaby::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////////////////Cslime!	슬라임!////////////////////////
//////////////////////////////////////////////////////////////
Cslime::Cslime()
{
	IMAGE->addFrameImage("슬라임", "images/monsters/slime.bmp", 180, 780, 3, 13, true);
}

Cslime::~Cslime()
{
}

HRESULT Cslime::init()
{
	return S_OK;
}

void Cslime::release()
{
}

void Cslime::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cslime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cslime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("슬라임");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth() / 3 * 2;
	newMonster.height = newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() / 6, y + newMonster.img->getFrameWidth() / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height * 2 / 3, newMonster.width, newMonster.height / 3);
	newMonster.speed = 2;
	newMonster.hp = 49;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 350;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cslime::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount >30 && _viMonster->patternCount < 60) {
			goOrStay(_viMonster->speed);
		}
		if (_viMonster->patternCount >= 150) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		if (_viMonster->patternCount < 35) {
			if (_viMonster->patternCount % 30 == 0) {
				bm->getTriBulInstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 10);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount < 110) {
			if (_viMonster->patternCount == 15) {
				_viMonster->y -= 25;
			}
			if (_viMonster->patternCount == 30) {
				_viMonster->y += 25;
			}
			if (_viMonster->patternCount == 45) {
				_viMonster->y -= 25;
			}
			if (_viMonster->patternCount == 60) {
				_viMonster->y += 25;
			}
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y + _viMonster->img->getFrameWidth() / 4, _viMonster->width, _viMonster->height - _viMonster->img->getFrameWidth() / 4);
			if (_viMonster->patternCount % 97 == 0) {
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		if (_viMonster->patternCount < 35) {
			goOrStay(_viMonster->speed);
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cslime::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
	case MONSTERACTIVE::RNDMOVE:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::ATTACK:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 11;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 9;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 8;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 10;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 8; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount == 75) {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
		}
		if (_viMonster->patternCount > 75) {
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				_viMonster->frameY = 7;
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				_viMonster->frameY = 5;
				break;
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				_viMonster->frameY = 4;
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				_viMonster->frameY = 6;
				break;
			case MONSTERMOVESTATE::NONE:
				_viMonster->frameY = 4; //디폴트
				break;
			}
		}
		maxFrameX = 2;
		break;


	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 12;
		maxFrameX = 2;
		break;
	}

	//X프레임 굴리기
	int currentX = _viMonster->frameX;
	if (_viMonster->framecount % 12 == 0) {
		currentX++;
		if (currentX > maxFrameX) {
			currentX = 0;
		}
		_viMonster->frameX = currentX;
	}
}

void Cslime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameWidth() / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
	if (stun) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cslime::stuncheck()
{
	if (_viMonster->isStun && _viMonster->activestate != MONSTERACTIVE::DEATH) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > STUNTIME) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->isStun = false;
		}
	}
}

void Cslime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if(_viMonster->oldactivestate == MONSTERACTIVE::ATTACK) _viMonster->activestate = MONSTERACTIVE::ATTACK2;
		else _viMonster->activestate = MONSTERACTIVE::ATTACK;
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Cslime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameWidth() / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////////////////Cmushman!	머쉬맨!///////////////////////
//////////////////////////////////////////////////////////////
Cmushman::Cmushman()
{
	IMAGE->addFrameImage("머쉬맨", "images/monsters/mushman-mushman.bmp", 144, 935, 3, 17, true);
}

Cmushman::~Cmushman()
{
}

HRESULT Cmushman::init()
{
	return S_OK;
}

void Cmushman::release()
{
}

void Cmushman::update(Cplayer* py, bulletManager* bm, Cmushman_mushroom* _mushroom)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm, _mushroom);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cmushman::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
	}
	//TCHAR str[128];
	//_stprintf_s(str, "플레이어좌표 : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushman::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("머쉬맨");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth() / 3 * 2;
	newMonster.height = newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() / 6, y, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(x + newMonster.img->getFrameWidth() / 6, y + newMonster.height*2/3, newMonster.width, newMonster.height / 3);
	newMonster.speed = 2;
	newMonster.hp = 77;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 350;
	newMonster.stunCount = 0;
	newMonster.patternCount = 400;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cmushman::move(bulletManager* bm, Cmushman_mushroom* _mushroom)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount <= 600) {
			//몇백30이상이면 RNDMOVE로 진입
			if (_viMonster->patternCount % 100 > 0 && _viMonster->patternCount % 100 < 30) {
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
			}
			//몇백일 때 방향확인하고 각 바꾸기
			if (_viMonster->patternCount % 100 == 0)
				_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		else _viMonster->activestate = MONSTERACTIVE::FINDING;
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		if (_viMonster->patternCount < 120) {

		}
		else {
			_mushroom->addMonster(_viMonster->x, _viMonster->y);
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		//움직이다가
		if (_viMonster->patternCount % 100 < 30) {
			goOrStay(_viMonster->speed);
		}
		//몇백60이상이면 NONE으로 돌아가기
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cmushman::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 9;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 7;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 6;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 8;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 6; //디폴트
			break;
		}
		maxFrameX = 1;
		break;

	case MONSTERACTIVE::ATTACK:
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::RNDMOVE:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 10;
		maxFrameX = 0;
		break;
	}

	//X프레임 굴리기1(공격이 아닐때)
	if (_viMonster->activestate != MONSTERACTIVE::ATTACK) {
		int currentX = _viMonster->frameX;
		if (_viMonster->framecount % 12 == 0) {
			currentX++;
			if (currentX > maxFrameX) {
				currentX = 0;
			}
			_viMonster->frameX = currentX;
		}
	}
	//x프레임 굴리기2(공격일 때)
	else {
		if (_viMonster->framecount < 12) {
			_viMonster->frameX = 0;
			_viMonster->frameY = 4;
		}
		else if (_viMonster->framecount < 24) {
			_viMonster->frameX = 1;
			_viMonster->frameY = 4;
		}
		else if (_viMonster->framecount < 36) {
			_viMonster->frameX = 2;
			_viMonster->frameY = 4;
		}
		else if (_viMonster->framecount < 48) {
			_viMonster->frameX = 0;
			_viMonster->frameY = 5;
		}
		else if (_viMonster->framecount < 60) {
			_viMonster->frameX = 2;
			_viMonster->frameY = 4;
		}
		else if (_viMonster->framecount < 72) {
			_viMonster->frameX = 0;
			_viMonster->frameY = 5;
		}
		else if (_viMonster->framecount < 84) {
			_viMonster->frameX = 2;
			_viMonster->frameY = 4;
		}
		else if (_viMonster->framecount < 96) {
			_viMonster->frameX = 0;
			_viMonster->frameY = 5;
		}
		else if (_viMonster->framecount < 108) {
			_viMonster->frameX = 1;
			_viMonster->frameY = 5;
		}
		else {
			_viMonster->frameX = 2;
			_viMonster->frameY = 5;
		}
	}
}

void Cmushman::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백 - 버섯은 넉백안함.
	//float centerx, centery;
	//centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	//centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	//float nbangle = UTIL::getAngle(x, y, centerx, centery);
	//iter->x += cosf(nbangle) * knockbackRange;
	//iter->y -= sinf(nbangle) * knockbackRange;
	//iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y, iter->width, iter->height);
	//iter->footRc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->height * 2 / 3, iter->width, iter->height / 3);

	if (stun) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cmushman::stuncheck()
{
	if (_viMonster->isStun && _viMonster->activestate != MONSTERACTIVE::DEATH) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > STUNTIME) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->patternCount = 400;
			_viMonster->isStun = false;
		}
	}
}

void Cmushman::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		//목표 지점과 각 설정(사거리 내라면 도망가기)
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		float tempangle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY) - PI;
		if (tempangle < 0) tempangle += PI2;
		if (tempangle > PI2) tempangle -= PI2;
		_viMonster->angle = (tempangle);
	}
	else {
		//사거리내가 아니라면 다가가기
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//얘는 특이하게, NONE일때 FIND를 주기적으로 실행.
	//고로 패턴카운트가 몇이냐에따라 다시 NONE으로 갈지 ATTACK으로 갈지 결정됨.
	if (_viMonster->patternCount < 600)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->activestate = MONSTERACTIVE::NONE;
	}
	else {
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
	}
}

void Cmushman::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y, iter->width, iter->height);
	iter->footRc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Cmushman_mushroom!	머쉬맨_머쉬룸!/////////////////
//////////////////////////////////////////////////////////////
Cmushman_mushroom::Cmushman_mushroom()
{
	IMAGE->addFrameImage("머쉬맨_머쉬룸", "images/monsters/mushman_mushroom.bmp", 144, 220, 3, 4, true);
}

Cmushman_mushroom::~Cmushman_mushroom()
{
}

HRESULT Cmushman_mushroom::init()
{
	return S_OK;
}

void Cmushman_mushroom::release()
{
}

void Cmushman_mushroom::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() * 3 / 8, _viMonster->y + _viMonster->img->getFrameHeight() * 3 / 4, _viMonster->width, _viMonster->height);
		_viMonster->footRc = RectMake(_viMonster->rc.left, _viMonster->rc.top + _viMonster->height / 2, _viMonster->width, _viMonster->height / 2);

		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cmushman_mushroom::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
	}
	//TCHAR str[128];
	//_stprintf_s(str, "플레이어좌표 : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushman_mushroom::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("머쉬맨_머쉬룸");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.neverchangeX = x;
	newMonster.neverchangeY = y;
	newMonster.width = newMonster.img->getFrameWidth() / 4 + 1;
	newMonster.height = newMonster.img->getFrameHeight() / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() * 3 / 8, y + newMonster.img->getFrameHeight() * 3 / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height / 2, newMonster.width, newMonster.height/2);
	newMonster.speed = 2;
	newMonster.hp = 36;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1500;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cmushman_mushroom::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount % 70 == 0) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		bm->getHomBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
			_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
			_viMonster->angle, 0);
		_viMonster->activestate = MONSTERACTIVE::NONE;
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount == 60) {
			int snum = RND->getInt(2);
			if (snum == 0) {
				bm->getCirBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right- _viMonster->rc.left)/2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
					_viMonster->angle, 0);
			}
			else {
				bm->getPsnBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
					_viMonster->angle, 0);
			}
			_viMonster->afterDeath = true;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cmushman_mushroom::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
	case MONSTERACTIVE::ATTACK:
	case MONSTERACTIVE::RNDMOVE:
		_viMonster->frameY = 0;
		maxFrameX = 2;
		break;
	case MONSTERACTIVE::ATTACK2:
		_viMonster->frameY = 3;
		maxFrameX = 2;
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 0;
		maxFrameX = 0;
		break;
	}

	//X프레임 굴리기1(공격이 아닐때)
	if (_viMonster->activestate != MONSTERACTIVE::ATTACK2) {
		int currentX = _viMonster->frameX;
		if (_viMonster->framecount % 12 == 0) {
			currentX++;
			if (currentX > maxFrameX) {
				currentX = 0;
			}
			_viMonster->frameX = currentX;
		}
	}
	//X프레임 굴리기2(폭발공격)
	else {
		int currentX = _viMonster->frameX;
		if (_viMonster->framecount % 15 == 0) {
			currentX++;
			if (currentX > maxFrameX) {
				currentX = 0;
			}
			_viMonster->frameX = currentX;
		}
	}
}

void Cmushman_mushroom::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//버섯은 스턴이 없는걸로..
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cmushman_mushroom::stuncheck()
{
}

void Cmushman_mushroom::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//목표 지점과 각 설정
	_viMonster->targetX = PLAYER->getPlayerAddress().x;
	_viMonster->targetY = PLAYER->getPlayerAddress().y;
	_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
		_viMonster->targetX, _viMonster->targetY);
	if (_viMonster->patternCount >= 350) {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK2;
	}
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
	}
}

void Cmushman_mushroom::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
////////////////Cfairy!				페어리!///////////////////
//////////////////////////////////////////////////////////////
Cfairy::Cfairy()
{
	IMAGE->addFrameImage("페어리", "images/monsters/fairy-forest.bmp", 168, 930, 3, 10, true);
}

Cfairy::~Cfairy()
{
}

HRESULT Cfairy::init()
{
	return S_OK;
}

void Cfairy::release()
{
}

void Cfairy::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cfairy::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL3);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL4, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "현재프레임X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cfairy::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("페어리");
	newMonster.frameX = 1;
	newMonster.frameY = 0;
	newMonster.framecount = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth() / 3;
	newMonster.height = newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() / 3, y + newMonster.img->getFrameHeight() / 5, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height*3/4, newMonster.width, newMonster.height/4);
	newMonster.speed = 1;
	newMonster.hp = 77;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI *3 / 2;
	newMonster.range = 450;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 0;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cfairy::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount % 100 == 30)
		{
			_viMonster->framecount = 0;
			_viMonster->frameX = 1;
			_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		}
		if (_viMonster->patternCount > 150) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		if (_viMonster->patternCount < 35) {
			if (_viMonster->patternCount % 30 == 0) {
				bm->getWidBulInstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 1;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount < 35) {
			if (_viMonster->patternCount % 30 == 0) {
				bm->getRtnBulInstance()->fire(
					RecCenX(_viMonster->rc)+20,
					RecCenY(_viMonster->rc)+20,
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 1;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
		}	
		break;
	case MONSTERACTIVE::RNDMOVE:
		if (_viMonster->patternCount < 60) {
			goOrStay(_viMonster->speed);
		}
		else {
			_viMonster->frameX = 1;
			_viMonster->framecount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cfairy::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
	case MONSTERACTIVE::RNDMOVE:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::ATTACK:
	case MONSTERACTIVE::ATTACK2:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 7;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 5;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 4;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 6;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 4; //디폴트
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::DEATH:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 9;
			_viMonster->frameX = 1;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 8;
			_viMonster->frameX = 2;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 8;
			_viMonster->frameX = 1;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 9;
			_viMonster->frameX = 0;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 8; //디폴트
			_viMonster->frameX = 1; //디폴트
			break;
		}
		maxFrameX = 0;
		break;
	}

	int currentX = _viMonster->frameX;
	//정지상태일땐 x프레임 고정
	if (_viMonster->activestate == MONSTERACTIVE::NONE||_viMonster->activestate == MONSTERACTIVE::FINDING) {
		_viMonster->frameX = 1;
	}
	//죽었을 땐 한번만 증가
	else if (_viMonster->activestate == MONSTERACTIVE::DEATH){
		if (_viMonster->framecount > 12) {
			_viMonster->frameY = 8;
			_viMonster->frameX = 0;
		}
	}
	//움직이거나 공격중일 땐 X프레임 굴리기
	else {
		if (_viMonster->framecount % 12 == 0) {
			currentX++;
			if (currentX > maxFrameX) {
				currentX = 0;
			}
			_viMonster->frameX = currentX;
		}
	}
}

void Cfairy::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 3, iter->y + iter->img->getFrameHeight() / 5, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 3 / 4, iter->width, iter->height / 4);
	if (stun) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cfairy::stuncheck()
{
	if (_viMonster->isStun && _viMonster->activestate != MONSTERACTIVE::DEATH) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > STUNTIME) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->isStun = false;
		}
	}
}

void Cfairy::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK && _viMonster->attackNum >= 2) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
			_viMonster->attackNum = 0;
		}
		else {
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
			_viMonster->attackNum++;
		}
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 1;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Cfairy::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 3, iter->y + iter->img->getFrameHeight() / 5, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 3 / 4, iter->width, iter->height / 4);
}
//////////////////////////////////////////////////////////////
////////////////Cflime!				꽃!///////////////////////
//////////////////////////////////////////////////////////////
Cflime::Cflime()
{
	IMAGE->addFrameImage("꽃", "images/monsters/flime-flime.bmp", 240, 549, 3, 9, true);
}

Cflime::~Cflime()
{
}

HRESULT Cflime::init()
{
	return S_OK;
}

void Cflime::release()
{
}

void Cflime::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() / 4, _viMonster->width, _viMonster->height);;
		_viMonster->footRc = RectMake(_viMonster->rc.left, _viMonster->rc.top + _viMonster->height * 2 / 3, _viMonster->width, _viMonster->height / 3);
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cflime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "스턴카운트 : %d", _viMonster->stunCount);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cflime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("꽃");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.neverchangeX = x;
	newMonster.neverchangeY = y;
	newMonster.width = newMonster.img->getFrameWidth() / 2;
	newMonster.height = newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() / 4, y + newMonster.img->getFrameHeight() / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height*2/3, newMonster.width, newMonster.height/3);
	newMonster.speed = 0;
	newMonster.hp = 57;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 450;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 0;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cflime::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount > 140) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		if (_viMonster->patternCount < 280) {
			if (_viMonster->patternCount == 55) {
				bm->getnidBulInstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					_viMonster->angle, 0);
			}
			else if (_viMonster->patternCount == 85) {
				bm->getnidBulInstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					_viMonster->angle, 0);
			}
			else if (_viMonster->patternCount == 115) {
				bm->getnidBulInstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount < 48) {
		}
		else if (_viMonster->patternCount == 48) {
			bm->getPsnBulInstance()->fire(
				RecCenX(_viMonster->rc),
				RecCenY(_viMonster->rc),
				_viMonster->angle, 0);
		}
		else if (_viMonster->patternCount < 270) {
			//잠시 독구름 사라질떄까지 대기
		}
		else {
			//공격상태 해제
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cflime::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8방향과 상태에 따른 Y프레임 고르기
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
	case MONSTERACTIVE::FINDING:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 1;
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::ATTACK:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 7;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 5;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 4;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 6;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 4; //디폴트
			break;
		}
		maxFrameX = 2;
		break;
	case MONSTERACTIVE::ATTACK2:
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			_viMonster->frameY = 3;
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			_viMonster->frameY = 1;
			break;
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			_viMonster->frameY = 0;
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			_viMonster->frameY = 2;
			break;
		case MONSTERMOVESTATE::NONE:
			_viMonster->frameY = 0; //디폴트
			break;
		}
		maxFrameX = 1;
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 8;
		maxFrameX = 0;
		break;
	}

	int currentX = _viMonster->frameX;
	//땅에뿌리꽂기 공격. 마지막 프레임에서 멈춰있기.
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK)
	{
		if (_viMonster->patternCount < 250) {
			if (_viMonster->framecount % 15 == 0) {
				if (currentX < maxFrameX) {
					currentX++;
					_viMonster->frameX = currentX;
				}
				else {
					_viMonster->framecount = 0;
				}
			}
		}
		else {
			//프레임감소
			if (_viMonster->framecount % 15 == 0) {
				currentX--;
				_viMonster->frameX = currentX;
				if (currentX < 0) {
					_viMonster->frameX = 0;
				}
			}
		}
	}
	else if (_viMonster->activestate == MONSTERACTIVE::ATTACK2)
	{
		//공격2 상태가 되자마자 기모으는 모션
		if (_viMonster->patternCount < 40) {
			_viMonster->frameX = 2;
		}
		else if (_viMonster->patternCount < 60) {
			_viMonster->frameX = 1;
		}
		else{
			if (_viMonster->framecount % 15 == 0) {
				currentX++;
				if (currentX > maxFrameX) {
					currentX = 0;
				}
				_viMonster->frameX = currentX;
			}
		}
	}
	//NONE이거나 DEATH일땐 정상프레임.
	else {
		if (_viMonster->framecount % 15 == 0) {
			currentX++;
			if (currentX > maxFrameX) {
				currentX = 0;
			}
			_viMonster->frameX = currentX;
		}
	}
}

void Cflime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
	if (stun) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cflime::stuncheck()
{
	if (_viMonster->isStun && _viMonster->activestate!= MONSTERACTIVE::DEATH) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > STUNTIME) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->isStun = false;
		}
	}
}

void Cflime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK && _viMonster->attackNum >= 2) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
			_viMonster->attackNum = 0;
		}
		else {
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
			_viMonster->attackNum++;
		}
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 NONE 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::NONE;
		_viMonster->angle = DEGREE(270);
	}
}

void Cflime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Cboss_slime!		보스슬라임!///////////////////////
//////////////////////////////////////////////////////////////
Cboss_slime::Cboss_slime()
{
	IMAGE->addFrameImage("보스슬라임", "images/monsters/boss_KingSlime.bmp", 576*2, 2496*2, 3, 13, true);
	EFFECT->addEffect("킹슬라임점프", "images/monsters/skill_slime_jump_effect.bmp", ZEFFECT1, 960, 384, 192, 192, 1, 0.3f, 5, 100);
}

Cboss_slime::~Cboss_slime()
{
}

HRESULT Cboss_slime::init()
{
	return S_OK;
}

void Cboss_slime::release()
{
}

void Cboss_slime::update(Cplayer* py, bulletManager* bm, Csemiboss_slime* ss)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		//stuncheck();
		checkPlayerXY(py);
		move(bm, ss);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cboss_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			if (_viMonster->activestate==MONSTERACTIVE::ATTACK2 && _viMonster->patternCount % 100 == 0)
				EFFECT->play("킹슬라임점프", _viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.bottom);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "현재프레임X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cboss_slime::addMonster(float centerx, float centery)
{

	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("보스슬라임");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("보스슬라임", 0, 2, 8, true, true);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.width = newMonster.img->getFrameWidth() / 2;
	newMonster.height = newMonster.img->getFrameHeight() / 3;
	newMonster.x = centerx - newMonster.img->getFrameWidth() / 2 ;
	newMonster.y = centery - newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 4, newMonster.y + newMonster.img->getFrameHeight() * 2 / 3, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height*2/3, newMonster.width, newMonster.height/3);
	newMonster.speed = 2;
	newMonster.hp = 220;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1000;
	newMonster.framecount = 0;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 2;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cboss_slime::move(bulletManager* bm, Csemiboss_slime* ss)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount > 30 && _viMonster->patternCount < 60) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 3, _viMonster->width, _viMonster->height);
			_viMonster->footRc = RectMake(_viMonster->rc.left, _viMonster->rc.top + _viMonster->height * 2 / 3, _viMonster->width, _viMonster->height / 3);
		}
		if (_viMonster->patternCount >= 120) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
		_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
		_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 3, _viMonster->width, _viMonster->height);
		_viMonster->footRc = RectMake(_viMonster->rc.left, _viMonster->rc.top + _viMonster->height * 2 / 3, _viMonster->width, _viMonster->height / 3);
		if (_viMonster->patternCount < 35) {
			if (_viMonster->patternCount % 30 == 0) {
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 30);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount < 110) {
			if (_viMonster->patternCount == 15) {
				_viMonster->y -= 100;
			}
			if (_viMonster->patternCount == 30) {
				_viMonster->y += 100;
			}
			if (_viMonster->patternCount == 45) {
				_viMonster->y -= 100;
			}
			if (_viMonster->patternCount == 60) {
				_viMonster->y += 100;
			}
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 3, _viMonster->width, _viMonster->height);
			if (_viMonster->patternCount % 100 == 0) {
				bm->getSlmBos1Bullnstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		if (_viMonster->patternCount < 35) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 3, _viMonster->width, _viMonster->height);
			_viMonster->footRc = RectMake(_viMonster->rc.left, _viMonster->rc.top + _viMonster->height * 2 / 3, _viMonster->width, _viMonster->height / 3);
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			ss->addMonster(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2 - 30,
				_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2);
			ss->addMonster(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2 + 30,
				_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2);
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cboss_slime::giveFrame()
{
	if (_viMonster->framecount == 0) {
		//8방향과 상태에 따른 애니메이션 고르기
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 9, 11, 8, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 3, 5, 8, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 0, 2, 8, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 6, 8, 8, true, true);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::ATTACK:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 33, 35, 5, false, false);
				break;											
			case MONSTERMOVESTATE::LEFTUP:						
			case MONSTERMOVESTATE::LEFT:						
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 27, 29, 5, false, false);
				break;												
			case MONSTERMOVESTATE::NONE:							
			case MONSTERMOVESTATE::LEFTDOWN:						
			case MONSTERMOVESTATE::DOWN:							
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 24, 26, 5, false, false);
				break;											
			case MONSTERMOVESTATE::RIGHTDOWN:					
			case MONSTERMOVESTATE::RIGHT:						
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 30, 32, 5, false, false);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 12;
			_viMonster->frameX = 0;
			break;
		}
	}

	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2 && _viMonster->framecount == 75) {
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 21, 23, 5, false, false);
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 15, 17, 5, false, false);
			break;
		case MONSTERMOVESTATE::NONE:
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 12, 14, 5, false, false);
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스슬라임", 18, 20, 5, false, false);
			break;
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;

}

void Cboss_slime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	if (iter->activestate != MONSTERACTIVE::ATTACK2) {
		iter->x += cosf(nbangle) * knockbackRange;
		iter->y -= sinf(nbangle) * knockbackRange;
		iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
		iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);

	}
	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cboss_slime::stuncheck(){}

void Cboss_slime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if (_viMonster->attackNum == 3 && _viMonster->oldactivestate == MONSTERACTIVE::ATTACK) {
			_viMonster->attackNum = 0;
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
		}
		else {
			_viMonster->attackNum++;
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
		}
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Cboss_slime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Csemiboss_slime!		준보스슬라임!//////////////////
//////////////////////////////////////////////////////////////
Csemiboss_slime::Csemiboss_slime()
{
	IMAGE->addFrameImage("준보스슬라임", "images/monsters/boss_KingSlime.bmp", 576, 2496, 3, 13, true);
}

Csemiboss_slime::~Csemiboss_slime()
{
}

HRESULT Csemiboss_slime::init()
{
	return S_OK;
}

void Csemiboss_slime::release()
{
}

void Csemiboss_slime::update(Cplayer* py, bulletManager* bm, Cslime* slm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		//stuncheck();
		checkPlayerXY(py);
		move(bm, slm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Csemiboss_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			if (_viMonster->activestate == MONSTERACTIVE::ATTACK2 && _viMonster->patternCount % 100 == 0)
				EFFECT->play("킹슬라임점프", _viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.bottom);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "현재프레임X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Csemiboss_slime::addMonster(float centerx, float centery)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("준보스슬라임");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("준보스슬라임", 0, 2, 8, true, true);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.width = newMonster.img->getFrameWidth() / 2;
	newMonster.height = newMonster.img->getFrameHeight() / 3;
	newMonster.x = centerx - newMonster.img->getFrameWidth() / 2;
	newMonster.y = centery - newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.rc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 4, newMonster.y + newMonster.img->getFrameHeight() * 2 / 3, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height/2, newMonster.width, newMonster.height/2);
	newMonster.speed = 2;
	newMonster.hp = 70;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1000;
	newMonster.framecount = 0;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 0;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::ATTACK;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Csemiboss_slime::move(bulletManager* bm, Cslime* slm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount > 30 && _viMonster->patternCount < 60) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			makeCollisionRect(_viMonster);
		}
		if (_viMonster->patternCount >= 100) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
		_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
		makeCollisionRect(_viMonster);
		if (_viMonster->patternCount < 35) {
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		if (_viMonster->patternCount < 110) {
			if (_viMonster->patternCount == 15) {
				_viMonster->y -= 100;
			}
			if (_viMonster->patternCount == 30) {
				_viMonster->y += 100;
			}
			if (_viMonster->patternCount == 45) {
				_viMonster->y -= 100;
			}
			if (_viMonster->patternCount == 60) {
				_viMonster->y += 100;
			}
			if (_viMonster->patternCount == 75) {
				_viMonster->y -= 100;
			}
			if (_viMonster->patternCount == 90) {
				_viMonster->y += 100;
			}
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 4, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 3, _viMonster->width, _viMonster->height);
			if (_viMonster->patternCount > 75 && _viMonster->patternCount < 100) {
				_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed*2;
				_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed*2;
				makeCollisionRect(_viMonster);
			}
			if (_viMonster->patternCount % 100 == 0) {
				//목표 지점과 각 설정
				_viMonster->targetX = PLAYER->getPlayerAddress().x;
				_viMonster->targetY = PLAYER->getPlayerAddress().y;
				_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2, _viMonster->targetX, _viMonster->targetY);
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc),
					RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		if (_viMonster->patternCount < 35) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			makeCollisionRect(_viMonster);
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			slm->addMonster(RecCenX(_viMonster->rc) - 30, 
				RecCenY(_viMonster->rc)-10);
			slm->addMonster(RecCenX(_viMonster->rc) + 30,
				RecCenY(_viMonster->rc)+10);
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Csemiboss_slime::giveFrame()
{
	if (_viMonster->framecount == 0) {
		//8방향과 상태에 따른 애니메이션 고르기
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 9, 11, 8, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 3, 5, 8, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 0, 2, 8, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 6, 8, 8, true, true);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::ATTACK:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 33, 35, 5, false, false);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 27, 29, 5, false, false);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 24, 26, 5, false, false);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 30, 32, 5, false, false);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 12;
			_viMonster->frameX = 0;
			break;
		}
	}

	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2 && _viMonster->framecount == 75) {
		switch (_viMonster->movestate)
		{
		case MONSTERMOVESTATE::RIGHTUP:
		case MONSTERMOVESTATE::UP:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 21, 23, 5, false, false);
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 15, 17, 5, false, false);
			break;
		case MONSTERMOVESTATE::NONE:
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 12, 14, 5, false, false);
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "준보스슬라임", 18, 20, 5, false, false);
			break;
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;

}

void Csemiboss_slime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	if(iter->activestate != MONSTERACTIVE::ATTACK2)
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Csemiboss_slime::stuncheck() {}

void Csemiboss_slime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
		}
		else {
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
		}
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Csemiboss_slime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
//////////Cboss_flime!			보스플라임!////////////////////
//////////////////////////////////////////////////////////////
Cboss_flime::Cboss_flime()
{
	IMAGE->addFrameImage("보스플라임", "images/monsters/flime-bossFlime.bmp", 750, 1710, 3, 9, true);
}

Cboss_flime::~Cboss_flime()
{
}

HRESULT Cboss_flime::init()
{
	return S_OK;
}

void Cboss_flime::release()
{
}

void Cboss_flime::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		makeCollisionRect(_viMonster);
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cboss_flime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cboss_flime::addMonster(float centerx, float centery)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("보스플라임");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("보스플라임", 1, 2, 3, true, true);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.width = newMonster.img->getFrameWidth() * 2 / 3;
	newMonster.height = newMonster.img->getFrameHeight() * 2 / 3;
	newMonster.x = centerx - newMonster.img->getFrameWidth() / 2;
	newMonster.y = centery - newMonster.img->getFrameHeight() * 2 / 3;
	newMonster.neverchangeX = newMonster.x;
	newMonster.neverchangeY = newMonster.y;
	newMonster.rc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 6, newMonster.y + newMonster.img->getFrameHeight() * 2 / 7, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height*2/3, newMonster.width, newMonster.height/3);
	newMonster.speed = 0;
	newMonster.hp = 450;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1000;
	newMonster.framecount = 0;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 0;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cboss_flime::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount > 100) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//독과 원형블릿 동시에 발사 (원형은 3번)
		if (_viMonster->patternCount < 280) {
			if (_viMonster->patternCount == 55) {
				bm->getLPsnBulInstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
			else if (_viMonster->patternCount == 85) {
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					_viMonster->angle + 0.3, 0);
			}
			else if (_viMonster->patternCount == 115) {
				bm->getCirBulInstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					_viMonster->angle, 0);
			}
		}
		else if (_viMonster->patternCount >= 280 && _viMonster->patternCount < 350) {
			//휴식
		}
		else {
			_viMonster->frameX = 0;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		//둘중하나. 가시감옥 또는 가시줄기.
		if (_viMonster->attackNum == 1) {
			//가시감옥
			if (_viMonster->patternCount == 55) {
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					1);
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					13);
			}
			else if (_viMonster->patternCount == 205) {
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					10);
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					24);
			}
			else if (_viMonster->patternCount == 355) {
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					1);
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					13);
				bm->getFlwBos2Bullnstance()->fire(
					PLAYER->getPlayerAddress().x,
					PLAYER->getPlayerAddress().y,
					32);
			}
			else if (_viMonster->patternCount < 505) {
				//휴식
			}
			else {
				//공격상태 해제
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::NONE;
				_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
			}
		}
		else {
			//가시 줄기
			if (_viMonster->patternCount == 55) {
				bm->getFlwBos1Bullnstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					RND->getInt(2), 0);
			}
			else if (_viMonster->patternCount == 90) {
				//빨간총알
				bm->getFlwBos3Bullnstance()->fire(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), 0);
			}
			else if (_viMonster->patternCount < 505) {
				//휴식
			}
			else {
				//공격상태 해제
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::NONE;
				_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
			}
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cboss_flime::giveFrame()
{
	if (_viMonster->framecount == 0) {
		//8방향과 상태에 따른 애니메이션 고르기
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스플라임", 1, 2, 3, true, true);
				break;
			}
			break;

		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 8;
			_viMonster->frameX = 0;
			break;
		}
	}

	//ATTACK1 : 원형블릿공격일때 앞부분만 프레임 돌기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스플라임", 2, 0, 4, true, true);
		}
		else if(_viMonster->framecount == 200){
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스플라임", 1, 2, 3, true, true);
		}
	}
	//ATTACK2 : 원형블릿공격일때 앞부분만 프레임 돌기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스플라임", 12, 14, 3, false, false);
		}
		else if (_viMonster->framecount == 445) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스플라임", 14, 12, 3, false, false);
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;

}

void Cboss_flime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameHeight() * 2 / 7, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);

	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cboss_flime::stuncheck()
{
}

void Cboss_flime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
			_viMonster->attackNum++;
			if (_viMonster->attackNum == 3) _viMonster->attackNum = 1;
		}
		else {
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
		}
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}

void Cboss_flime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameHeight() * 2 / 7, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Cboss_mushmam!			보스머쉬맘!////////////////
//////////////////////////////////////////////////////////////
Cboss_mushmam::Cboss_mushmam()
{
	IMAGE->addFrameImage("보스머쉬맘", "images/monsters/mushmam-mushmam.bmp", 432, 2475, 3, 15, true);
}

Cboss_mushmam::~Cboss_mushmam()
{
}

HRESULT Cboss_mushmam::init()
{
	return S_OK;
}

void Cboss_mushmam::release()
{
}

void Cboss_mushmam::update(Cplayer* py, bulletManager* bm, Cmushmam_mushroom_G* mrG, Cmushmam_mushroom_P* mrP, Cmushmam_mushroom_B* mrB, Cmushman_mushroom* smr)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkPlayerXY(py);
		move(bm, mrG, mrP, mrB, smr);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cboss_mushmam::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cboss_mushmam::addMonster(float centerx, float centery)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("보스머쉬맘");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("보스머쉬맘", 18, 19, 3, true, true);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.width = newMonster.img->getFrameWidth() * 2 / 3;
	newMonster.height = newMonster.img->getFrameHeight() * 3 / 4;
	newMonster.x = centerx - newMonster.img->getFrameWidth() / 2;
	newMonster.y = centery - newMonster.img->getFrameHeight() / 2;
	newMonster.rc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 6, newMonster.y + 2, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height*2/3, newMonster.width, newMonster.height/3);
	newMonster.speed = 2;
	newMonster.hp = 450;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 340;
	newMonster.framecount = 0;
	newMonster.stunCount = 0;
	newMonster.patternCount = 300;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 1;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cboss_mushmam::move(bulletManager* bm, Cmushmam_mushroom_G* mrG, Cmushmam_mushroom_P* mrP, Cmushmam_mushroom_B* mrB, Cmushman_mushroom* smr)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount < 550) {
			//몇백30이상이면 RNDMOVE로 진입
			if (_viMonster->patternCount % 100 > 0 && _viMonster->patternCount % 100 < 30) {
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
			}
			//몇백일 때 방향확인하고 각 바꾸기
			if (_viMonster->patternCount % 100 == 0)
				_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		else _viMonster->activestate = MONSTERACTIVE::FINDING;
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//심기
		if (_viMonster->patternCount < 150) {
		}
		else {
			if(color == 0) mrG->addMonster(_viMonster->x, _viMonster->y);
			else if (color == 1) mrP->addMonster(_viMonster->x, _viMonster->y);
			else mrB->addMonster(_viMonster->x, _viMonster->y);			
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		//뿌리기
		if (_viMonster->patternCount < 120) {
		}
		else {
			smr->addMonster(_viMonster->x-20, _viMonster->y);
			smr->addMonster(_viMonster->x+120, _viMonster->y);
			smr->addMonster(_viMonster->x+60, _viMonster->y+70);
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		//움직이다가
		if (_viMonster->patternCount % 100 < 30) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			makeCollisionRect(_viMonster);
		}
		//몇백30이상이면 NONE으로 돌아가기
		else {
			_viMonster->framecount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cboss_mushmam::giveFrame()
{
	if (_viMonster->framecount == 0) {
		//8방향과 상태에 따른 애니메이션 고르기
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 27, 28, 3, false, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 21, 22, 3, false, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 18, 19, 3, false, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 24, 25, 3, false, true);
				break;
			}
			break;
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 9, 11, 3, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 3, 5, 3, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 0, 2, 3, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", 6, 8, 3, true, true);
				break;
			}
			break;
		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 10;
			_viMonster->frameX = 0;
			break;
		}
	}


	//ATTACK1 : 심기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			if (color == 0) {
				int arrAtk1[] = { 12, 13, 14, 15, 14, 15, 14, 15, 16, 17 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}
			else if (color == 1) {
				int arrAtk1[] = { 33, 34, 35, 36, 35, 36, 35, 36, 37, 38 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}
			else {
				int arrAtk1[] = { 39, 40, 41, 42, 41, 42, 41, 42, 43, 44 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}			
		}
	}
	//ATTACK2 : 뿌리기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			int arrAtk2[] = { 13, 13, 12, 23 };
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "보스머쉬맘", arrAtk2, (int)sizeof(arrAtk2) / sizeof(int), 3, false);
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;

}

void Cboss_mushmam::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + 2, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);

	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cboss_mushmam::stuncheck()
{
}

void Cboss_mushmam::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	float angle = UTIL::getAngle(RecCenX(_viMonster->rc),
		RecCenY(_viMonster->rc),
		PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);

	//거리가 가깝다면, 멀어지는 방향을 랜덤으로 정해서 도망.
	if (distance < _viMonster->range){
		//플레이어를 향하는 각을 계산하고, ±45범위의 랜덤각을 뽑는다. 180을 더해서 방향을 뒤집는다.
		_viMonster->angle = PI + DEGREE(RND->getFromInTo((int)(angle * 180 / PI) - 45, (int)(angle * 180 / PI) + 45));
		//보정.
		while (_viMonster->angle < 0) _viMonster->angle += PI2;
		while (_viMonster->angle > PI2) _viMonster->angle -= PI2;
	}
	//거리가 멀다면, 사거리까지 다가오기.
	else {
		//플레이어를 향해 다가간다.
		_viMonster->angle = angle;
	}


	//얘는 특이하게, NONE일때 FIND를 주기적으로 실행.
	//고로 패턴카운트가 몇이냐에따라 다시 NONE으로 갈지 ATTACK으로 갈지 결정됨.
	if (_viMonster->patternCount < 550)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->activestate = MONSTERACTIVE::NONE;
	}
	else {
		if (_viMonster->attackNum == 2) {
			_viMonster->attackNum = 0;
			_viMonster->activestate = MONSTERACTIVE::ATTACK2;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
		}
		else {
			color = RND->getInt(3);		//0초록, 1보라, 2파랑
			_viMonster->attackNum++;
			_viMonster->activestate = MONSTERACTIVE::ATTACK;
			_viMonster->framecount = 0;
			_viMonster->patternCount = 0;
		}
	}
	
}
void Cboss_mushmam::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + 2, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
///////Cmushmam_mushroom_G!		머쉬맘_녹색머쉬룸!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_G::Cmushmam_mushroom_G()
{
	IMAGE->addFrameImage("머쉬맘_녹색머쉬룸", "images/monsters/mushmam_mushroom1.bmp", 432, 660, 3, 4, true);
}

Cmushmam_mushroom_G::~Cmushmam_mushroom_G()
{
}

HRESULT Cmushmam_mushroom_G::init()
{
	return S_OK;
}

void Cmushmam_mushroom_G::release()
{
}

void Cmushmam_mushroom_G::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		makeCollisionRect(_viMonster);
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cmushmam_mushroom_G::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
	}
	//TCHAR str[128];
	//_stprintf_s(str, "플레이어좌표 : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushmam_mushroom_G::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("머쉬맘_녹색머쉬룸");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.neverchangeX = x;
	newMonster.neverchangeY = y;
	newMonster.width = newMonster.img->getFrameWidth() / 4 + 1;
	newMonster.height = newMonster.img->getFrameHeight() / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() * 3 / 8, y + newMonster.img->getFrameHeight() * 3 / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height/2, newMonster.width, newMonster.height/2);
	newMonster.speed = 0;
	newMonster.hp = 50;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1500;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cmushmam_mushroom_G::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount > 100) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		bm->getHomBulInstance()->fire(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc),
			DEGREE(45), 0);
		bm->getHomBulInstance()->fire(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc),
			DEGREE(135), 0);
		bm->getHomBulInstance()->fire(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc),
			DEGREE(225), 0);
		bm->getHomBulInstance()->fire(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc),
			DEGREE(315), 0);
		_viMonster->activestate = MONSTERACTIVE::NONE;
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cmushmam_mushroom_G::giveFrame()
{
}

void Cmushmam_mushroom_G::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cmushmam_mushroom_G::stuncheck()
{
}

void Cmushmam_mushroom_G::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//목표 지점과 각 설정
	_viMonster->targetX = PLAYER->getPlayerAddress().x;
	_viMonster->targetY = PLAYER->getPlayerAddress().y;
	_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
		RecCenY(_viMonster->rc),
		_viMonster->targetX, _viMonster->targetY);

	_viMonster->patternCount = 0;
	_viMonster->activestate = MONSTERACTIVE::ATTACK;
}
void Cmushmam_mushroom_G::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
///////Cmushmam_mushroom_P!		머쉬맘_보라머쉬룸!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_P::Cmushmam_mushroom_P()
{
	IMAGE->addFrameImage("머쉬맘_보라머쉬룸", "images/monsters/mushmam_mushroom2.bmp", 432, 660, 3, 4, true);
}

Cmushmam_mushroom_P::~Cmushmam_mushroom_P()
{
}

HRESULT Cmushmam_mushroom_P::init()
{
	return S_OK;
}

void Cmushmam_mushroom_P::release()
{
}

void Cmushmam_mushroom_P::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		makeCollisionRect(_viMonster);
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cmushmam_mushroom_P::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cmushmam_mushroom_P::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("머쉬맘_보라머쉬룸");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.neverchangeX = x;
	newMonster.neverchangeY = y;
	newMonster.width = newMonster.img->getFrameWidth() / 4 + 1;
	newMonster.height = newMonster.img->getFrameHeight() / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() * 3 / 8, y + newMonster.img->getFrameHeight() * 3 / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height / 2, newMonster.width, newMonster.height / 2);
	newMonster.speed = 0;
	newMonster.hp = 50;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1500;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cmushmam_mushroom_P::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount % 350 == 0) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		bm->getPsnBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
			_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
			_viMonster->angle, 0);
		_viMonster->activestate = MONSTERACTIVE::NONE;
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cmushmam_mushroom_P::giveFrame()
{
}

void Cmushmam_mushroom_P::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cmushmam_mushroom_P::stuncheck()
{
}

void Cmushmam_mushroom_P::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//목표 지점과 각 설정
	_viMonster->targetX = PLAYER->getPlayerAddress().x;
	_viMonster->targetY = PLAYER->getPlayerAddress().y;
	_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
		_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
		_viMonster->targetX, _viMonster->targetY);

	_viMonster->patternCount = 0;
	_viMonster->activestate = MONSTERACTIVE::ATTACK;
}

void Cmushmam_mushroom_P::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
///////Cmushmam_mushroom_B!		머쉬맘_파랑머쉬룸!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_B::Cmushmam_mushroom_B()
{
	IMAGE->addFrameImage("머쉬맘_파랑머쉬룸", "images/monsters/mushmam_mushroom3.bmp", 432, 660, 3, 4, true);
}

Cmushmam_mushroom_B::~Cmushmam_mushroom_B()
{
}

HRESULT Cmushmam_mushroom_B::init()
{
	return S_OK;
}

void Cmushmam_mushroom_B::release()
{
}

void Cmushmam_mushroom_B::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		makeCollisionRect(_viMonster);
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cmushmam_mushroom_B::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL2, MINT);
			}
			ZORDER->ZorderFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom, _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cmushmam_mushroom_B::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("머쉬맘_파랑머쉬룸");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.neverchangeX = x;
	newMonster.neverchangeY = y;
	newMonster.width = newMonster.img->getFrameWidth() / 4 + 1;
	newMonster.height = newMonster.img->getFrameHeight() / 4;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() * 3 / 8, y + newMonster.img->getFrameHeight() * 3 / 4, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height / 2, newMonster.width, newMonster.height / 2);
	newMonster.speed = 0;
	newMonster.hp = 50;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1500;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cmushmam_mushroom_B::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount % 100 == 0) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		bm->getCirBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
			_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
			_viMonster->angle, 0);
		_viMonster->activestate = MONSTERACTIVE::NONE;
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cmushmam_mushroom_B::giveFrame()
{
}

void Cmushmam_mushroom_B::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cmushmam_mushroom_B::stuncheck()
{
}

void Cmushmam_mushroom_B::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//목표 지점과 각 설정
	_viMonster->targetX = PLAYER->getPlayerAddress().x;
	_viMonster->targetY = PLAYER->getPlayerAddress().y;
	_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
		_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
		_viMonster->targetX, _viMonster->targetY);

	_viMonster->patternCount = 0;
	_viMonster->activestate = MONSTERACTIVE::ATTACK;
}

void Cmushmam_mushroom_B::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
////////////////Cyggdrasil!		이그드라실!////////////////////
//////////////////////////////////////////////////////////////
Cyggdrasil::Cyggdrasil()
{
	IMAGE->addFrameImage("이그드라실", "images/monsters/ent-ent.bmp", 966, 3850, 3, 11, true);
	EFFECT->addEffect("이그드라실점프", "images/monsters/ent_explosion.bmp", ZEFFECT2, 1920, 1536, 384, 384, 1, 0.4f, 1, 150);
}

Cyggdrasil::~Cyggdrasil()
{
}

HRESULT Cyggdrasil::init()
{
	return S_OK;
}

void Cyggdrasil::release()
{
}

void Cyggdrasil::update(Cplayer* py, bulletManager* bm, Cyggdrasil_bomb* bomb)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->x = _viMonster->neverchangeX;
		_viMonster->y = _viMonster->neverchangeY;
		_viMonster->bossRc[0] = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 10, _viMonster->y + _viMonster->img->getFrameHeight() * 2 / 10, _viMonster->width, _viMonster->height);
		_viMonster->bossRc[1] = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() * 4 / 10, _viMonster->y + _viMonster->img->getFrameHeight() * 7 / 10, _viMonster->width * 1 / 4, _viMonster->height * 3 / 5);
		checkPhase();
		checkPlayerXY(py);
		move(bm, bomb);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cyggdrasil::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
		case MONSTERACTIVE::ATTACK3:
			if (_isDebug) {
				//ZORDER->ZorderRectangle(_viMonster->rc, ZCOL1);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL1, MINT);
				ZORDER->ZorderRectangle(_viMonster->bossRc[0], ZCOL2);
				ZORDER->ZorderRectangle(_viMonster->bossRc[1], ZCOL2);
			}
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y, _viMonster->ani);
			if (_viMonster->isNextPhase && _viMonster->activestate == MONSTERACTIVE::ATTACK3 && _viMonster->patternCount == 1)
				EFFECT->play("이그드라실점프", RecCenX(_viMonster->rc)-10, RecCenY(_viMonster->rc)+100);
			//TCHAR str[128];
			//_stprintf_s(str, "hp : %d", _viMonster->hp);
			//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAniAlphaRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y, _viMonster->ani, _viMonster->deathalpha);
			break;
		}
	}
}

void Cyggdrasil::addMonster(float centerx, float centery)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("이그드라실");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("이그드라실", 0, 2, 2, false, false);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.width = newMonster.img->getFrameWidth() * 4 / 5;
	newMonster.height = newMonster.img->getFrameHeight() * 5 / 10;
	newMonster.x = centerx - newMonster.img->getFrameWidth() / 2;
	newMonster.y = centery - newMonster.img->getFrameHeight() * 2 / 3;
	newMonster.neverchangeX = newMonster.x;
	newMonster.neverchangeY = newMonster.y;
	newMonster.rc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 10, newMonster.y + newMonster.img->getFrameHeight() * 1 / 4, newMonster.width, newMonster.img->getFrameHeight() * 4 / 5);
	newMonster.footRc = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 10, newMonster.y + newMonster.img->getFrameHeight() * 1 / 4, newMonster.width, newMonster.img->getFrameHeight() * 4 / 5);
	newMonster.bossRc[0] = RectMake(newMonster.x + newMonster.img->getFrameWidth() / 10, newMonster.y + newMonster.img->getFrameHeight() * 2 / 10, newMonster.width, newMonster.height);
	newMonster.bossRc[1] = RectMake(newMonster.x + newMonster.img->getFrameWidth()* 4 / 10, newMonster.y + newMonster.img->getFrameHeight() * 7 / 10, newMonster.width * 1 / 4, newMonster.height * 3 / 5);
	newMonster.speed = 2;
	newMonster.hp = 900;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI * 3 / 2;
	newMonster.range = 1500;
	newMonster.framecount = 0;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.attackNum = 0;
	newMonster.isLeft = false;
	newMonster.isNextPhase = false;
	newMonster.oldPhase = false;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);

}

void Cyggdrasil::move(bulletManager* bm, Cyggdrasil_bomb* bomb)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		//NONE으로 올때는 항상 patternCount를 0이 아닌 250으로 해주세요.
		if (_viMonster->patternCount > 400) {
			//다음페이즈 신호
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//평상시
			else {
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::FINDING;
			}
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//독브레스 & 추적블릿
		if (_viMonster->patternCount < 250) {
			if (!_viMonster->isNextPhase) {
				//단방향
				if (_viMonster->isLeft) {
					if (_viMonster->patternCount % 5 == 0) {
						bm->getTreBos1Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100,
							UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
								_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
								450 + _viMonster->patternCount / 5 * 9, 0), true, 0);
					}
				}
				else {
					if (_viMonster->patternCount % 5 == 0) {
						bm->getTreBos1Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100,
							UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
								_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
								570 - _viMonster->patternCount / 5 * 9, 0), false, 0);
					}
				}
			}
			else {
				//쌍방향
				if (_viMonster->patternCount % 5 == 0) {
					bm->getTreBos1Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100,
						UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
							570 - _viMonster->patternCount / 5 * 9, 0), false, 0);
				}
				if (_viMonster->patternCount % 5 == 0) {
					bm->getTreBos1Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100,
						UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
							450 + _viMonster->patternCount / 5 * 9, 0), true, 0);
				}
			}
			//추적블릿★
			if (_viMonster->patternCount > 125) {
				bm->getTreBos3Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle, true, 0);
			}

		}
		else {
			//다음페이즈 신호
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//평상시
			else {
				_viMonster->framecount = 0;
				_viMonster->patternCount = 250;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		//바람3줄기
		if (_viMonster->patternCount < 350) {
			float anglechange = (_viMonster->isNextPhase) ? 0.017 : 0.008;
			if (_viMonster->patternCount % 5 == 0 && _viMonster->patternCount >= 100) {
				//처음엔 플레이어쪽으로 뿌리기
				if (_viMonster->patternCount < 150) {
					bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle, true, 0);
				}
				//플레이어가 왼쪽인지 오른쪽인지 확인하고 각도 이동하며 뿌리기
				if (_viMonster->patternCount == 150 || _viMonster->patternCount == 250 ) {
					float nowAngle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
					if (_viMonster->angle >= nowAngle){		//플레이어가 왼쪽으로 피했다
						_viMonster->isLeft = true;
					}
					else {
						_viMonster->isLeft = false;
					}
				}
				////이동하며 뿌리기(150이상 250미만)
				if (_viMonster->patternCount >= 150 && _viMonster->patternCount<250) {
					int standardnum = _viMonster->patternCount - 150;
					if (_viMonster->isLeft) {
						bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle- anglechange *(standardnum), true, 0);
						if (_viMonster->patternCount == 245) {
							_viMonster->angle = _viMonster->angle - anglechange * (standardnum);
						}
					}
					else {
						bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle + anglechange * (standardnum), true, 0);
						if (_viMonster->patternCount == 245) {
							_viMonster->angle = _viMonster->angle + anglechange * (standardnum);
						}
					}
				}
				//이동하며 뿌리기(250이상)
				if (_viMonster->patternCount >= 250) {
					//bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					//	_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle, true, 0);
					int standardnum = _viMonster->patternCount - 250;
					if (_viMonster->isLeft) {
						bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle - anglechange * (standardnum), true, 0);
					}
					else {
						bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
							_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle + anglechange * (standardnum), true, 0);
					}
				}
			}
		}
		else {
			//다음페이즈 신호
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//평상시
			else {
				_viMonster->framecount = 0;
				_viMonster->patternCount = 250;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
		}
		break;
	case MONSTERACTIVE::ATTACK3:
		if (_viMonster->patternCount < 210) {
			//나무열매 3개
			if (_viMonster->patternCount % 60 == 0) {
				bomb->addMonster(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 50);
			}			
			//가시 빠르게 7개
			if (_viMonster->isNextPhase) {
				if (_viMonster->patternCount % 28 == 0) {
					bm->getnidBulInstance()->fire(PLAYER->getPlayerAddress().x,
						PLAYER->getPlayerAddress().y,
						_viMonster->angle, 0);
				}
			}
		}
		else {
			//다음페이즈 신호
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//평상시
			else {
				_viMonster->framecount = 0;
				_viMonster->patternCount = 250;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 1;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cyggdrasil::giveFrame()
{
	//NONE
	if (_viMonster->activestate == MONSTERACTIVE::NONE) {
		//입장프레임때문에 얘는 NONE으로 돌아올때 꼭 250부터 시작하게 하자.
		if (_viMonster->patternCount == 90) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 15, 18, 3, false, false);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 6, 8, 3, false, false);
			}
		}
		if (_viMonster->patternCount == 251) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 18, 20, 4, true, true);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 3, 5, 4, true, true);
			}
		}
	}

	//ATTACK1 : 독브레스
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				int aniarr[] = { 24, 25, 27, 28, 29, 30, 31 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
			else {
				if (!_viMonster->isLeft) {
					int aniarr[] = { 6, 7, 9, 10, 11, 12, 13 };
					ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
				}
				else {
					int aniarr[] = { 6, 7, 13, 12, 11, 10, 9 };
					ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
				}
			}
		}
	}
	//ATTACK2 : 바람3줄기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 24, 26, 2, false, false);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 6, 8, 2, false, false);
			}
		}
	}

	//ATTACK3 : 열매투척, (광폭후)가시패턴
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK3) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 24, 25, 2, false, false);
			}
			else{
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", 6, 7, 2, false, false);
			}
		}
		if (_viMonster->framecount == 200) {
			if (_viMonster->isNextPhase) {
				/*★ 이펙트매니저로 쿵 이펙트 뿌리기*/
				int aniarr[] = { 24, 22 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
			else {
				int aniarr[] = { 6, 4 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
		}
	}
	//DEATH : 죽었을 때
	if (_viMonster->activestate == MONSTERACTIVE::DEATH) {
		if (_viMonster->framecount == 0) {
			int aniarr[] = { 30, 28, 30, 28, 26, 24, 25 };
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실", aniarr, sizeof(aniarr) / sizeof(int), 4, false);
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;
}

void Cyggdrasil::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->bossRc[0] = RectMake(iter->x + iter->img->getFrameWidth() / 10, iter->y + iter->img->getFrameHeight() * 2 / 10, iter->width, iter->height);
	iter->bossRc[1] = RectMake(iter->x + iter->img->getFrameWidth() * 4 / 10, iter->y + iter->img->getFrameHeight() * 7 / 10, iter->width * 1 / 4, iter->height * 3 / 5);
	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cyggdrasil::stuncheck()
{
}

void Cyggdrasil::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		//직전공격이 1번이나 2번이였던 경우, 3번공격개시
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK ||
			_viMonster->oldactivestate == MONSTERACTIVE::ATTACK2) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK3;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK3;
		}
		//3번이였던경우, 1번 또는 2번 개시
		else {
			if (RND->getInt(2)) {
				_viMonster->isLeft = RND->getInt(2);
				_viMonster->activestate = MONSTERACTIVE::ATTACK;
				_viMonster->oldactivestate = MONSTERACTIVE::ATTACK;
			}
			else {
				_viMonster->activestate = MONSTERACTIVE::ATTACK2;
				_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
			}
		}

		//목표 지점과 각 설정
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
			_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2, _viMonster->targetX, _viMonster->targetY);
	}
	//사거리내가 아니라면 랜덤무브 진입.
	else {
		_viMonster->framecount = 0;
		_viMonster->patternCount = 250;
		_viMonster->activestate = MONSTERACTIVE::NONE;
	}
}

void Cyggdrasil::makeCollisionRect(vector<tagMonster>::iterator iter)
{
}

void Cyggdrasil::checkPhase()
{
	//다음페이즈돌입
	if (!_viMonster->isNextPhase && _viMonster->hp < 360) {
		_viMonster->isNextPhase = true;
	}
	//현재진행중인 패턴끝나고 NONE으로 돌입했을 때, patternCount 0으로가서 광폭애니메이션 출력한다. 
}
//////////////////////////////////////////////////////////////
//////////Cyggdrasil_bomb!		이그드라실_폭탄!///////////////
//////////////////////////////////////////////////////////////
Cyggdrasil_bomb::Cyggdrasil_bomb()
{
	IMAGE->addFrameImage("이그드라실_폭탄", "images/monsters/bomb-bomb.bmp", 81, 108, 3, 4, true);
}

Cyggdrasil_bomb::~Cyggdrasil_bomb()
{
}

HRESULT Cyggdrasil_bomb::init()
{
	return S_OK;
}

void Cyggdrasil_bomb::release()
{
}

void Cyggdrasil_bomb::update(Cplayer* py, bulletManager* bm)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		//날라가는중이 아닐때만 보정
		if (_viMonster->activestate != MONSTERACTIVE::ATTACK) {
			_viMonster->x = _viMonster->neverchangeX;
			_viMonster->y = _viMonster->neverchangeY;
			makeCollisionRect(_viMonster);
		}
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
	}
	//소멸
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
}

void Cyggdrasil_bomb::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
		case MONSTERACTIVE::ATTACK:
		case MONSTERACTIVE::ATTACK2:
			ZORDER->ZorderAniRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y, _viMonster->ani);
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, ZCOL3);
				ZORDER->ZorderRectangleColor(_viMonster->footRc, ZCOL4, MINT);
			}
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "hp : %d", _viMonster->hp);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cyggdrasil_bomb::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("이그드라실_폭탄");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("이그드라실_폭탄", 0, 11, 4, false, false);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	//newMonster.neverchangeX; //= RND->getFromInTo((int)x-200, (int)x+200);
	//newMonster.neverchangeY; //= RND->getFromInTo((int)y + 20, (int)y + 400);
	newMonster.width = newMonster.img->getFrameWidth() * 2 / 3;
	newMonster.height = newMonster.img->getFrameHeight() * 2 / 3;
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() * 1 / 6, y + newMonster.img->getFrameHeight() * 1 / 6, newMonster.width, newMonster.height);
	newMonster.footRc = RectMake(newMonster.rc.left, newMonster.rc.top + newMonster.height/2, newMonster.width, newMonster.height/2);
	newMonster.speed = RND->getFromInTo(7, 14);
	newMonster.hp = 55;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = DEGREE(RND->getFromInTo(215, 325));
	newMonster.range = 1500;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::ATTACK;
	newMonster.oldactivestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Cyggdrasil_bomb::move(bulletManager* bm)
{
	_viMonster->patternCount++;
	switch (_viMonster->activestate)
	{
	case MONSTERACTIVE::NONE:
		if (_viMonster->patternCount % 100 == 0) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//목표지점까지 날라가기
		if (_viMonster->patternCount < 100) {
			if (_viMonster->angle * 180 / PI < 270) _viMonster->angle+=0.0025f;
			if (_viMonster->angle * 180 / PI > 270) _viMonster->angle-=0.0025f;
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			makeCollisionRect(_viMonster);
			_viMonster->speed -= 0.25f;
			if (_viMonster->speed < 0) {
				_viMonster->speed = 0;
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::NONE;
				_viMonster->neverchangeX = _viMonster->x;
				_viMonster->neverchangeY = _viMonster->y;
			}
		}
		else {
			_viMonster->patternCount = 0;
			_viMonster->activestate = MONSTERACTIVE::NONE;
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		//터지며 폭발
		if (_viMonster->patternCount == 250) {
			if (RND->getInt(2)) {
				bm->getCirBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
					_viMonster->angle, 0);
			}
			else {
				bm->getLPsnBulInstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
					_viMonster->angle, 0);
			}
			_viMonster->afterDeath = true;
		}
		break;
	case MONSTERACTIVE::RNDMOVE:
		break;
	case MONSTERACTIVE::DEATH:
		_viMonster->deathalpha -= 3;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cyggdrasil_bomb::giveFrame()
{
	//ATTACK2 : 터지기
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "이그드라실_폭탄", 11, 0, 3);
		}
	}

	//프레임카운트증가(상태변화 알림외에 기능 없음)
	_viMonster->framecount++;

}

void Cyggdrasil_bomb::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH || iter->activestate == MONSTERACTIVE::ATTACK) return;
	//외부호출용함수(공격에맞을떄)
	//짧은무적돌입
	iter->isGraceperiod = true;
	//데미지반영
	iter->hp -= damage;
	//총알이 나를 바라보던 방향으로 넉백
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 1 / 6, iter->y + iter->img->getFrameHeight() * 1 / 6, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//보스는 절대 스턴먹지 않는다.
	if (stun = false) {
		iter->isStun = stun;
		iter->frameX = 0;
		iter->framecount = 0;
		iter->patternCount = 0;
		iter->activestate = MONSTERACTIVE::NONE;
	}
}

void Cyggdrasil_bomb::stuncheck()
{
}

void Cyggdrasil_bomb::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//목표 지점과 각 설정
	_viMonster->targetX = PLAYER->getPlayerAddress().x;
	_viMonster->targetY = PLAYER->getPlayerAddress().y;
	_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
		_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2,
		_viMonster->targetX, _viMonster->targetY);

	_viMonster->framecount = 0;
	_viMonster->patternCount = 0;
	_viMonster->activestate = MONSTERACTIVE::ATTACK2;
}

void Cyggdrasil_bomb::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 1 / 6, iter->y + iter->img->getFrameHeight() * 1 / 6, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
