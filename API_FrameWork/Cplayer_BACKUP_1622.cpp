#include "framework.h"
#include "Cplayer.h"

//ÀÌ°÷ÀÇ ÁÖ¸ñÀû
//Å°ÀÔ·Â¿¡µû¸¥ ÇÁ·¹ÀÓ ·£´õ
HRESULT Cplayer::init()
{
	this->imageInit();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_walkspeed = 1;
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	_direction = DIRECTION::DOWN;
	_player.weapon = WEAPONSTATE::EMPTY;
	_index = 0;
	_isAutoRun = false;
	_frameswitching = true;
	return S_OK;
}

void Cplayer::release() {}

void Cplayer::update()
{
	inputCheck();
	directionCheck();
	stateCheck();
	movePlayer();
	_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
	setPlayerFrame();
}

void Cplayer::render(HDC hdc)
{
	if (_isDebug)
		RectangleMake(hdc, _player.playerRect);
	switch (_state)
	{
	case STATE::WALK:
	case STATE::IDLE:
		IMAGE->frameRender("°È±â", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _walk_img->getFrameX(), _walk_img->getFrameY());
		break;
	case STATE::RUN:
		IMAGE->frameRender("´Þ¸®±â", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _run_img->getFrameX(), _walk_img->getFrameY());
		break;
	}
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("°È±â", "images/Player/°È±â¼ø¼­¼öÁ¤.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_run_img = IMAGE->addFrameImage("´Þ¸®±â", "images/Player/´Þ¸®±â¼öÁ¤.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255));
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
	if (INPUT->isOnceKeyDown('Q')) {
		if (_isAutoRun)
			_isAutoRun = false;
		else if (!_isAutoRun)
			_isAutoRun = true;
	}
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
	if (INPUT->isStayKeyDown(VK_LSHIFT) || _isAutoRun)
	{
		if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
			_state = STATE::RUN;
	}
	else if (_inputDirection.isUp || _inputDirection.isRight || _inputDirection.isDown || _inputDirection.isLeft)
		_state = STATE::WALK;
	if (INPUT->isStayKeyDown(VK_SPACE)) {

	}
}

void Cplayer::movePlayer()
{
	int speed = _walkspeed;
	switch (_state)
	{
	case STATE::RUN:
		speed = _walkspeed * 2;
	case STATE::WALK:
<<<<<<< HEAD
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
			_player.playerRect = RectMakeCenter(_player.x, _player.y, 25, 45);
=======
		switch (_direction)
		{
		case UPLEFT:
			_player.x += cosf(DEGREE(135)) * speed;
			_player.y -= sinf(DEGREE(135)) * speed;
>>>>>>> ê³ ì„±ë¯¼ì˜ë¸ŒëŸ°ì¹˜(í”Œë ˆì´ì–´êµ¬í˜„)
			break;
		case UPRIGHT:
			_player.x += cosf(DEGREE(45)) * speed;
			_player.y -= sinf(DEGREE(45)) * speed;
			break;
		case DOWNRIGHT:
			_player.x += cosf(DEGREE(315)) * speed;
			_player.y -= sinf(DEGREE(315)) * speed;
			break;
		case DOWNLEFT:
			_player.x += cosf(DEGREE(225)) * speed;
			_player.y -= sinf(DEGREE(225)) * speed;
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
	}
}

void Cplayer::setPlayerFrame()
{
	_walk_img->setFrameY(_direction);
	switch (_state)
	{
	case STATE::IDLE:
		_count = 0;
		_index = 0;
		_walk_img->setFrameX(1);
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
	}
}