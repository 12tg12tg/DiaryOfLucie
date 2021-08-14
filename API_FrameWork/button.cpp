#include "framework.h"
#include "button.h"

HRESULT Cbutton::init()
{
	return S_OK;
}

void Cbutton::update()
{
	for (_miButton = _mButton.begin(); _miButton!=_mButton.end() ; ++_miButton)
	{
		if (!_miButton->second->buttonOn) continue;

		//오버확인
		if (PtInRect(&_miButton->second->rc, m_ptMouse))
		{
			_miButton->second->isMouseOver = true;
		}
		else {
			_miButton->second->isMouseOver = false;
		}

		//클릭확인
		if (_miButton->second->isMouseOver)
		{
			if (INPUT->isOnceKeyDown(VK_LBUTTON))
			{
				_miButton->second->isClick = true;
				_tempX = m_ptMouse.x - _miButton->second->rc.left;
				_tempY = m_ptMouse.y - _miButton->second->rc.top;
			}
			else if(INPUT->isOnceKeyUp(VK_LBUTTON))
			{
				_miButton->second->isClick = false;
			}
		}

		//드래그확인 후 버튼 갱신
		if (_miButton->second->isMouseOver)
		{
			if (INPUT->isStayKeyDown(VK_LBUTTON))
			{
				_miButton->second->isDrag = true;
				//_miButton->second->rc = RectMake(m_ptMouse.x-_tempX, m_ptMouse.y-_tempY, RecWidth(_miButton->second->rc), RecHeight(_miButton->second->rc));
			}
			else
			{
				_miButton->second->isDrag = false;
			}
		}
	}
}

void Cbutton::release()
{
	removeAll();
}

void Cbutton::render()
{
	if (!_isDebug) return;
	for (_miButton = _mButton.begin(); _miButton != _mButton.end(); ++_miButton)
	{
		if (!_miButton->second->buttonOn) continue;
		ZORDER->ZorderRectangleColor(_miButton->second->rc, 10, _miButton->second->butColor); //레이어10은 매크로 미정의. 가려지지않는 충분히 높은값.
	}
}

Button* Cbutton::addButton(string buttonkey, const int x, const int y, const int width, const int height, COLORREF color)
{
	//추가하려는 키값으로 버튼이 존재하는지 확인
	Button* newbutton = findButton(buttonkey);
	//추가하려는 버튼이 이미 있으면 리턴
	if (newbutton) return newbutton;

	newbutton = new Button;
	newbutton->rc = RectMake(x, y, width, height);
	newbutton->isClick = false;
	newbutton->isDrag = false;
	newbutton->isMouseOver = false;
	newbutton->butColor = color;
	newbutton->buttonOn = false;
	newbutton->img = nullptr;			//아직 미구현.

	_mButton.insert(make_pair(buttonkey, newbutton));
	return newbutton;
}

Button* Cbutton::addButtonCenter(string buttonkey, const int centerx, const int centery, const int width, const int height, COLORREF color)
{
	//추가하려는 키값으로 버튼이 존재하는지 확인
	Button* newbutton = findButton(buttonkey);
	//추가하려는 버튼이 이미 있으면 리턴
	if (newbutton) return newbutton;

	newbutton = new Button;
	newbutton->rc = RectMakeCenter(centerx, centery, width, height);
	newbutton->isClick = false;
	newbutton->isDrag = false;
	newbutton->isMouseOver = false;
	newbutton->butColor = color;
	newbutton->buttonOn = false;
	newbutton->img = nullptr;			//아직 미구현.

	_mButton.insert(make_pair(buttonkey, newbutton));
	return newbutton;
}

Button* Cbutton::findButton(string buttonkey)
{
	//해당키 검색
	_miButton = _mButton.find(buttonkey);
	//키를 찾으면 반환
	if (_miButton != _mButton.end())
	{
		return _miButton->second;
	}
	//없으면 널
	return NULL;
}

void Cbutton::buttonOn(string buttonkey)
{
	_miButton = _mButton.find(buttonkey);
	_miButton->second->buttonOn = true;
}

void Cbutton::buttonOff(string buttonkey)
{
	_miButton = _mButton.find(buttonkey);
	_miButton->second->buttonOn = false;
}

void Cbutton::removeButton(string buttonkey)
{
	//해당키 검색
	_miButton = _mButton.find(buttonkey);

	if (_miButton != _mButton.end())
	{
		SAFE_DELETE(_miButton->second);
		_mButton.erase(_miButton);
	}
}

void Cbutton::removeAll()
{
	//전체를 돌면서 삭제
	_miButton = _mButton.begin();

	for (_miButton; _miButton != _mButton.end(); )
	{
		if (_miButton->second != NULL)
		{
			SAFE_DELETE(_miButton->second);
			_miButton = _mButton.erase(_miButton);
		}
		else ++_miButton;
	}
	_mButton.clear();
}

bool Cbutton::isMouseOver(string buttonkey)
{
	Button* but = findButton(buttonkey);
	if (but != NULL) return but->isMouseOver;
	return NULL;
}

bool Cbutton::isClick(string buttonkey)
{
	Button* but = findButton(buttonkey);
	if (but != NULL) return but->isClick;
	return NULL;
}

bool Cbutton::isDrag(string buttonkey)
{
	Button* but = findButton(buttonkey);
	if (but != NULL) return but->isDrag;
	return NULL;
}

void Cbutton::setIsDebug(bool isDebug)
{
	this->_isDebug = isDebug;
}
