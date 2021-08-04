#include "framework.h"
#include "Cplayer.h"

HRESULT Cplayer::init()
{
	this->imageInit();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_walkspeed = 2;
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
	setPlayerFrame();
}

void Cplayer::render(HDC hdc)
{
	if (_isDebug)
		RectangleMake(hdc, _player.playerRect);

	IMAGE->frameRender("務晦", hdc, _player.playerRect.left-38 , _player.playerRect.top-28 , _walk_img->getFrameX(), _walk_img->getFrameY());
}

void Cplayer::imageInit()
{
	_walk_img = IMAGE->addFrameImage("務晦", "images/Player/務晦牖憮熱薑.bmp", 300, 800, 3, 8, true, RGB(255, 0, 255));
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
				_player.x+= cosf(DEGREE(135))*_walkspeed;
				_player.y-= sinf(DEGREE(135))*_walkspeed;
				break;
			case UPRIGHT:
				_player.x+= cosf(DEGREE(45))*_walkspeed;
				_player.y-= sinf(DEGREE(45))*_walkspeed;
				break;
			case DOWNRIGHT:
				_player.x+= cosf(DEGREE(315))*_walkspeed;
				_player.y-= sinf(DEGREE(315))*_walkspeed;
				break;
			case DOWNLEFT:
				_player.x+= cosf(DEGREE(225))*_walkspeed;
				_player.y-= sinf(DEGREE(225))*_walkspeed;
				break;
			case UP:
				_player.y -= _walkspeed;
				break;
			case DOWN:
				_player.y += _walkspeed;
				break;
			case LEFT:
				_player.x -= _walkspeed;
				break;
			case RIGHT:
				_player.x += _walkspeed;
				break;
			}
			break;
	}
}

void Cplayer::setPlayerFrame()
{
	_walk_img->setFrameY(_direction);
}
