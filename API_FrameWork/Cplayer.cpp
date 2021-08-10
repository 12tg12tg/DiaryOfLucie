#include "framework.h"
#include "Cplayer.h"
#include "bulletmanager.h"

//이곳의 주목적
//키입력에따른 프레임 랜더와 이동

HRESULT Cplayer::init()
{
	this->imageInit();

	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.weapon = WEAPONTYPE::EMPTY;
	_walkspeed = 1.5;

	_direction = DIRECTION::DOWN;
	_moveDirection = _direction;

	_isAutoRun = false;
	_frameswitching = true;
	_hitCount = 300;
	_player.isHit = false;

	return S_OK;
}

void Cplayer::release() {}

void Cplayer::update()
{
	this->inputCheck();
	this->inputDirectionCheck();
	if (_state != STATE::DASH) 
	{
		this->stateCheck();
	}
	this->movePlayer();
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 25);
	this->setPlayerFrame();
	this->hitCheck();
}

void Cplayer::render(HDC hdc)
{
	if (_isDebug) RectangleMake(hdc, _player.playerRect);
	this->renderDashEffecct(hdc);
	if (!_player.isHit) {
		switch (_state)
		{
		case STATE::IDLE:
			IMAGE->frameRender("걷기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, 1, _moveDirection);
			break;
		case STATE::WALK:
			IMAGE->frameRender("걷기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _walk_img->getFrameX(), _moveDirection);
			break;
		case STATE::RUN:
			IMAGE->frameRender("달리기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _run_img->getFrameX(), _moveDirection);
			break;
		case STATE::DASH:
			IMAGE->frameRender("대쉬", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _dash_img->getFrameX(), _moveDirection);
			break;
		case STATE::ATTSTAFF:
			IMAGE->frameRender("기본공격", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _attstaff_img->getFrameX(), _moveDirection);
			break;
		}
	}
	if (_player.isHit) {
		if (_hitCount % 10 <= 5) {
			switch (_state)
			{
			case STATE::IDLE:
				IMAGE->frameRender("걷기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, 1, _moveDirection);
				break;
			case STATE::WALK:
				IMAGE->frameRender("걷기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _walk_img->getFrameX(), _moveDirection);
				break;
			case STATE::RUN:
				IMAGE->frameRender("달리기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _run_img->getFrameX(), _moveDirection);
				break;
			case STATE::DASH:
				IMAGE->frameRender("대쉬", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _dash_img->getFrameX(), _moveDirection);
				break;
			case STATE::ATTSTAFF:
				IMAGE->frameRender("기본공격", hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _attstaff_img->getFrameX(), _moveDirection);
				break;
			}
		}
		else
		{
			switch (_state)
			{
			case STATE::IDLE:
				IMAGE->findImage("걷기")->alphaFrameRender(hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, 1, _moveDirection, 100);
				break;
			case STATE::WALK:
				IMAGE->findImage("걷기")->alphaFrameRender(hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _walk_img->getFrameX(), _moveDirection, 100);
				break;
			case STATE::RUN:
				IMAGE->findImage("달리기")->alphaFrameRender(hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _run_img->getFrameX(), _moveDirection, 100);
				break;
			case STATE::DASH:
				IMAGE->findImage("대쉬")->alphaFrameRender(hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _dash_img->getFrameX(), _moveDirection, 100);
				break;
			case STATE::ATTSTAFF:
				IMAGE->findImage("기본공격")->alphaFrameRender(hdc, _player.playerRect.left - 38, _player.playerRect.top - 58, _attstaff_img->getFrameX(), _moveDirection, 100);
				break;
			}
		}
	}
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("걷기", "images/Player/걷기순서수정.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_run_img = IMAGE->addFrameImage("달리기", "images/Player/달리기수정.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255));
	_dash_img = IMAGE->addFrameImage("대쉬", "images/Player/대쉬수정.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
	_attstaff_img = IMAGE->addFrameImage("기본공격", "images/Player/기본공격.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
}

void Cplayer::inputCheck()
{
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
	{
		if (_isAutoRun)
			_isAutoRun = false;
		else if (!_isAutoRun)
			_isAutoRun = true;
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

void Cplayer::stateCheck()
{
	if (_state != STATE::ATTSTAFF) {
		if (!(_inputDirection.isUp || _inputDirection.isRight ||_inputDirection.isDown || _inputDirection.isLeft))
			_state = STATE::IDLE;
		if (!_isAutoRun&&INPUT->isStayKeyDown(VK_LSHIFT) || _isAutoRun&& !INPUT->isStayKeyDown(VK_LSHIFT))
		{
			if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft) {
				_moveDirection = _direction;
				_state = STATE::RUN;
			}
		}
		else if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft) {
			_moveDirection = _direction;
			_state = STATE::WALK;
		}
		if (INPUT->isOnceKeyDown(VK_LBUTTON))
		{
			_attCount = 0;
			_attIndex = 0;
			_moveDirection = _direction;
			if (_player.weapon == WEAPONTYPE::EMPTY || _player.weapon == WEAPONTYPE::STAFF)
				_state = STATE::ATTSTAFF;
			_attAngle = UTIL::getAngle(_player.x, _player.y-30, m_ptMouse.x, m_ptMouse.y);
			_Cbullet->getMgcBulInstance()->fire(_player.x, _player.y-30, _attAngle, 30);
			this->angleCheckDirection(_attAngle);
		}
	}
	if (INPUT->isOnceKeyDown(VK_SPACE))
	{
		_dashCount = 0;
		_dashIndex = 0;
		_moveDirection = _direction;
		_state = STATE::DASH;
		if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
		{
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
				_dashAngle = 0;
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
		else {
			_dashAngle = UTIL::getAngle(_player.x, _player.y, m_ptMouse.x, m_ptMouse.y);
			this->angleCheckDirection(_dashAngle);
		}
	}
}

void Cplayer::movePlayer()
{
	float speed = _walkspeed;
	switch (_state)
	{
	case STATE::RUN:
		speed = _walkspeed * 2;
	case STATE::WALK:
		switch (_moveDirection)
		{
		case UPLEFT:
			_player.x += cosf(UPLEFTANGLE) * speed;
			_player.y -= sinf(UPLEFTANGLE) * speed;
			break;
		case UPRIGHT:
			_player.x += cosf(UPRIGHTANGLE) * speed;
			_player.y -= sinf(UPRIGHTANGLE) * speed;
			break;
		case DOWNRIGHT:
			_player.x += cosf(DOWNRIGHTANGLE) * speed;
			_player.y -= sinf(DOWNRIGHTANGLE) * speed;
			break;
		case DOWNLEFT:
			_player.x += cosf(DOWNLEFTANGLE) * speed;
			_player.y -= sinf(DOWNLEFTANGLE) * speed;
			break;
		case UP:
			_player.y -= speed;
			break;
		case DOWN:
			_player.y += speed;
			break;
		case LEFT:
			_player.x -= speed;
			break;
		case RIGHT:
			_player.x += speed;
			break;
		}
		break;
	case STATE::DASH:
		_player.x += cosf(_dashAngle) * _walkspeed * 3;
		_player.y -= sinf(_dashAngle) * _walkspeed * 3;
		break;
	case STATE::ATTSTAFF:
		_player.x += cosf(_attAngle);
		_player.y -= sinf(_attAngle);
		break;
	}
}

void Cplayer::setPlayerFrame()
{
	switch (_state)
	{
	case STATE::IDLE:
		_count = 0;
		_index = 0;
		break;

	case STATE::WALK:
		_count++;
		if (_count % 12 == 0)
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
		if (_count % 10 == 0)
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
		if (_dashCount % 5 == 0)
		{
			this->pushbackDashEffect(_player.x-50,_player.y-70,_dashIndex,_moveDirection);
			_dashCount = 0;
			_dashIndex++;
			if (_dashIndex > _dash_img->getMaxFrameX()) {
				_state = STATE::IDLE;
			}
			_dash_img->setFrameX(_dashIndex);
		}
		break;
	case STATE::ATTSTAFF:
		_attCount++;
		if (_attCount % 5 == 0)
		{
			_attCount = 0;
			_attIndex++;
			if (_attIndex > _attstaff_img->getMaxFrameX()) {
				_state = STATE::IDLE;
			}
			_attstaff_img->setFrameX(_attIndex);
		}
		break;
	}
}

void Cplayer::angleCheckDirection(float angle)
{
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
		if (DEGREE(292.5)<angle||angle<DEGREE(22.5))
			if (angle > DEGREE(337.5) || angle < DEGREE(22.5))
				_moveDirection = RIGHT;
			else _moveDirection = DOWNRIGHT;
		else
			if (angle > DEGREE(247.5))
				_moveDirection = DOWN;
			else _moveDirection = DOWNLEFT;
}

void Cplayer::pushbackDashEffect(int x, int y, int FrameX, DIRECTION direction)
{
	DashEffect temp = { IMAGE->addFrameImage("대쉬", "images/Player/대쉬수정.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255)),  x, y, FrameX,direction, 200 };
	_vectDashEffect.push_back(temp);
}

void Cplayer::renderDashEffecct(HDC hdc)
{
	for (_iterDashEffect = _vectDashEffect.begin(); _iterDashEffect !=_vectDashEffect.end();)
	{
		_iterDashEffect->dashEffect->alphaFrameRender(hdc, _iterDashEffect->x, _iterDashEffect->y, _iterDashEffect->dashFrameX, _iterDashEffect->direction, _iterDashEffect->dashAlpha);
		_iterDashEffect->dashAlpha -= 10;

		if (_iterDashEffect->dashAlpha<0) _iterDashEffect=_vectDashEffect.erase(_iterDashEffect); 
		else ++_iterDashEffect;
	}
}

void Cplayer::hitCheck()
{
	if (_player.isHit)
	{
		_hitCount--;
	}
	if (!_player.isHit) {
		_hitCount = 300;
	}
	if (_hitCount < 0) {
		_player.isHit = false;
	}
}