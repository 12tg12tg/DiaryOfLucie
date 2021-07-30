#include "framework.h"
#include "Cmonsters.h"
#include "Cplayer.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername			imagename
1.		Csnaby		/		뱀
2.					/		
3.					/		
4.					/		
5.					/		
6.					/		
7.					/		
8.					/		
*/
//////////////////////////////////////////////////////////////
//////////////////////Csnaby!	뱀!//////////////////////////
//////////////////////////////////////////////////////////////
Csnaby::Csnaby()
{
	fackpy = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 30, 50);
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

void Csnaby::update(Cplayer* py)
{
	//업뎃
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move();
		checkAngle();
		giveFrame();
		deathCheck();
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
	//더미움직이기
	{
		if (InputManager->isStayKeyDown(VK_LEFT)) {
			OffsetRect(&fackpy, -3, 0);
		}
		if (InputManager->isStayKeyDown(VK_RIGHT)) {
			OffsetRect(&fackpy, 3, 0);
		}
		if (InputManager->isStayKeyDown(VK_UP)) {
			OffsetRect(&fackpy, 0, -3);
		}
		if (InputManager->isStayKeyDown(VK_DOWN)) {
			OffsetRect(&fackpy, 0, 3);
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
			if (_isDebug) RectangleMake(getMemDC(), _viMonster->rc);
			_viMonster->img->frameRender(getMemDC(), _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			_viMonster->img->alphaFrameRender(getMemDC(), _viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}		
	}
	//TCHAR str[128];
	//_stprintf_s(str, "벡터의 갯수 : %d", _vMonster.size());
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	RectangleMake(getMemDC(), fackpy);
}

void Csnaby::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->addFrameImage("뱀", "images/monsters/snaby-snaby.bmp", 144, 624, 3, 13, true);
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth()/3 * 2;
	newMonster.height = newMonster.img->getFrameHeight();
	newMonster.rc = RectMake(x+ newMonster.img->getFrameWidth()/6, y, newMonster.width, newMonster.height);
	newMonster.speed = 2;
	newMonster.hp = 40;
	newMonster.isStun = false;
	newMonster.isDeath = false;
	newMonster.findPlayer = false;
	newMonster.afterDeath = false;
	newMonster.targetX = 0;
	newMonster.targetY = 0;
	newMonster.angle = PI*3/2;
	newMonster.range = 280;
	newMonster.stunCount = 0;
	newMonster.patternCount = 0;
	newMonster.deathalpha = 255;
	newMonster.activestate = MONSTERACTIVE::NONE;
	newMonster.movestate = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void Csnaby::move()
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
			_viMonster->x += cosf(_viMonster->angle) * 1;
			_viMonster->y -= sinf(_viMonster->angle) * 1;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y, _viMonster->width, _viMonster->height);
			if (_viMonster->patternCount % 30 == 0) {
				/*발사함수 호출*/
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
			_viMonster->x += cosf(_viMonster->angle)*_viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y, _viMonster->width, _viMonster->height);
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

void Csnaby::checkAngle()
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

void Csnaby::deathCheck()
{
	if (_viMonster->activestate != MONSTERACTIVE::DEATH && _viMonster->hp <= 0) {
		_viMonster->activestate = MONSTERACTIVE::DEATH;
		_viMonster->patternCount = 0;
	}
}

void Csnaby::stuncheck()
{
	if (_viMonster->isStun) {
		_viMonster->stunCount++;
		if (_viMonster->stunCount > 10) {
			_viMonster->activestate = MONSTERACTIVE::FINDING;
			_viMonster->stunCount = 0;
			_viMonster->isStun = false;
		}
	}
}

void Csnaby::knockback(float x, float y, bool stun)
{
	//외부호출용함수(공격에맞을떄)
	//총알이 나를 바라보던 방향으로 넉백
	float nbangle = UTIL::getAngle(x, y, _viMonster->x, _viMonster->y);
	_viMonster->x += cosf(nbangle) * 1;
	_viMonster->y -= sinf(nbangle) * 1;
	_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y, _viMonster->width, _viMonster->height);
	if (stun) {
		_viMonster->isStun = stun;
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::NONE;
	}
}

void Csnaby::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//플레이어의 좌표를 확인후 사거리내로 들어왔다면 공격상태돌입.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);//py->getX(), py->getY());
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
		//목표 지점과 각 설정
		_viMonster->targetX = fackpy.left;
		_viMonster->targetY = fackpy.right;
		_viMonster->angle = UTIL::getAngle(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);
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
//////////////////////////////////////////////////////////////
//////////////////////				//////////////////////////
//////////////////////////////////////////////////////////////