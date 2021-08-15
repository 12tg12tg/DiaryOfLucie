#include "framework.h"
#include "camera.h"

camera::camera()
{
	_cameraRect = { 0,0,0,0 };
	_pivotX = 0.f;
	_pivotY = 0.f;
	_maxX = 0.f;
	_maxY = 0.f;
	_minX = 0.f;
	_minY = 0.f;
	_distanceX = 0.f;
	_distanceY = 0.f;
	_isShake = false;
}

camera::~camera()
{
}

HRESULT camera::init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY)
{
	_maxX = maxX;
	_maxY = maxY;
	_minX = minX;
	_minY = minY;
	_pivotX = pivotX;
	_pivotY = pivotY;
	_distanceX = disX;
	_distanceY = disY;
	_absDistanceX = disX;
	_absDistanceY = disY;

	_cameraRect = RectMake(_pivotX - disX, _pivotY - disY, WINSIZEX, WINSIZEY);

	_state = CAMERASTATE::FOLLOWPIVOT;

	return S_OK;
}

void camera::update(float pivotX, float pivotY)
{
	float angle;
	float _x;
	float _y;

	switch (_state)
	{
	case CAMERASTATE::FOLLOWPIVOT:
		_pivotX = _moveToPivot.x;
		_pivotY = _moveToPivot.y;
		_cameraRect = RectMake(_pivotX - _absDistanceX, _pivotY - _absDistanceY, WINSIZEX, WINSIZEY);
		_distanceX = _absDistanceX;
		_distanceY = _absDistanceY;
		_savePivot.x = _pivotX;
		_savePivot.y = _pivotY;

		if (_cameraRect.left <= _minX)
		{
			_cameraRect.left = _minX;
			_cameraRect.right = _minX + WINSIZEX;
			_distanceX = _pivotX - _cameraRect.left;
		}
		if (_cameraRect.right >= _maxX)
		{
			_cameraRect.right = _maxX;
			_cameraRect.left = _maxX - WINSIZEX;
			_distanceX = _pivotX - _cameraRect.left;
		}
		if (_cameraRect.top <= _minY)
		{
			_cameraRect.top = _minY;
			_cameraRect.bottom = _minY + WINSIZEY;
			_distanceY = _pivotY - _cameraRect.top;

		}
		if (_cameraRect.bottom >= _maxY)
		{
			_cameraRect.bottom = _maxY;
			_cameraRect.top = _maxY - WINSIZEY;
			_distanceY = _pivotY - _cameraRect.top;
		}
		break;


	case CAMERASTATE::CHANGEPIVOT:
		angle = UTIL::getAngle(_pivotX, _pivotY, _changePivotX, _changePivotY);
		if (_pivotX == _changePivotX && _pivotY == _changePivotY)
		{
			_state = CAMERASTATE::FOLLOWPIVOT;
			break;
		}
		_x = _pivotX;
		_y = _pivotY;
		_savePivot.x = _pivotX;
		_savePivot.y = _pivotY;
		_x += cosf(angle) * _changeSpeed;
		_y -= sinf(angle) * _changeSpeed;
		_cameraRect = RectMake(_x - _distanceX, _y - _distanceY, WINSIZEX, WINSIZEY);

		_pivotX = _x;
		_pivotY = _y;

		//pivot 거리가 충분히 가까워졌다면 그냥 자석
		if (UTIL::getDistance(_x, _y, _changePivotX, _changePivotY) < _changeSpeed + 1.f)
		{
			_pivotX = _changePivotX;
			_pivotY = _changePivotY;
			pivotX = _pivotX;
			pivotY = _pivotY;
			_savePivot.x = _pivotX;
			_savePivot.y = _pivotY;
			_state = CAMERASTATE::FOLLOWPIVOT;
		}
		break;
	case CAMERASTATE::SHAKE:
		break;
	}


	if (_isShake == true)
	{
		_shakeTime.current++;
		if (_shakeTime.current > _shakeTime.max)
		{
			_isShake = false;
			_cameraRect = RectMake(_savePivot.x - _distanceX, _savePivot.y - _distanceY, WINSIZEX, WINSIZEY);
		}
		if (_shakeTime.current % _shakeTime.cool == 0)
		{
			_shakePivot.x = RND->getFromInTo(_savePivot.x - _shakePower, _savePivot.x + _shakePower);
			_shakePivot.y = RND->getFromInTo(_savePivot.y - _shakePower, _savePivot.y + _shakePower);
			_cameraRect = RectMake(_shakePivot.x - _distanceX, _shakePivot.y - _distanceY, WINSIZEX, WINSIZEY);
		}
	}
}

void camera::release()
{
}

void camera::Rectangle(HDC hdc, RECT rc)
{
}

void camera::Rectangle(HDC hdc, int left, int top, int width, int height)
{
}

void camera::FrameRect(HDC hdc, RECT rc, COLORREF color)
{
}

void camera::LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
}

RECT camera::RectMake(float x, float y, int width, int height)
{
    return RECT();
}

void camera::Render(HDC hdc, image* ig, int destX, int destY)
{
	ig->render(hdc, getRelativeX(destX), getRelativeY(destY));
}

void camera::Render(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei)
{
}

void camera::FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY)
{
}

void camera::StretchRender(HDC hdc, image* ig, int destX, int destY, float size)
{
}

void camera::StretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY)
{
}

void camera::StretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float size)
{
}

void camera::StretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY)
{
}

void camera::AlphaRender(HDC hdc, image* ig, int destX, int destY, BYTE alpha)
{
}

void camera::AlphaRender(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei, BYTE alpha)
{
}

void camera::AlphaFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
}

void camera::RotateRender(HDC hdc, image* img, int centerX, int centerY, float angle)
{
}

void camera::RotateFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX, int frameY)
{
}

void camera::RotateAlphaRender(HDC hdc, image* img, int centerX, int centerY, float angle, BYTE alpha)
{
}

void camera::RotateAlphaFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha)
{
}

void camera::FadeInit(int time, FADEKIND fadeKind)
{
}

void camera::FadeStart()
{
}

void camera::FadeUpdate()
{
}

void camera::FadeRender(HDC hdc)
{
}

void camera::textOut(HDC hdc, int x, int y, const char* text, COLORREF color)
{
}

void camera::movePivot(float x, float y)
{
}

void camera::ChangePivot(float x, float y, float speed)
{
}

void camera::setShake(float power, int time, int cool)
{
}

int camera::getRelativeX(float x)
{
    return 0;
}

int camera::getRelativeY(float y)
{
    return 0;
}

POINT camera::getRelativeMouse(POINT ptMouse)
{
    return POINT();
}

RECT camera::getRelativeRect(RECT rc)
{
    return RECT();
}
