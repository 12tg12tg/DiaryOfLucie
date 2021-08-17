#include "framework.h"
#include "Cplayer.h"
#include "bulletmanager.h"
#include "progressBar.h"

//이곳의 주목적
//키입력에따른 프레임 랜더와 이동

HRESULT Cplayer::init()
{
	this->imageInit();
	_player.place = PLACE::DUNGEON;

	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 10, 10);
	_player.weapon = WEAPONTYPE::EMPTY;

	_direction = DIRECTION::DOWN;
	_moveDirection = _direction;

	_isAutoRun = false;
	_frameswitching = true;

	_knockBackTime = 20;
	_gracePeriod = 130;
	_hitCount = 1;
	_knockBackIndex = 0;
	_player.isHit = false;
	_player.isDashHit = false;

	_attCount = 0;
	_attIndex = 0;
	_chargeShotCount = 0;
	_bowCount = 0;

	_dashCount = 0;
	_dashIndex = 0;

	imageLeftCorrection = 50 - (_player.playerRect.right - _player.playerRect.left) / 2;
	imageTopCorrection = 70 - (_player.playerRect.bottom - _player.playerRect.top) / 2;
	shootingCorrection = 20;

	_dieAlpha = 255;

	return S_OK;
}

void Cplayer::release() {
	SAFE_DELETE(_chargeshotBar);
}

void Cplayer::update()
{
	this->inputCheck();
	this->inputDirectionCheck();
	if (!(_state == STATE::DIE || _state == STATE::STOP))
	{
		this->hitStateCheck();
		this->stateCheck();
		this->movePlayer();
		_player.playerRect = RectMakeCenter(_player.x, _player.y, 10, 10);
		this->setPlayerFrame();
	}
	if (_player.weapon == WEAPONTYPE::STAFF) {
		_chargeshotBar->setGauge(_chargeShotCount - 40, 100);
		_chargeshotBar->setX(_player.x);
		_chargeshotBar->setY(_player.y);
	}
	else if(_player.weapon == WEAPONTYPE::BOW) {
		_bowCount++;
	}
}

void Cplayer::render(HDC hdc)
{
	char str[256];
	SetTextColor(hdc, RGB(0, 0, 255));
	if (_isDebug)
	{
		//카메라 영향을 받는 zorder 디버그
		ZORDER->ZorderRectangle(_player.playerRect, ZCOL1);
	}

	this->renderDashEffecct(hdc);

	if (_state == STATE::STOP)
		ZORDER->ZorderFrameRender(_walk_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 1, _moveDirection);
	else if (_state == STATE::DIE)
	{
		ZORDER->ZorderAlphaFrameRender(_die_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 0, 0, _dieAlpha);

		if (_dieAlpha > 50)
			_dieAlpha--;
	}
	else {
		if (_player.isHit && _hitCount % 10 >= 5)  _alpha = 255 / 2;
		else _alpha = 255;
		switch (_state)
		{
		case STATE::ATTBOWIDLE:
			ZORDER->ZorderAlphaFrameRender(_chargeAtt_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection,2, _moveDirection, _alpha);
			break;
		case STATE::IDLE:
			//IMAGE->findImage("걷기")->alphaFrameRender(hdc, _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 1, _moveDirection, 100);
			ZORDER->ZorderAlphaFrameRender(IMAGE->findImage("걷기"), ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 1, _moveDirection, _alpha);
			break;
		case STATE::WALK:
			ZORDER->ZorderAlphaFrameRender(_walk_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _walk_img->getFrameX(), _moveDirection, _alpha);
			break;
		case STATE::ATTBOWWALK:
			ZORDER->ZorderAlphaFrameRender(_bowWalk_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _bowWalk_img->getFrameX(), _bowDirection, _alpha);
			break;
		case STATE::RUN:
			ZORDER->ZorderAlphaFrameRender(_run_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _run_img->getFrameX(), _moveDirection, _alpha);
			break;
		case STATE::DASH:
			ZORDER->ZorderAlphaFrameRender(_dash_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _dash_img->getFrameX(), _moveDirection, _alpha);
			break;
		case STATE::ATTSTAFF:
			ZORDER->ZorderAlphaFrameRender(_attStaff_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _attStaff_img->getFrameX(), _moveDirection, _alpha);
			break;
		case STATE::KNOCKBACK:
			ZORDER->ZorderAlphaFrameRender(_knockBack_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _knockBack_img->getFrameX(), _moveDirection, _alpha);
			break;
		case STATE::STAFFCHARGE:
			ZORDER->ZorderAlphaFrameRender(_chargeAtt_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _chargeAtt_img->getFrameX(), _moveDirection, _alpha);
			break;
		}
	}

	/*이거버림*/
	//else
	//{
	//	switch (_state)
	//	{
	//	case STATE::IDLE:
	//		//IMAGE->frameRender("걷기", hdc, _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 1, _moveDirection);
	//		ZORDER->ZorderFrameRender(_walk_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, 1, _moveDirection);
	//		break;
	//	case STATE::WALK:
	//		ZORDER->ZorderFrameRender(_walk_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _walk_img->getFrameX(), _moveDirection);
	//		break;
	//	case STATE::RUN:
	//		ZORDER->ZorderFrameRender(_run_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _run_img->getFrameX(), _moveDirection);
	//		break;
	//	case STATE::DASH:
	//		ZORDER->ZorderFrameRender(_dash_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _dash_img->getFrameX(), _moveDirection);
	//		break;
	//	case STATE::ATTSTAFF:
	//		ZORDER->ZorderFrameRender(_attStaff_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _attStaff_img->getFrameX(), _moveDirection);
	//		break;
	//	case STATE::KNOCKBACK:
	//		ZORDER->ZorderFrameRender(_knockBack_img, ZUNIT, RecCenY(_player.playerRect), _player.playerRect.left - imageLeftCorrection, _player.playerRect.top - imageTopCorrection, _knockBack_img->getFrameX(), _moveDirection);
	//		break;
	//	}
	//}

	if (_chargeShotCount > 40)
	{
		_chargeshotBar->render();
	}
}

void Cplayer::imageInit()
{
	_alpha = 255;
	_walk_img = IMAGE->addFrameImage("걷기", "images/Player/걷기순서수정.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_bowWalk_img = IMAGE->addFrameImage("활걷기", "images/Player/활.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_run_img = IMAGE->addFrameImage("달리기", "images/Player/달리기수정왼발먼저.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255));
	_dash_img = IMAGE->addFrameImage("대쉬", "images/Player/대쉬수정.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("대쉬이펙트", "images/Player/대쉬수정.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
	_attStaff_img = IMAGE->addFrameImage("기본공격", "images/Player/기본공격.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
	_knockBack_img = IMAGE->addFrameImage("넉백", "images/Player/피격수정.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_die_img = IMAGE->addFrameImage("죽기", "images/Player/사망.bmp", 100, 100, 1, 1, true, RGB(255, 0, 255));
	_chargeAtt_img = IMAGE->addFrameImage("챠지샷", "images/Player/스태프_챠지샷수정.bmp", 300, 800, 3, 8, true);
	_chargeshotBar = new progressBar;
	_chargeshotBar->init("images/Player/챠지샷바백.bmp", "images/Player/챠지샷바프론트.bmp", _player.x, _player.y, 69 * 3, 8 * 3);
}

void Cplayer::inputCheck()
{
	if (INPUT->isStayKeyDown('R')) {
		PLAYERDATA->changeHP(6);
		PLAYERDATA->recoveryStamina(100);
		_state = STATE::IDLE;
		_dieAlpha = 255;
	}
	if (INPUT->isOnceKeyDown('1'))
		_player.weapon = WEAPONTYPE::EMPTY;
	if (INPUT->isOnceKeyDown('2'))
		_player.weapon = WEAPONTYPE::STAFF;
	if (INPUT->isOnceKeyDown('3'))
		_player.weapon = WEAPONTYPE::SWORD;
	//콤보
	if (INPUT->isOnceKeyDown('4'))
		_player.weapon = WEAPONTYPE::BOW;
	//끝
	if (INPUT->isOnceKeyDown('P'))
		this->playerStop();
	if (INPUT->isStayKeyDown('W'))
		_inputDirection.isUp = true;
	else _inputDirection.isUp = false;
	if (INPUT->isStayKeyDown('D'))
		_inputDirection.isRight = true;
	else _inputDirection.isRight = false;
	if (INPUT->isStayKeyDown('S'))
		_inputDirection.isDown = true;
	else _inputDirection.isDown = false;
	if (INPUT->isStayKeyDown('A'))
		_inputDirection.isLeft = true;
	else _inputDirection.isLeft = false;
	if (INPUT->isOnceKeyDown('Q'))
		_isAutoRun = !_isAutoRun;

	if (_state != STATE::DIE) {
		if (_player.weapon == WEAPONTYPE::STAFF && PLAYERDATA->useStamina(10, 1) && INPUT->isStayKeyDown(VK_LBUTTON)) {
			_chargeShotCount++;
			if (_chargeShotCount > 140) {
				_chargeShotCount = 140;
			}
			if (_chargeShotCount == 40) {
				PLAYERDATA->useStamina(10);
			}
		}
	}
	else {
		_chargeShotCount = 0;
	}
}

void Cplayer::inputDirectionCheck()
{
	if (_inputDirection.isUp && !_inputDirection.isLeft && !_inputDirection.isRight)
		_direction = UP;
	else if (_inputDirection.isUp && _inputDirection.isLeft)
		_direction = UPLEFT;
	else if (_inputDirection.isUp && _inputDirection.isRight)
		_direction = UPRIGHT;

	if (_inputDirection.isRight && !_inputDirection.isUp && !_inputDirection.isDown)
		_direction = RIGHT;

	if (_inputDirection.isDown && !_inputDirection.isLeft && !_inputDirection.isRight)
		_direction = DOWN;
	else if (_inputDirection.isDown && _inputDirection.isLeft)
		_direction = DOWNLEFT;
	else if (_inputDirection.isDown && _inputDirection.isRight)
		_direction = DOWNRIGHT;
	if (_inputDirection.isLeft && !_inputDirection.isUp && !_inputDirection.isDown)
		_direction = LEFT;
}

void Cplayer::hitStateCheck()
{
	if (_player.isHit)
	{
		_hitCount++;
	}
	if (_hitCount > _gracePeriod)
	{
		_player.isHit = false;
		_hitCount = 1;
		_knockBackIndex = 0;
	}
}

void Cplayer::stateCheck()
{
	if (PLAYERDATA->getPresentHP() <= 0)
	{
		_state = STATE::DIE;
	}
	else if (1 < _hitCount && _hitCount < _knockBackTime)
	{
		_state = STATE::KNOCKBACK;
	}
	else if (_state != STATE::DASH)
	{
		if (_state != STATE::ATTSTAFF && _state != STATE::ATTSWORD && _state != STATE::STAFFCHARGE)
		{
			if (!(_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)) {
				if ((_player.weapon == WEAPONTYPE::BOW && !INPUT->isStayKeyDown(VK_LBUTTON)) || _player.weapon != WEAPONTYPE::BOW)
					_state = STATE::IDLE;
				else if (INPUT->isStayKeyDown(VK_LBUTTON) && _player.weapon == WEAPONTYPE::BOW && PLAYERDATA->useStamina(5, 1)) {
					_state = STATE::ATTBOWIDLE;
					_attAngle = UTIL::getAngle(_player.x, _player.y - shootingCorrection, CAMMOUSEX, CAMMOUSEY);
					_attAngle = _attAngle - 0.03 + 0.00003 * RND->getFromInTo(0, 2000);
					this->angleCheckDirection(_attAngle);
					if (_bowCount > 5 * 5 - (PLAYERDATA->getData().AtkSpeed / 10)) {
						_Cbullet->getArwBulInstance()->fire(_player.x, _player.y - shootingCorrection, _attAngle, 20);
						_bowCount = 0;
						PLAYERDATA->useStamina(5);
					}
				}
			}
			if ((_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft))
			{
				if(INPUT->isStayKeyDown(VK_LBUTTON) && _player.weapon == WEAPONTYPE::BOW && PLAYERDATA->useStamina(5, 1)) {
					_speed = PLAYERDATA->getData().presentSpeed;
					_moveDirection = _direction;
					_state = STATE::ATTBOWWALK;
					_attAngle = UTIL::getAngle(_player.x, _player.y - shootingCorrection, CAMMOUSEX, CAMMOUSEY);
					this->angleCheckDirection(_attAngle,1);
					if (_bowCount > 5 * 5 - (PLAYERDATA->getData().AtkSpeed / 10)) {
					_attAngle = _attAngle - 0.03 + 0.00003 * RND->getFromInTo(0, 2000);
						_Cbullet->getArwBulInstance()->fire(_player.x, _player.y - shootingCorrection, _attAngle, 20);
						_bowCount = 0;
						PLAYERDATA->useStamina(5);
					}
				}
				else if ((!_isAutoRun && INPUT->isStayKeyDown(VK_LSHIFT) || _isAutoRun && !INPUT->isStayKeyDown(VK_LSHIFT)) && PLAYERDATA->useStamina(2, 1))
				{
					_moveDirection = _direction;
					_state = STATE::RUN;
					_speed = PLAYERDATA->getData().presentSpeed * 2;
				}
				else  {
					_moveDirection = _direction;
					_state = STATE::WALK;
					_speed = PLAYERDATA->getData().presentSpeed;
				}
			}

			if (INPUT->isOnceKeyDown(VK_LBUTTON) && PLAYERDATA->useStamina(5, 1))
			{
				_attAngle = UTIL::getAngle(_player.x, _player.y - shootingCorrection, CAMMOUSEX, CAMMOUSEY);
				_attAngle = _attAngle - 0.03 + 0.00003 * RND->getFromInTo(0, 2000);
				if (_player.weapon == WEAPONTYPE::EMPTY || _player.weapon == WEAPONTYPE::STAFF) {
					_state = STATE::ATTSTAFF;
					_Cbullet->getMgcBulInstance()->fire(_player.x, _player.y - shootingCorrection, _attAngle, 20);
				}
				else if (_player.weapon == WEAPONTYPE::SWORD) {
					_state = STATE::ATTSWORD;
				}
				this->angleCheckDirection(_attAngle);
				PLAYERDATA->useStamina(5);
			}
			if (!(INPUT->isStayKeyDown(VK_LBUTTON)) && _player.weapon == WEAPONTYPE::STAFF && _state != STATE::ATTSTAFF && _chargeShotCount > 40)
			{
				_attAngle = UTIL::getAngle(_player.x, _player.y - shootingCorrection, CAMMOUSEX, CAMMOUSEY);
				_attAngle = _attAngle - 0.03 + 0.00003 * RND->getFromInTo(0, 2000);
				this->angleCheckDirection(_attAngle);

				if (_chargeShotCount < 140) {
					_Cbullet->getMgcBulInstance()->fire(_player.x, _player.y - shootingCorrection, _attAngle, 20 + _chargeShotCount / 2 - 20);
					_state = STATE::ATTSTAFF;
				}
				else if (_chargeShotCount >= 140) {
					_Cbullet->getChargeInstance()->fire(_player.x, _player.y - shootingCorrection, _attAngle, 20 + _chargeShotCount / 2 - 20);
					_state = STATE::STAFFCHARGE;
				}
				_chargeShotCount = 0;
			}
			else if (!(INPUT->isStayKeyDown(VK_LBUTTON)) && _player.weapon == WEAPONTYPE::STAFF && _chargeShotCount < 40)
				_chargeShotCount = 0;
		}
		if (INPUT->isOnceKeyDown(VK_SPACE))
		{
			_state = STATE::DASH;
			PLAYERDATA->useStamina(10);
			if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
			{
				_moveDirection = _direction;
				switch (_moveDirection)
				{
				case UPLEFT:
					_dashAngle = UPLEFTANGLE;
					break;
				case UP:
					_dashAngle = UPANGLE;
					break;
				case UPRIGHT:
					_dashAngle = UPRIGHTANGLE;
					break;
				case RIGHT:
					_dashAngle = RIHGTANGLE;
					break;
				case DOWNRIGHT:
					_dashAngle = DOWNRIGHTANGLE;
					break;
				case DOWN:
					_dashAngle = DOWNANGLE;
					break;
				case DOWNLEFT:
					_dashAngle = DOWNLEFTANGLE;
					break;
				case LEFT:
					_dashAngle = LEFTANGLE;
					break;
				}
			}
			else
			{
				_dashAngle = UTIL::getAngle(_player.x, _player.y, CAMMOUSEX, CAMMOUSEY);
				this->angleCheckDirection(_dashAngle);
			}
		}
	}
	//대쉬어택 만들거에여
	else if (_state == STATE::DASH && _player.weapon == WEAPONTYPE::SWORD) {}
}

void Cplayer::movePlayer()
{
	switch (_state)
	{
	case STATE::RUN:
	case STATE::WALK:
	case STATE::ATTBOWWALK:
		switch (_moveDirection)
		{
		case UPLEFT:
			_player.x += cosf(UPLEFTANGLE) * _speed;
			_player.y -= sinf(UPLEFTANGLE) * _speed;
			break;
		case UPRIGHT:
			_player.x += cosf(UPRIGHTANGLE) * _speed;
			_player.y -= sinf(UPRIGHTANGLE) * _speed;
			break;
		case DOWNRIGHT:
			_player.x += cosf(DOWNRIGHTANGLE) * _speed;
			_player.y -= sinf(DOWNRIGHTANGLE) * _speed;
			break;
		case DOWNLEFT:
			_player.x += cosf(DOWNLEFTANGLE) * _speed;
			_player.y -= sinf(DOWNLEFTANGLE) * _speed;
			break;
		case UP:
			_player.y -= _speed;
			break;
		case DOWN:
			_player.y += _speed;
			break;
		case LEFT:
			_player.x -= _speed;
			break;
		case RIGHT:
			_player.x += _speed;
			break;
		}
		break;
	case STATE::DASH:
		_player.x += cosf(_dashAngle) * PLAYERDATA->getData().presentSpeed * 3;
		_player.y -= sinf(_dashAngle) * PLAYERDATA->getData().presentSpeed * 3;
		break;
	case STATE::ATTSTAFF:
		_player.x += cosf(_attAngle);
		_player.y -= sinf(_attAngle);
		break;
	case STATE::STAFFCHARGE:
		this->angleCheckDirection(_attAngle);
		_player.x += cosf(_attAngle + PI) * 1.5;
		_player.y -= sinf(_attAngle + PI) * 1.5;
		break;
	case STATE::KNOCKBACK:
		this->angleCheckDirection(_knockBackAngle + PI);
		_player.x += cosf(_knockBackAngle) * 1.5;
		_player.y -= sinf(_knockBackAngle) * 1.5;
		break;
	}
}

void Cplayer::setPlayerFrame()
{
	switch (_state)
	{
	case STATE::ATTBOWIDLE:
	case STATE::IDLE:
		_count = 0;
		_index = 0;
		break;
	case STATE::ATTBOWWALK:
		_count++;
		if (_count > 12)
		{
			_count = 0;
			if (_frameswitching)
			{
				_index++;
				if (_index > _bowWalk_img->getMaxFrameX()) {
					_index -= 2;
					_frameswitching = false;
				}
			}
			else if (!_frameswitching)
			{
				_index--;
				if (_index < 0) {
					_index += 2;
					_frameswitching = true;
				}
			}
		}
		_bowWalk_img->setFrameX(_index);
		break;

	case STATE::WALK:
		_count++;
		if (_count > 12)
		{
			_count = 0;
			if (_frameswitching)
			{
				_index++;
				if (_index > _walk_img->getMaxFrameX()) {
					_index -= 2;
					_frameswitching = false;
				}
			}
			else if (!_frameswitching)
			{
				_index--;
				if (_index < 0) {
					_index += 2;
					_frameswitching = true;
				}
			}
		}
		_walk_img->setFrameX(_index);
		break;

	case STATE::RUN:
		_count++;
		if (_count > 10)
		{
			_count = 0;
			_index++;
			if (_index > _run_img->getMaxFrameX()) {
				_index = 0;
			}
			_run_img->setFrameX(_index);
		}
		break;
	case STATE::DASH:
		_dashCount++;
		if (_dashCount % 2 == 0)
			this->pushbackDashEffect(_player.x - 50, _player.y - 70, _dashIndex, _moveDirection);
		if (_dashCount > 5)
		{
			_dashCount = 0;
			_dashIndex++;
			if (_dashIndex > _dash_img->getMaxFrameX()) {
				_state = STATE::IDLE;
				_dashCount = 0;
				_dashIndex = 0;
				_player.isDashHit = false;
			}
			_dash_img->setFrameX(_dashIndex);
		}
		break;
	case STATE::ATTSTAFF:
		_attCount++;
		if (_attCount > 5 - (PLAYERDATA->getData().AtkSpeed / 10))
		{
			_attCount = 0;
			_attIndex++;
			if (_attIndex > _attStaff_img->getMaxFrameX()) {
				_state = STATE::IDLE;
				_attCount = 0;
				_attIndex = 0;
			}
			_attStaff_img->setFrameX(_attIndex);
		}
		break;
	case STATE::KNOCKBACK:
		if (_hitCount % (_knockBackTime / 3) == 0)
		{
			_knockBackIndex++;
			if (_knockBackIndex > _knockBack_img->getMaxFrameX()) {
				_state = STATE::IDLE;
			}
			_knockBack_img->setFrameX(_knockBackIndex);
		}
		break;
	case STATE::STAFFCHARGE:
		_attCount++;
		if (_attCount > 5*2 - (PLAYERDATA->getData().AtkSpeed / 10))
		{
			_attCount = 0;
			_attIndex++;
			if (_attIndex > _chargeAtt_img->getMaxFrameX()-1) {
				_state = STATE::IDLE;
				_attCount = 0;
				_attIndex = 0;
			}
			_chargeAtt_img->setFrameX(_attIndex);
		}
		break;
	}
}

void Cplayer::angleCheckDirection(float angle,bool inputdirection)
{
	if (angle < 0) {
		angle += PI2;
	}
	while (angle > PI2)
	{
		angle -= PI2;
	}
	if (!inputdirection) {
		if (DEGREE(22.5) < angle && angle < DEGREE(202.5))
			if (angle > DEGREE(112.5))
				if (angle > DEGREE(157.5))
					_moveDirection = LEFT;
				else _moveDirection = UPLEFT;
			else
				if (angle > DEGREE(67.5))
					_moveDirection = UP;
				else _moveDirection = UPRIGHT;
		else
			if (DEGREE(292.5) < angle || angle < DEGREE(22.5))
				if (angle > DEGREE(337.5) || angle < DEGREE(22.5))
					_moveDirection = RIGHT;
				else _moveDirection = DOWNRIGHT;
			else
				if (angle > DEGREE(247.5))
					_moveDirection = DOWN;
				else _moveDirection = DOWNLEFT;
	}
	else {
		if (DEGREE(22.5) < angle && angle < DEGREE(202.5))
			if (angle > DEGREE(112.5))
				if (angle > DEGREE(157.5))
					_bowDirection = LEFT;
				else _bowDirection = UPLEFT;
			else
				if (angle > DEGREE(67.5))
					_bowDirection = UP;
				else _bowDirection = UPRIGHT;
		else
			if (DEGREE(292.5) < angle || angle < DEGREE(22.5))
				if (angle > DEGREE(337.5) || angle < DEGREE(22.5))
					_bowDirection = RIGHT;
				else _bowDirection = DOWNRIGHT;
			else
				if (angle > DEGREE(247.5))
					_bowDirection = DOWN;
				else _bowDirection = DOWNLEFT;
	}
}

void Cplayer::pushbackDashEffect(int x, int y, int FrameX, DIRECTION direction)
{
	DashEffect temp = { x, y, FrameX,direction, 200 };
	_vectDashEffect.push_back(temp);
}

void Cplayer::renderDashEffecct(HDC hdc)
{
	for (_iterDashEffect = _vectDashEffect.begin(); _iterDashEffect != _vectDashEffect.end();)
	{
		ZORDER->ZorderAlphaFrameRender(IMAGE->findImage("대쉬이펙트"), ZUNIT, RecCenY(_player.playerRect) - 1, _iterDashEffect->x, _iterDashEffect->y, _iterDashEffect->dashFrameX, _iterDashEffect->direction, _iterDashEffect->dashAlpha);
		_iterDashEffect->dashAlpha -= 10;

		if (_iterDashEffect->dashAlpha < 0) _iterDashEffect = _vectDashEffect.erase(_iterDashEffect);
		else ++_iterDashEffect;
	}
}

void Cplayer::hitPlayer(int bulletX, int bulletY)
{
	if (_state != STATE::STOP) {
		_player.isHit = true;
		PLAYERDATA->changeHP(-1);
		_knockBackAngle = UTIL::getAngle(bulletX, bulletY, _player.x, _player.y);
	}
}

void Cplayer::hitDash()
{
	if (_player.isDashHit != true)
	{
		_player.isDashHit = true;
		PLAYERDATA->changeMP(1);
	}
}

void Cplayer::playerStop()
{
	if (_state != STATE::STOP)
		_state = STATE::STOP;
	else _state = STATE::IDLE;
}