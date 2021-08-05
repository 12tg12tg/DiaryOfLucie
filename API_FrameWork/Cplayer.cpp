#include "framework.h"
#include "Cplayer.h"

//이곳의 주목적
//키입력에따른 프레임 랜더
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
	switch (_state) {
	case STATE::WALK:
	case STATE::IDLE:
		IMAGE->frameRender("걷기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _walk_img->getFrameX(), _walk_img->getFrameY());
		break;
	case STATE::RUN:
		IMAGE->frameRender("달리기", hdc, _player.playerRect.left - 38, _player.playerRect.top - 28, _walk_img->getFrameX(), _walk_img->getFrameY());
		break;
	}
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("걷기", "images/Player/걷기순서수정.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
	_run_img = IMAGE->addFrameImage("달리기", "images/Player/달리기수정.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255));
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
	int speed = _walkspeed;
	switch (_state)
	{
	case STATE::RUN:
		speed = _walkspeed * 2;
	case STATE::WALK:
		switch (_direction)
		{
		case UPLEFT:
			_player.x += cosf(DEGREE(135)) * speed;
			_player.y -= sinf(DEGREE(135)) * speed;
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
	if (_state == STATE::IDLE)
		_walk_img->setFrameX(1);
	if (_state == STATE::WALK || _state == STATE::RUN)
	{
		_count++;
		if (_count % 12 == 0)
		{
			_count = 0;
			_index++;

			if (_index > _walk_img->getMaxFrameX())
			{
				_index = 0;
			}
			_walk_img->setFrameX(_index);
			_run_img->setFrameX(_index);
		}
	}
}
