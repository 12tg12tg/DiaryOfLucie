#include "framework.h"
#include "Cmonsters.h"
#include "Cplayer.h"
#include "bulletManager.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername			imagename
1.		Csnaby		/		��
2.		Cslime		/		������
3.					/		
4.					/		
5.					/		
6.					/		
7.					/		
8.					/		
*/
//////////////////////////////////////////////////////////////
//////////////////////Csnaby!	��!//////////////////////////
//////////////////////////////////////////////////////////////
Csnaby::Csnaby()
{
	IMAGE->addFrameImage("��", "images/monsters/snaby-snaby.bmp", 144, 624, 3, 13, true);
	//fackpy = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 30, 50);
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
	//����
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
	}
	//�Ҹ�
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
	//���̿����̱�
	//{
	//	if (InputManager->isStayKeyDown(VK_LEFT)) {
	//		OffsetRect(&fackpy, -3, 0);
	//	}
	//	if (InputManager->isStayKeyDown(VK_RIGHT)) {
	//		OffsetRect(&fackpy, 3, 0);
	//	}
	//	if (InputManager->isStayKeyDown(VK_UP)) {
	//		OffsetRect(&fackpy, 0, -3);
	//	}
	//	if (InputManager->isStayKeyDown(VK_DOWN)) {
	//		OffsetRect(&fackpy, 0, 3);
	//	}
	//}
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
	//_stprintf_s(str, "������ ���� : %d", _vMonster.size());
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	//RectangleMake(getMemDC(), fackpy);
}

void Csnaby::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("��");
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
			_viMonster->x += cosf(_viMonster->angle) * 1;
			_viMonster->y -= sinf(_viMonster->angle) * 1;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y, _viMonster->width, _viMonster->height);
			if (_viMonster->patternCount % 30 == 0) {
				bm->getTriBulInstance()->fire(
					_viMonster->x + _viMonster->img->getFrameWidth()/2,
					_viMonster->y + _viMonster->img->getFrameHeight()/2,
					_viMonster->angle);
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
	//8����� ���¿� ���� Y������ ����
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
			_viMonster->frameY = 8; //����Ʈ
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
			_viMonster->frameY = 4; //����Ʈ
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
			_viMonster->frameY = 0; //����Ʈ
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 12;
		maxFrameX = 0;
		break;
	}

	//X������ ������
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);//py->getX(), py->getY());
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
		//��ǥ ������ �� ����
		_viMonster->targetX = fackpy.left;
		_viMonster->targetY = fackpy.right;
		_viMonster->angle = UTIL::getAngle(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);
	}
	//��Ÿ����� �ƴ϶�� �������� ����.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}
//////////////////////////////////////////////////////////////
//////////////////////Cslime!	������!////////////////////////
//////////////////////////////////////////////////////////////
Cslime::Cslime()
{
	IMAGE->addFrameImage("������", "images/monsters/slime.bmp", 120, 520, 3, 13, true);
	fackpy = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 30, 50);
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
	//����
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		stuncheck();
		checkPlayerXY(py);
		move(bm);
		checkAngle();
		giveFrame();
		deathCheck();
	}
	//�Ҹ�
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); )
	{
		if (_viMonster->afterDeath) {
			_viMonster = _vMonster.erase(_viMonster);
		}
		else {
			++_viMonster;
		}
	}
	//���̿����̱�
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
			if (_isDebug) RectangleMake(getMemDC(), _viMonster->rc);
			_viMonster->img->frameRender(getMemDC(), _viMonster->x, _viMonster->y, _viMonster->frameX, _viMonster->frameY);
			break;
		case MONSTERACTIVE::DEATH:
			_viMonster->img->alphaFrameRender(getMemDC(), _viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
	}
	TCHAR str[128];
	_stprintf_s(str, "������ ���� : %d", _vMonster.size());
	TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	RectangleMake(getMemDC(), fackpy);
}

void Cslime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("������");
	newMonster.frameX = 0;
	newMonster.frameY = 0;
	newMonster.x = x;
	newMonster.y = y;
	newMonster.width = newMonster.img->getFrameWidth() / 3 * 2;
	newMonster.height = newMonster.img->getFrameHeight();
	newMonster.rc = RectMake(x + newMonster.img->getFrameWidth() / 6, y, newMonster.width, newMonster.height);
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
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			_viMonster->rc = RectMake(_viMonster->x + _viMonster->img->getFrameWidth() / 6, _viMonster->y, _viMonster->width, _viMonster->height);
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
					_viMonster->x + _viMonster->img->getFrameWidth() / 2,
					_viMonster->y + _viMonster->img->getFrameHeight() / 2,
					_viMonster->angle);
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
			if (_viMonster->patternCount % 97 == 0) {
				bm->getCirBulInstance()->fire(
					_viMonster->x + _viMonster->img->getFrameWidth() / 2,
					_viMonster->y + _viMonster->img->getFrameHeight() / 2,
					_viMonster->angle);
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
		_viMonster->deathalpha -= 2;
		if (_viMonster->deathalpha < 0) _viMonster->deathalpha = 0;
		if (_viMonster->deathalpha == 0) {
			_viMonster->afterDeath = true;
		}
		break;
	}
}

void Cslime::checkAngle()
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

void Cslime::giveFrame()
{
	int maxFrameX;
	_viMonster->framecount++;
	//8����� ���¿� ���� Y������ ����
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
			_viMonster->frameY = 0; //����Ʈ
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
			_viMonster->frameY = 8; //����Ʈ
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
				_viMonster->frameY = 4; //����Ʈ
				break;
			}
		}
		maxFrameX = 2;
		break;

	//case MONSTERACTIVE::RNDMOVE:
	//	switch (_viMonster->movestate)
	//	{
	//	case MONSTERMOVESTATE::RIGHTUP:
	//	case MONSTERMOVESTATE::UP:
	//		_viMonster->frameY = 3;
	//		break;
	//	case MONSTERMOVESTATE::LEFTUP:
	//	case MONSTERMOVESTATE::LEFT:
	//		_viMonster->frameY = 1;
	//		break;
	//	case MONSTERMOVESTATE::LEFTDOWN:
	//	case MONSTERMOVESTATE::DOWN:
	//		_viMonster->frameY = 0;
	//		break;
	//	case MONSTERMOVESTATE::RIGHTDOWN:
	//	case MONSTERMOVESTATE::RIGHT:
	//		_viMonster->frameY = 2;
	//		break;
	//	case MONSTERMOVESTATE::NONE:
	//		_viMonster->frameY = 0; //����Ʈ
	//		break;
	//	}
	//	maxFrameX = 2;
	//	break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 12;
		maxFrameX = 2;
		break;
	}

	//X������ ������
	int currentX = _viMonster->frameX;
	if (_viMonster->framecount % 12 == 0) {
		currentX++;
		if (currentX > maxFrameX) {
			currentX = 0;
		}
		_viMonster->frameX = currentX;
	}
}

void Cslime::deathCheck()
{
	if (_viMonster->activestate != MONSTERACTIVE::DEATH && _viMonster->hp <= 0) {
		_viMonster->activestate = MONSTERACTIVE::DEATH;
		_viMonster->patternCount = 0;
	}
}

void Cslime::knockback(float x, float y, bool stun)
{
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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

void Cslime::stuncheck()
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

void Cslime::checkPlayerXY(Cplayer* py)
{
	if (_viMonster->activestate != MONSTERACTIVE::FINDING) return;
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);//py->getX(), py->getY());
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if(_viMonster->oldactivestate == MONSTERACTIVE::ATTACK) _viMonster->activestate = MONSTERACTIVE::ATTACK2;
		else _viMonster->activestate = MONSTERACTIVE::ATTACK;
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//��ǥ ������ �� ����
		_viMonster->targetX = fackpy.left;
		_viMonster->targetY = fackpy.right;
		_viMonster->angle = UTIL::getAngle(_viMonster->x, _viMonster->y, fackpy.left, fackpy.top);
	}
	//��Ÿ����� �ƴ϶�� �������� ����.
	else {
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
		_viMonster->angle = RND->getInt(360) * PI / 180;
	}
}
