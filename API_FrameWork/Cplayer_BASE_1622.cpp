#include "framework.h"
#include "Cplayer.h"

HRESULT Cplayer::init()
{
	this->imageInit();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_speed = 5;
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	_direction = DIRECTION::DOWN;
	_player.weapon = WEAPONSTATE::EMPTY;
	
	return S_OK;
}

void Cplayer::release(){}

void Cplayer::update()
{
	inputCheck();
	directionCheck();
	stateCheck();
	movePlayer();
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);

}

void Cplayer::render(HDC hdc)
{
	if (_isDebug)
		RectangleMake(hdc, _player.playerRect);
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("°È±â", "images/Player/°È±â.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
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
}

void Cplayer::directionCheck()
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
	if (!_inputDirection.isUp && !_inputDirection.isRight && !_inputDirection.isDown && !_inputDirection.isLeft)
		_state = STATE::IDLE;
	if (INPUT->isStayKeyDown(VK_LSHIFT)) {
		if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
			_state = STATE::RUN;
	}
	else if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
		_state = STATE::WALK;
}

void Cplayer::movePlayer()
{
	switch (_state) 
	{
	case STATE::WALK:
			switch(_direction)
			{
			case UPLEFT:
				_player.x+= cosf(DEGREE(135))*_speed;
				_player.y-= sinf(DEGREE(135))*_speed;
				break;
			case UPRIGHT:
				_player.x+= cosf(DEGREE(45))*_speed;
				_player.y-= sinf(DEGREE(45))*_speed;
				break;
			case DOWNRIGHT:
				_player.x+= cosf(DEGREE(315))*_speed;
				_player.y-= sinf(DEGREE(315))*_speed;
				break;
			case DOWNLEFT:
				_player.x+= cosf(DEGREE(225))*_speed;
				_player.y-= sinf(DEGREE(225))*_speed;
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
	//case STATE::RUN:

	}
}
