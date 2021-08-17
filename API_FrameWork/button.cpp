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
			if (INPUT->isOnceKeyUp(VK_LBUTTON))
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
			}
			else
			{
				_miButton->second->isDrag = false;
			}
		}

		//수정가능사각형
		if (_miButton->second->fixMode)
		{
			_miButton->second->smallRect = RectMake(_miButton->second->rc.left + differ, _miButton->second->rc.top + differ, RecWidth(_miButton->second->rc) - differ*2, RecHeight(_miButton->second->rc) - differ*2);
			_miButton->second->bigRect = RectMake(_miButton->second->rc.left - differ, _miButton->second->rc.top - differ, RecWidth(_miButton->second->rc) + differ*2, RecHeight(_miButton->second->rc) + differ*2);
			//드래그중이면서 작은사각형 안에 있다면, 옮기기.
			if ((INPUT->isStayKeyDown(VK_LBUTTON)) && PtInRect(&_miButton->second->smallRect, m_ptMouse))
			{
				_miButton->second->rc = RectMake(m_ptMouse.x - _tempX, m_ptMouse.y - _tempY, RecWidth(_miButton->second->rc), RecHeight(_miButton->second->rc));
			}
			//큰사각형에 겹쳐있는데, 작은사각형은 아니면서, 드래그중이라면, 
			if (PtInRect(&_miButton->second->bigRect, m_ptMouse) && !PtInRect(&_miButton->second->smallRect, m_ptMouse) && INPUT->isStayKeyDown(VK_LBUTTON))
			{
				RECT lefttop = RectMake(_miButton->second->bigRect.left, _miButton->second->bigRect.top, differ*2, differ*2);
				RECT righttop = RectMake(_miButton->second->smallRect.right, _miButton->second->bigRect.top, differ*2, differ*2);
				RECT leftbottom = RectMake(_miButton->second->bigRect.left, _miButton->second->smallRect.bottom, differ*2, differ*2);
				RECT rightbottom = RectMake(_miButton->second->smallRect.right, _miButton->second->smallRect.bottom, differ*2, differ*2);
				RECT left = RectMake(_miButton->second->bigRect.left, _miButton->second->smallRect.top, _miButton->second->smallRect.left - _miButton->second->bigRect.left, RecHeight(_miButton->second->smallRect));
				RECT top = RectMake(_miButton->second->smallRect.left, _miButton->second->bigRect.top, RecWidth(_miButton->second->smallRect), _miButton->second->smallRect.top - _miButton->second->bigRect.top);
				RECT right = RectMake(_miButton->second->smallRect.right, _miButton->second->smallRect.top, _miButton->second->bigRect.right - _miButton->second->smallRect.right, RecHeight(_miButton->second->smallRect));
				RECT bottom = RectMake(_miButton->second->smallRect.left, _miButton->second->smallRect.bottom, RecWidth(_miButton->second->smallRect), _miButton->second->bigRect.bottom - _miButton->second->smallRect.bottom);

				int l = _miButton->second->rc.left;
				int t = _miButton->second->rc.top;
				int r = _miButton->second->rc.right;
				int b = _miButton->second->rc.bottom;

				if (PtInRect(&lefttop, m_ptMouse)) l = m_ptMouse.x, t = m_ptMouse.y;
				if (PtInRect(&righttop, m_ptMouse)) r = m_ptMouse.x, t = m_ptMouse.y;
				if (PtInRect(&leftbottom, m_ptMouse)) l = m_ptMouse.x, b = m_ptMouse.y;
				if (PtInRect(&rightbottom, m_ptMouse)) r = m_ptMouse.x, b = m_ptMouse.y;
				if (PtInRect(&left, m_ptMouse)) l = m_ptMouse.x ;
				if (PtInRect(&top, m_ptMouse)) t = m_ptMouse.y;
				if (PtInRect(&right, m_ptMouse)) r = m_ptMouse.x;
				if (PtInRect(&bottom, m_ptMouse)) b = m_ptMouse.y;

				(l > r) ? swap(l, r) : NULL;
				(t > b) ? swap(t, b) : NULL;
				_miButton->second->rc = { l, t, r, b };
			}

		}
	}


}

void Cbutton::release()
{
	removeAll();
}

void Cbutton::render(HDC hdc)
{
	for (_miButton = _mButton.begin(); _miButton != _mButton.end(); ++_miButton)
	{
		if (_miButton->second->fixMode) {
			TCHAR str[128];
			ZORDER->UIRectangleColor(_miButton->second->rc, ZUIFIRST, _miButton->second->butColor);
			wsprintf(str, "RectMake(%d, %d, %d, %d);", _miButton->second->rc.left, _miButton->second->rc.top, RecWidth(_miButton->second->rc), RecHeight(_miButton->second->rc));
			ZORDER->UITextOut(str, ZUIFIRST, _miButton->second->rc.left, _miButton->second->rc.top - 20, RGB(0, 0, 255));			
		}
	}
	if (!_isDebug) return;
	for (_miButton = _mButton.begin(); _miButton != _mButton.end(); ++_miButton)
	{
		if (!_miButton->second->buttonOn || _miButton->second->fixMode) continue;
		ZORDER->UIRectangleColor(_miButton->second->rc, ZUIFIRST, _miButton->second->butColor);
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
	newbutton->fixMode = false;
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
	newbutton->fixMode = false;
	newbutton->img = nullptr;			//아직 미구현.

	_mButton.insert(make_pair(buttonkey, newbutton));
	return newbutton;
}

Button* Cbutton::addFixableRect(string buttonkey, COLORREF color)
{
	//추가하려는 키값으로 버튼이 존재하는지 확인
	Button* newbutton = findButton(buttonkey);
	//추가하려는 버튼이 이미 있으면 리턴
	if (newbutton) return newbutton;

	newbutton = new Button;
	newbutton->rc = RectMakeCenter(0, 0, 100, 100);
	newbutton->isClick = false;
	newbutton->isDrag = false;
	newbutton->isMouseOver = false;
	newbutton->butColor = color;
	newbutton->buttonOn = true;
	newbutton->fixMode = true;
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
	_miButton->second->isMouseOver = false;
	_miButton->second->isClick = false;
	_miButton->second->isDrag = false;
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
