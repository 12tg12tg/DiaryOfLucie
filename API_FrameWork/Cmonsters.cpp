#include "framework.h"
#include "Cmonsters.h"
#include "Cplayer.h"
#include "bulletManager.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername					imagename
1.		Csnaby			/		��
2.		Cslime			/		������
3.		Cmushman		/		�ӽ���
4	Cmushman_mushroom!	/		�ӽ���_�ӽ���		
5.		Cfairy			/		��
6.		Cflime			/		��
7.	Cboss_slime			/		����������
8.	Csemiboss_slime		/		�غ���������
9.	Cboss_flime			/		�����ö���
10. Cboss_mushmam		/		�����ӽ���
11. Cmushmam_mushroom_G	/		�ӽ���_����ӽ���
12. Cmushmam_mushroom2_P/		�ӽ���_����ӽ���
13. Cmushmam_mushroom3_B/		�ӽ���_�Ķ��ӽ���
14.	Cyggdrasil_bomb		/		�̱׵���_��ź
15.		Cyggdrasil		/		�̱׵���
16.
17.
*/
//////////////////////////////////////////////////////////////
//////////////////////Csnaby!	��!//////////////////////////
//////////////////////////////////////////////////////////////
Csnaby::Csnaby()
{
	IMAGE->addFrameImage("��", "images/monsters/snaby-snaby.bmp", 144, 624, 3, 13, true);
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
		checkInvincibility();
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
			//1�� ���������� �浹��ٸ� �������
			goOrStay(1);
			//3������߻�
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

void Csnaby::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		_viMonster->activestate = MONSTERACTIVE::ATTACK;
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
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

void Csnaby::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////////////////Cslime!	������!////////////////////////
//////////////////////////////////////////////////////////////
Cslime::Cslime()
{
	IMAGE->addFrameImage("������", "images/monsters/slime.bmp", 180, 780, 3, 13, true);
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
		checkInvincibility();
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
	newMonster.img = IMAGE->findImage("������");
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

void Cslime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->frameX = 0;
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		if(_viMonster->oldactivestate == MONSTERACTIVE::ATTACK) _viMonster->activestate = MONSTERACTIVE::ATTACK2;
		else _viMonster->activestate = MONSTERACTIVE::ATTACK;
		_viMonster->oldactivestate = MONSTERACTIVE::NONE;
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
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

void Cslime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameWidth() / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////////////////Cmushman!	�ӽ���!///////////////////////
//////////////////////////////////////////////////////////////
Cmushman::Cmushman()
{
	IMAGE->addFrameImage("�ӽ���", "images/monsters/mushman-mushman.bmp", 144, 935, 3, 17, true);
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
	//����
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
	//_stprintf_s(str, "�÷��̾���ǥ : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushman::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("�ӽ���");
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
			//���30�̻��̸� RNDMOVE�� ����
			if (_viMonster->patternCount % 100 > 0 && _viMonster->patternCount % 100 < 30) {
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
			}
			//����� �� ����Ȯ���ϰ� �� �ٲٱ�
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
		//�����̴ٰ�
		if (_viMonster->patternCount % 100 < 30) {
			goOrStay(_viMonster->speed);
		}
		//���60�̻��̸� NONE���� ���ư���
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
	//8����� ���¿� ���� Y������ ����
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
			_viMonster->frameY = 6; //����Ʈ
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
			_viMonster->frameY = 0; //����Ʈ
			break;
		}
		maxFrameX = 2;
		break;

	case MONSTERACTIVE::DEATH:
		_viMonster->frameY = 10;
		maxFrameX = 0;
		break;
	}

	//X������ ������1(������ �ƴҶ�)
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
	//x������ ������2(������ ��)
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹� - ������ �˹����.
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		//��ǥ ������ �� ����(��Ÿ� ����� ��������)
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		float tempangle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY) - PI;
		if (tempangle < 0) tempangle += PI2;
		if (tempangle > PI2) tempangle -= PI2;
		_viMonster->angle = (tempangle);
	}
	else {
		//��Ÿ����� �ƴ϶�� �ٰ�����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//��� Ư���ϰ�, NONE�϶� FIND�� �ֱ������� ����.
	//��� ����ī��Ʈ�� ���̳Ŀ����� �ٽ� NONE���� ���� ATTACK���� ���� ������.
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
//////////Cmushman_mushroom!	�ӽ���_�ӽ���!/////////////////
//////////////////////////////////////////////////////////////
Cmushman_mushroom::Cmushman_mushroom()
{
	IMAGE->addFrameImage("�ӽ���_�ӽ���", "images/monsters/mushman_mushroom.bmp", 144, 220, 3, 4, true);
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
	//����
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
	//_stprintf_s(str, "�÷��̾���ǥ : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushman_mushroom::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("�ӽ���_�ӽ���");
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
	//8����� ���¿� ���� Y������ ����
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

	//X������ ������1(������ �ƴҶ�)
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
	//X������ ������2(���߰���)
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//������ ������ ���°ɷ�..
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
	//��ǥ ������ �� ����
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
////////////////Cfairy!				��!///////////////////
//////////////////////////////////////////////////////////////
Cfairy::Cfairy()
{
	IMAGE->addFrameImage("��", "images/monsters/fairy-forest.bmp", 168, 930, 3, 10, true);
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
	//����
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
		//_stprintf_s(str, "����������X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cfairy::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("��");
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
			_viMonster->frameY = 4; //����Ʈ
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
			_viMonster->frameY = 8; //����Ʈ
			_viMonster->frameX = 1; //����Ʈ
			break;
		}
		maxFrameX = 0;
		break;
	}

	int currentX = _viMonster->frameX;
	//���������϶� x������ ����
	if (_viMonster->activestate == MONSTERACTIVE::NONE||_viMonster->activestate == MONSTERACTIVE::FINDING) {
		_viMonster->frameX = 1;
	}
	//�׾��� �� �ѹ��� ����
	else if (_viMonster->activestate == MONSTERACTIVE::DEATH){
		if (_viMonster->framecount > 12) {
			_viMonster->frameY = 8;
			_viMonster->frameX = 0;
		}
	}
	//�����̰ų� �������� �� X������ ������
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
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
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//��Ÿ����� �ƴ϶�� �������� ����.
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
////////////////Cflime!				��!///////////////////////
//////////////////////////////////////////////////////////////
Cflime::Cflime()
{
	IMAGE->addFrameImage("��", "images/monsters/flime-flime.bmp", 240, 549, 3, 9, true);
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
	//����
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
		//_stprintf_s(str, "����ī��Ʈ : %d", _viMonster->stunCount);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cflime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("��");
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
			//��� ������ ����������� ���
		}
		else {
			//���ݻ��� ����
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
	//8����� ���¿� ���� Y������ ����
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
			_viMonster->frameY = 0; //����Ʈ
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
			_viMonster->frameY = 4; //����Ʈ
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
			_viMonster->frameY = 0; //����Ʈ
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
	//�����Ѹ��ȱ� ����. ������ �����ӿ��� �����ֱ�.
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
			//�����Ӱ���
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
		//����2 ���°� ���ڸ��� ������� ���
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
	//NONE�̰ų� DEATH�϶� ����������.
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
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
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
	}
	//��Ÿ����� �ƴ϶�� NONE ����.
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
//////////Cboss_slime!		����������!///////////////////////
//////////////////////////////////////////////////////////////
Cboss_slime::Cboss_slime()
{
	IMAGE->addFrameImage("����������", "images/monsters/boss_KingSlime.bmp", 576*2, 2496*2, 3, 13, true);
	EFFECT->addEffect("ŷ����������", "images/monsters/skill_slime_jump_effect.bmp", ZEFFECT1, 960, 384, 192, 192, 1, 0.3f, 5, 100);
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
	//����
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
				EFFECT->play("ŷ����������", _viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.bottom);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "����������X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Cboss_slime::addMonster(float centerx, float centery)
{

	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("����������");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("����������", 0, 2, 8, true, true);
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
		//8����� ���¿� ���� �ִϸ��̼� ����
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 9, 11, 8, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 3, 5, 8, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 0, 2, 8, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 6, 8, 8, true, true);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::ATTACK:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 33, 35, 5, false, false);
				break;											
			case MONSTERMOVESTATE::LEFTUP:						
			case MONSTERMOVESTATE::LEFT:						
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 27, 29, 5, false, false);
				break;												
			case MONSTERMOVESTATE::NONE:							
			case MONSTERMOVESTATE::LEFTDOWN:						
			case MONSTERMOVESTATE::DOWN:							
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 24, 26, 5, false, false);
				break;											
			case MONSTERMOVESTATE::RIGHTDOWN:					
			case MONSTERMOVESTATE::RIGHT:						
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 30, 32, 5, false, false);
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
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 21, 23, 5, false, false);
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 15, 17, 5, false, false);
			break;
		case MONSTERMOVESTATE::NONE:
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 12, 14, 5, false, false);
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "����������", 18, 20, 5, false, false);
			break;
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;

}

void Cboss_slime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
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
	//������ ���� ���ϸ��� �ʴ´�.
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
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
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
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

void Cboss_slime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Csemiboss_slime!		�غ���������!//////////////////
//////////////////////////////////////////////////////////////
Csemiboss_slime::Csemiboss_slime()
{
	IMAGE->addFrameImage("�غ���������", "images/monsters/boss_KingSlime.bmp", 576, 2496, 3, 13, true);
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
	//����
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
				EFFECT->play("ŷ����������", _viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.bottom);
			break;
		case MONSTERACTIVE::DEATH:
			ZORDER->ZorderAlphaFrameRender(_viMonster->img, ZUNIT, _viMonster->footRc.bottom,
				_viMonster->x, _viMonster->y,
				_viMonster->frameX, _viMonster->frameY, _viMonster->deathalpha);
			break;
		}
		//TCHAR str[128];
		//_stprintf_s(str, "����������X : %d", _viMonster->frameX);
		//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
	}
}

void Csemiboss_slime::addMonster(float centerx, float centery)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("�غ���������");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�غ���������", 0, 2, 8, true, true);
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
				//��ǥ ������ �� ����
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
		//8����� ���¿� ���� �ִϸ��̼� ����
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 9, 11, 8, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 3, 5, 8, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 0, 2, 8, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 6, 8, 8, true, true);
				break;
			}
			//maxFrameX = 2;
			break;

		case MONSTERACTIVE::ATTACK:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 33, 35, 5, false, false);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 27, 29, 5, false, false);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 24, 26, 5, false, false);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 30, 32, 5, false, false);
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
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 21, 23, 5, false, false);
			break;
		case MONSTERMOVESTATE::LEFTUP:
		case MONSTERMOVESTATE::LEFT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 15, 17, 5, false, false);
			break;
		case MONSTERMOVESTATE::NONE:
		case MONSTERMOVESTATE::LEFTDOWN:
		case MONSTERMOVESTATE::DOWN:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 12, 14, 5, false, false);
			break;
		case MONSTERMOVESTATE::RIGHTDOWN:
		case MONSTERMOVESTATE::RIGHT:
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�غ���������", 18, 20, 5, false, false);
			break;
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;

}

void Csemiboss_slime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	if(iter->activestate != MONSTERACTIVE::ATTACK2)
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//������ ���� ���ϸ��� �ʴ´�.
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
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
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
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

void Csemiboss_slime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 4, iter->y + iter->img->getFrameHeight() * 2 / 3, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
}
//////////////////////////////////////////////////////////////
//////////Cboss_flime!			�����ö���!////////////////////
//////////////////////////////////////////////////////////////
Cboss_flime::Cboss_flime()
{
	IMAGE->addFrameImage("�����ö���", "images/monsters/flime-bossFlime.bmp", 750, 1710, 3, 9, true);
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
	//����
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
	newMonster.img = IMAGE->findImage("�����ö���");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�����ö���", 1, 2, 3, true, true);
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
		//���� ������ ���ÿ� �߻� (������ 3��)
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
			//�޽�
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
		//�����ϳ�. ���ð��� �Ǵ� �����ٱ�.
		if (_viMonster->attackNum == 1) {
			//���ð���
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
				//�޽�
			}
			else {
				//���ݻ��� ����
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::NONE;
				_viMonster->oldactivestate = MONSTERACTIVE::ATTACK2;
			}
		}
		else {
			//���� �ٱ�
			if (_viMonster->patternCount == 55) {
				bm->getFlwBos1Bullnstance()->fire(
					RecCenX(_viMonster->rc), RecCenY(_viMonster->rc),
					RND->getInt(2), 0);
			}
			else if (_viMonster->patternCount == 90) {
				//�����Ѿ�
				bm->getFlwBos3Bullnstance()->fire(RecCenX(_viMonster->rc), RecCenY(_viMonster->rc), 0);
			}
			else if (_viMonster->patternCount < 505) {
				//�޽�
			}
			else {
				//���ݻ��� ����
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
		//8����� ���¿� ���� �ִϸ��̼� ����
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
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ö���", 1, 2, 3, true, true);
				break;
			}
			break;

		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 8;
			_viMonster->frameX = 0;
			break;
		}
	}

	//ATTACK1 : �����������϶� �պκи� ������ ����
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ö���", 2, 0, 4, true, true);
		}
		else if(_viMonster->framecount == 200){
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ö���", 1, 2, 3, true, true);
		}
	}
	//ATTACK2 : �����������϶� �պκи� ������ ����
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ö���", 12, 14, 3, false, false);
		}
		else if (_viMonster->framecount == 445) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ö���", 14, 12, 3, false, false);
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;

}

void Cboss_flime::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameHeight() * 2 / 7, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);

	//������ ���� ���ϸ��� �ʴ´�.
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
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
		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(RecCenX(_viMonster->rc),
			RecCenY(_viMonster->rc), _viMonster->targetX, _viMonster->targetY);
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

void Cboss_flime::makeCollisionRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + iter->img->getFrameHeight() * 2 / 7, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);
}
//////////////////////////////////////////////////////////////
//////////Cboss_mushmam!			�����ӽ���!////////////////
//////////////////////////////////////////////////////////////
Cboss_mushmam::Cboss_mushmam()
{
	IMAGE->addFrameImage("�����ӽ���", "images/monsters/mushmam-mushmam.bmp", 432, 2475, 3, 15, true);
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
	//����
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkPlayerXY(py);
		move(bm, mrG, mrP, mrB, smr);
		checkAngle();
		giveFrame();
		deathCheck();
		checkInvincibility();
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
	newMonster.img = IMAGE->findImage("�����ӽ���");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�����ӽ���", 18, 19, 3, true, true);
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
			//���30�̻��̸� RNDMOVE�� ����
			if (_viMonster->patternCount % 100 > 0 && _viMonster->patternCount % 100 < 30) {
				_viMonster->frameX = 0;
				_viMonster->framecount = 0;
				_viMonster->activestate = MONSTERACTIVE::RNDMOVE;
			}
			//����� �� ����Ȯ���ϰ� �� �ٲٱ�
			if (_viMonster->patternCount % 100 == 0)
				_viMonster->activestate = MONSTERACTIVE::FINDING;
		}
		else _viMonster->activestate = MONSTERACTIVE::FINDING;
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//�ɱ�
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
		//�Ѹ���
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
		//�����̴ٰ�
		if (_viMonster->patternCount % 100 < 30) {
			_viMonster->x += cosf(_viMonster->angle) * _viMonster->speed;
			_viMonster->y -= sinf(_viMonster->angle) * _viMonster->speed;
			makeCollisionRect(_viMonster);
		}
		//���30�̻��̸� NONE���� ���ư���
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
		//8����� ���¿� ���� �ִϸ��̼� ����
		switch (_viMonster->activestate)
		{
		case MONSTERACTIVE::NONE:
		case MONSTERACTIVE::FINDING:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 27, 28, 3, false, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 21, 22, 3, false, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 18, 19, 3, false, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 24, 25, 3, false, true);
				break;
			}
			break;
		case MONSTERACTIVE::RNDMOVE:
			switch (_viMonster->movestate)
			{
			case MONSTERMOVESTATE::RIGHTUP:
			case MONSTERMOVESTATE::UP:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 9, 11, 3, true, true);
				break;
			case MONSTERMOVESTATE::LEFTUP:
			case MONSTERMOVESTATE::LEFT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 3, 5, 3, true, true);
				break;
			case MONSTERMOVESTATE::NONE:
			case MONSTERMOVESTATE::LEFTDOWN:
			case MONSTERMOVESTATE::DOWN:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 0, 2, 3, true, true);
				break;
			case MONSTERMOVESTATE::RIGHTDOWN:
			case MONSTERMOVESTATE::RIGHT:
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", 6, 8, 3, true, true);
				break;
			}
			break;
		case MONSTERACTIVE::DEATH:
			_viMonster->frameY = 10;
			_viMonster->frameX = 0;
			break;
		}
	}


	//ATTACK1 : �ɱ�
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			if (color == 0) {
				int arrAtk1[] = { 12, 13, 14, 15, 14, 15, 14, 15, 16, 17 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}
			else if (color == 1) {
				int arrAtk1[] = { 33, 34, 35, 36, 35, 36, 35, 36, 37, 38 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}
			else {
				int arrAtk1[] = { 39, 40, 41, 42, 41, 42, 41, 42, 43, 44 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", arrAtk1, (int)sizeof(arrAtk1) / sizeof(int), 4, false);
			}			
		}
	}
	//ATTACK2 : �Ѹ���
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			int arrAtk2[] = { 13, 13, 12, 23 };
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�����ӽ���", arrAtk2, (int)sizeof(arrAtk2) / sizeof(int), 3, false);
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;

}

void Cboss_mushmam::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() / 6, iter->y + 2, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height * 2 / 3, iter->width, iter->height / 3);

	//������ ���� ���ϸ��� �ʴ´�.
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

	//�Ÿ��� �����ٸ�, �־����� ������ �������� ���ؼ� ����.
	if (distance < _viMonster->range){
		//�÷��̾ ���ϴ� ���� ����ϰ�, ��45������ �������� �̴´�. 180�� ���ؼ� ������ �����´�.
		_viMonster->angle = PI + DEGREE(RND->getFromInTo((int)(angle * 180 / PI) - 45, (int)(angle * 180 / PI) + 45));
		//����.
		while (_viMonster->angle < 0) _viMonster->angle += PI2;
		while (_viMonster->angle > PI2) _viMonster->angle -= PI2;
	}
	//�Ÿ��� �ִٸ�, ��Ÿ����� �ٰ�����.
	else {
		//�÷��̾ ���� �ٰ�����.
		_viMonster->angle = angle;
	}


	//��� Ư���ϰ�, NONE�϶� FIND�� �ֱ������� ����.
	//��� ����ī��Ʈ�� ���̳Ŀ����� �ٽ� NONE���� ���� ATTACK���� ���� ������.
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
			color = RND->getInt(3);		//0�ʷ�, 1����, 2�Ķ�
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
///////Cmushmam_mushroom_G!		�ӽ���_����ӽ���!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_G::Cmushmam_mushroom_G()
{
	IMAGE->addFrameImage("�ӽ���_����ӽ���", "images/monsters/mushmam_mushroom1.bmp", 432, 660, 3, 4, true);
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
	//����
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
	//_stprintf_s(str, "�÷��̾���ǥ : %.1f, %.1f", PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	//TextOut(getMemDC(), 100, 0, str, lstrlen(str));
}

void Cmushmam_mushroom_G::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("�ӽ���_����ӽ���");
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//������ ���� ���ϸ��� �ʴ´�.
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
	//��ǥ ������ �� ����
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
///////Cmushmam_mushroom_P!		�ӽ���_����ӽ���!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_P::Cmushmam_mushroom_P()
{
	IMAGE->addFrameImage("�ӽ���_����ӽ���", "images/monsters/mushmam_mushroom2.bmp", 432, 660, 3, 4, true);
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
	//����
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
	newMonster.img = IMAGE->findImage("�ӽ���_����ӽ���");
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//������ ���� ���ϸ��� �ʴ´�.
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
	//��ǥ ������ �� ����
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
///////Cmushmam_mushroom_B!		�ӽ���_�Ķ��ӽ���!/////////////
//////////////////////////////////////////////////////////////
Cmushmam_mushroom_B::Cmushmam_mushroom_B()
{
	IMAGE->addFrameImage("�ӽ���_�Ķ��ӽ���", "images/monsters/mushmam_mushroom3.bmp", 432, 660, 3, 4, true);
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
	//����
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
	newMonster.img = IMAGE->findImage("�ӽ���_�Ķ��ӽ���");
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
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 3 / 8, iter->y + iter->img->getFrameHeight() * 3 / 4, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);
	//������ ���� ���ϸ��� �ʴ´�.
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
	//��ǥ ������ �� ����
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
////////////////Cyggdrasil!		�̱׵���!////////////////////
//////////////////////////////////////////////////////////////
Cyggdrasil::Cyggdrasil()
{
	IMAGE->addFrameImage("�̱׵���", "images/monsters/ent-ent.bmp", 966, 3850, 3, 11, true);
	EFFECT->addEffect("�̱׵�������", "images/monsters/ent_explosion.bmp", ZEFFECT2, 1920, 1536, 384, 384, 1, 0.4f, 1, 150);
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
	//����
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
				EFFECT->play("�̱׵�������", RecCenX(_viMonster->rc)-10, RecCenY(_viMonster->rc)+100);
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
	newMonster.img = IMAGE->findImage("�̱׵���");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�̱׵���", 0, 2, 2, false, false);
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
		//NONE���� �ö��� �׻� patternCount�� 0�� �ƴ� 250���� ���ּ���.
		if (_viMonster->patternCount > 400) {
			//���������� ��ȣ
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//����
			else {
				_viMonster->patternCount = 0;
				_viMonster->activestate = MONSTERACTIVE::FINDING;
			}
		}
		break;
	case MONSTERACTIVE::FINDING:
		break;
	case MONSTERACTIVE::ATTACK:
		//���극�� & ������
		if (_viMonster->patternCount < 250) {
			if (!_viMonster->isNextPhase) {
				//�ܹ���
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
				//�ֹ���
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
			//��������
			if (_viMonster->patternCount > 125) {
				bm->getTreBos3Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
					_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle, true, 0);
			}

		}
		else {
			//���������� ��ȣ
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//����
			else {
				_viMonster->framecount = 0;
				_viMonster->patternCount = 250;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
		}
		break;
	case MONSTERACTIVE::ATTACK2:
		//�ٶ�3�ٱ�
		if (_viMonster->patternCount < 350) {
			float anglechange = (_viMonster->isNextPhase) ? 0.017 : 0.008;
			if (_viMonster->patternCount % 5 == 0 && _viMonster->patternCount >= 100) {
				//ó���� �÷��̾������� �Ѹ���
				if (_viMonster->patternCount < 150) {
					bm->getTreBos2Bullnstance()->fire(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 100, _viMonster->angle, true, 0);
				}
				//�÷��̾ �������� ���������� Ȯ���ϰ� ���� �̵��ϸ� �Ѹ���
				if (_viMonster->patternCount == 150 || _viMonster->patternCount == 250 ) {
					float nowAngle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
						_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
					if (_viMonster->angle >= nowAngle){		//�÷��̾ �������� ���ߴ�
						_viMonster->isLeft = true;
					}
					else {
						_viMonster->isLeft = false;
					}
				}
				////�̵��ϸ� �Ѹ���(150�̻� 250�̸�)
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
				//�̵��ϸ� �Ѹ���(250�̻�)
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
			//���������� ��ȣ
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//����
			else {
				_viMonster->framecount = 0;
				_viMonster->patternCount = 250;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
		}
		break;
	case MONSTERACTIVE::ATTACK3:
		if (_viMonster->patternCount < 210) {
			//�������� 3��
			if (_viMonster->patternCount % 60 == 0) {
				bomb->addMonster(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2, _viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2 + 50);
			}			
			//���� ������ 7��
			if (_viMonster->isNextPhase) {
				if (_viMonster->patternCount % 28 == 0) {
					bm->getnidBulInstance()->fire(PLAYER->getPlayerAddress().x,
						PLAYER->getPlayerAddress().y,
						_viMonster->angle, 0);
				}
			}
		}
		else {
			//���������� ��ȣ
			if (!_viMonster->oldPhase && _viMonster->isNextPhase) {
				_viMonster->oldPhase = true;
				_viMonster->framecount = 0;
				_viMonster->patternCount = 90;
				_viMonster->activestate = MONSTERACTIVE::NONE;
			}
			//����
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
		//���������Ӷ����� ��� NONE���� ���ƿö� �� 250���� �����ϰ� ����.
		if (_viMonster->patternCount == 90) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 15, 18, 3, false, false);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 6, 8, 3, false, false);
			}
		}
		if (_viMonster->patternCount == 251) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 18, 20, 4, true, true);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 3, 5, 4, true, true);
			}
		}
	}

	//ATTACK1 : ���극��
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				int aniarr[] = { 24, 25, 27, 28, 29, 30, 31 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
			else {
				if (!_viMonster->isLeft) {
					int aniarr[] = { 6, 7, 9, 10, 11, 12, 13 };
					ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
				}
				else {
					int aniarr[] = { 6, 7, 13, 12, 11, 10, 9 };
					ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
				}
			}
		}
	}
	//ATTACK2 : �ٶ�3�ٱ�
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 24, 26, 2, false, false);
			}
			else {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 6, 8, 2, false, false);
			}
		}
	}

	//ATTACK3 : ������ô, (������)��������
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK3) {
		if (_viMonster->framecount == 0) {
			if (_viMonster->isNextPhase) {
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 24, 25, 2, false, false);
			}
			else{
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", 6, 7, 2, false, false);
			}
		}
		if (_viMonster->framecount == 200) {
			if (_viMonster->isNextPhase) {
				/*�� ����Ʈ�Ŵ����� �� ����Ʈ �Ѹ���*/
				int aniarr[] = { 24, 22 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
			else {
				int aniarr[] = { 6, 4 };
				ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 2, false);
			}
		}
	}
	//DEATH : �׾��� ��
	if (_viMonster->activestate == MONSTERACTIVE::DEATH) {
		if (_viMonster->framecount == 0) {
			int aniarr[] = { 30, 28, 30, 28, 26, 24, 25 };
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���", aniarr, sizeof(aniarr) / sizeof(int), 4, false);
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;
}

void Cyggdrasil::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->bossRc[0] = RectMake(iter->x + iter->img->getFrameWidth() / 10, iter->y + iter->img->getFrameHeight() * 2 / 10, iter->width, iter->height);
	iter->bossRc[1] = RectMake(iter->x + iter->img->getFrameWidth() * 4 / 10, iter->y + iter->img->getFrameHeight() * 7 / 10, iter->width * 1 / 4, iter->height * 3 / 5);
	//������ ���� ���ϸ��� �ʴ´�.
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
	//�÷��̾��� ��ǥ�� Ȯ���� ��Ÿ����� ���Դٸ� ���ݻ��µ���.
	float distance = UTIL::getDistance(_viMonster->x, _viMonster->y, PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
	if (distance < _viMonster->range)
	{
		_viMonster->framecount = 0;
		_viMonster->patternCount = 0;
		//���������� 1���̳� 2���̿��� ���, 3�����ݰ���
		if (_viMonster->oldactivestate == MONSTERACTIVE::ATTACK ||
			_viMonster->oldactivestate == MONSTERACTIVE::ATTACK2) {
			_viMonster->activestate = MONSTERACTIVE::ATTACK3;
			_viMonster->oldactivestate = MONSTERACTIVE::ATTACK3;
		}
		//3���̿������, 1�� �Ǵ� 2�� ����
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

		//��ǥ ������ �� ����
		_viMonster->targetX = PLAYER->getPlayerAddress().x;
		_viMonster->targetY = PLAYER->getPlayerAddress().y;
		_viMonster->angle = UTIL::getAngle(_viMonster->rc.left + (_viMonster->rc.right - _viMonster->rc.left) / 2,
			_viMonster->rc.top + (_viMonster->rc.bottom - _viMonster->rc.top) / 2, _viMonster->targetX, _viMonster->targetY);
	}
	//��Ÿ����� �ƴ϶�� �������� ����.
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
	//�����������
	if (!_viMonster->isNextPhase && _viMonster->hp < 360) {
		_viMonster->isNextPhase = true;
	}
	//������������ ���ϳ����� NONE���� �������� ��, patternCount 0���ΰ��� �����ִϸ��̼� ����Ѵ�. 
}
//////////////////////////////////////////////////////////////
//////////Cyggdrasil_bomb!		�̱׵���_��ź!///////////////
//////////////////////////////////////////////////////////////
Cyggdrasil_bomb::Cyggdrasil_bomb()
{
	IMAGE->addFrameImage("�̱׵���_��ź", "images/monsters/bomb-bomb.bmp", 81, 108, 3, 4, true);
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
	//����
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		//���󰡴����� �ƴҶ��� ����
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
	newMonster.img = IMAGE->findImage("�̱׵���_��ź");
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�̱׵���_��ź", 0, 11, 4, false, false);
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
		//��ǥ�������� ���󰡱�
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
		//������ ����
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
	//ATTACK2 : ������
	if (_viMonster->activestate == MONSTERACTIVE::ATTACK2) {
		if (_viMonster->framecount == 0) {
			ANIMATION->changeNonKeyAnimation(_viMonster->ani, "�̱׵���_��ź", 11, 0, 3);
		}
	}

	//������ī��Ʈ����(���º�ȭ �˸��ܿ� ��� ����)
	_viMonster->framecount++;

}

void Cyggdrasil_bomb::knockback(vector<tagMonster>::iterator iter, float x, float y, int damage, float knockbackRange, bool stun)
{
	if (iter->activestate == MONSTERACTIVE::DEATH || iter->activestate == MONSTERACTIVE::ATTACK) return;
	//�ܺ�ȣ����Լ�(���ݿ�������)
	//ª����������
	iter->isGraceperiod = true;
	//�������ݿ�
	iter->hp -= damage;
	//�Ѿ��� ���� �ٶ󺸴� �������� �˹�
	float centerx, centery;
	centerx = iter->rc.left + (iter->rc.right - iter->rc.left) / 2;
	centery = iter->rc.top + (iter->rc.bottom - iter->rc.top) / 2;
	float nbangle = UTIL::getAngle(x, y, centerx, centery);
	iter->x += cosf(nbangle) * knockbackRange;
	iter->y -= sinf(nbangle) * knockbackRange;
	iter->rc = RectMake(iter->x + iter->img->getFrameWidth() * 1 / 6, iter->y + iter->img->getFrameHeight() * 1 / 6, iter->width, iter->height);
	iter->footRc = RectMake(iter->rc.left, iter->rc.top + iter->height / 2, iter->width, iter->height / 2);

	//������ ���� ���ϸ��� �ʴ´�.
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
	//��ǥ ������ �� ����
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
