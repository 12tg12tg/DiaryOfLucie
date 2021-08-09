#include "framework.h"
#include "Cplayer.h"

//�̰��� �ָ���
//Ű�Է¿����� ������ ����

HRESULT Cplayer::init()
{
	this->imageInit();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_walkspeed = 1.5;
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	_direction = DIRECTION::DOWN;
	_player.weapon = WEAPONSTATE::EMPTY;
	_isAutoRun = false;
	_frameswitching = true;

	_dashCount = 0;
	_dashIndex = -1;

	return S_OK;
}

void Cplayer::release() {}

void Cplayer::update()
{
	inputCheck();
	if (_state != STATE::DASH) 
	{
		directionCheck();
		stateCheck();
	}
	movePlayer();
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	setPlayerFrame();
}

void Cplayer::render(HDC hdc)
{
	if (_isDebug)RectangleMake(hdc, _player.playerRect);
	switch (_state)
	{
	case STATE::IDLE:
		IMAGE->frameRender("�ȱ�", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, 1, _direction);
		break;
	case STATE::WALK:
		IMAGE->frameRender("�ȱ�", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _walk_img->getFrameX(), _direction);
		break;
	case STATE::RUN:
		IMAGE->frameRender("�޸���", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _run_img->getFrameX(), _direction);
		break;
	case STATE::DASH:
		IMAGE->frameRender("�뽬", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _dash_img->getFrameX(), _direction);
		break;
	}
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("�ȱ�", "images/Player/�ȱ��������.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_run_img = IMAGE->addFrameImage("�޸���", "images/Player/�޸������.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255));
	_dash_img = IMAGE->addFrameImage("�뽬", "images/Player/�뽬����.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255));
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

void Cplayer::directionCheck()
{
	if (_state != STATE::DASH) {
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
}

void Cplayer::stateCheck()
{
	if (!_inputDirection.isUp && !_inputDirection.isRight && !_inputDirection.isDown && !_inputDirection.isLeft)
		_state = STATE::IDLE;
	if (INPUT->isStayKeyDown(VK_LSHIFT) || _isAutoRun)
	{
		if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft )
			_state = STATE::RUN;
	}
	else if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft )
		_state = STATE::WALK;
	if (INPUT->isOnceKeyDown(VK_SPACE))
	{
		_dashCount = 0;
		_dashIndex = -1;
		if (_state == STATE::RUN || _state == STATE::WALK)
		{
			_state = STATE::DASH;
			switch (_direction)
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
			_state = STATE::DASH;
			_dashAngle = UTIL::getAngle(_player.x, _player.y, m_ptMouse.x, m_ptMouse.y);
			angleCheckDirection(_dashAngle);
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
		switch (_direction)
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
	}
}

void Cplayer::setPlayerFrame()
{
	switch (_state)
	{
	case STATE::IDLE:
		_count = 0;
		_index = 1;
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
			_dashCount = 0;
			_dashIndex++;
			if (_dashIndex > _dash_img->getMaxFrameX()) {
				_state = STATE::IDLE;
			}
			_dash_img->setFrameX(_dashIndex);
		}
		break;
	}
}

void Cplayer::angleCheckDirection(float angle)
{
	if (DEGREE(22.5) < angle && angle < DEGREE(202.5))
		if (angle > DEGREE(112.5))
			if (angle > DEGREE(157.5))
				_direction = LEFT;
			else _direction = UPLEFT;
		else
			if (angle > DEGREE(67.5))
				_direction = UP;
			else _direction = UPRIGHT;
	else
		if (DEGREE(292.5)<angle||angle<DEGREE(22.5))
			if (angle > DEGREE(337.5) || angle < DEGREE(22.5))
				_direction = RIGHT;
			else _direction = DOWNRIGHT;
		else
			if (angle > DEGREE(247.5))
				_direction = DOWN;
			else _direction = DOWNLEFT;
}
