#include "framework.h"
#include "Zorder.h"

void Zorder::release()
{
	_vZorder.clear();
}

void Zorder::ZorderRender(image* img, float z, float bottom, int destX, int destY)
{
    tagZorder _zo(IMG_NOMAL, img, z, destX, destY);
	_zo.bottom = bottom;
    _vZorder.push_back(_zo);
}

void Zorder::ZorderRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	tagZorder _zo(IMG_NOMAL_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY)
{
	tagZorder _zo(IMG_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderAlphaRender(image* img, float z, float bottom, int destX, int destY, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderAlphaRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderAlphaFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateRender(image* img, float z, float bottom, int centerX, int centerY, float angle)
{
	tagZorder _zo(IMG_ROTATE, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.angle = angle;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX, int frameY)
{
	tagZorder _zo(IMG_ROTATE_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.angle = angle;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateAlphaRender(image* img, float z, float bottom, int centerX, int centerY, float angle, BYTE alpha)
{
	tagZorder _zo(IMG_ROTATE_ALPHA, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.alpha = alpha;
	_zo.angle = angle;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateAlphaFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha)
{
	tagZorder _zo(IMG_ROTATE_ALPHAFRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.alpha = alpha;
	_zo.angle = angle;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderStretchRender(image* img, float z, float bottom, int centerX, int centerY, float ratio)
{
	tagZorder _zo(IMG_STRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.ratio = ratio;
	_zo.stretchKind = STRETCH_WHOLE_RATIO;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderStretchRender(image* img, float z, float bottom, int centerX, int centerY, float newWidth, float newHeight)
{
	tagZorder _zo(IMG_STRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.newWidth = newWidth;
	_zo.newHeight = newHeight;
	_zo.stretchKind = STRETCH_EACH_SCALE;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float ratio)
{
	tagZorder _zo(IMG_STRETCH_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.ratio = ratio;
	_zo.stretchKind = STRETCH_WHOLE_RATIO;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float newWidth, float newHeight)
{
	tagZorder _zo(IMG_STRETCH_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.newWidth = newWidth;
	_zo.newHeight = newHeight;
	_zo.stretchKind = STRETCH_EACH_SCALE;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateStretchRender(image* img, float z, float bottom, int centerX, int centerY, float angle, float ratio)
{
	tagZorder _zo(IMG_ROTATESTRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.angle = angle;
	_zo.ratio = ratio;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRotateStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float angle, float ratio)
{
	tagZorder _zo(IMG_ROTATESTRETCHFRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.angle = angle;
	_zo.ratio = ratio;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderAniRender(image* img, float z, float bottom, int destX, int destY, animation* ani)
{
	tagZorder _zo(IMG_ANI, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.ani = ani;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderAniAlphaRender(image* img, float z, float bottom, int destX, int destY, animation* ani, BYTE alpha)
{
	tagZorder _zo(IMG_ANIALPHA, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.ani = ani;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRectangle(RECT rc, float z)
{
	tagZorder _zo(OBJ_RECT, nullptr, z, 0, 0);
	_zo.bottom = rc.bottom;
	_zo.rc = rc;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRectangleColor(RECT rc, float z, COLORREF color)
{
	tagZorder _zo(OBJ_COLORRECT, nullptr, z, 0, 0);
	_zo.bottom = rc.bottom;
	_zo.rc = rc;
	_zo.rectColor = color;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderRectangleRotate(RECT rc, float z, float angle)
{
	tagZorder _zo(OBJ_RECTROTATE, nullptr, z, 0, 0);

	int min = RotateRectBottom(rc, angle);

	_zo.bottom = min;
	_zo.rc = rc;
	_zo.angle = angle;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderTextOut(string txt, float z, int destX, int destY, COLORREF color)
{
	tagZorder _zo(TXT_TEXTOUT, nullptr, z, destX, destY);
	_zo.bottom = destY + 20;
	_zo.txt = txt;
	_zo.txtColor = color;
	_vZorder.push_back(_zo);
}

void Zorder::ZorderDrawText(string txt, float z, RECT txtRC, HFONT font, COLORREF color, UINT format)
{
	tagZorder _zo(TXT_DRAWTEXT, nullptr, z, 0, 0);
	_zo.bottom = txtRC.bottom;
	_zo.txt = txt;
	_zo.txtRC = txtRC;
	_zo.font = font;
	_zo.txtColor = color;
	_zo.format = format;
	_vZorder.push_back(_zo);
}

//여기서부터 Ui
void Zorder::UIRender(image* img, float z, float bottom, int destX, int destY)
{
	tagZorder _zo(IMG_NOMAL, img, z, destX, destY);
	_zo.bottom = bottom;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	tagZorder _zo(IMG_NOMAL_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY)
{
	tagZorder _zo(IMG_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIAlphaRender(image* img, float z, float bottom, int destX, int destY, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.alpha = alpha;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIAlphaRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_zo.alpha = alpha;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIAlphaFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	tagZorder _zo(IMG_ALPHA_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.alpha = alpha;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateRender(image* img, float z, float bottom, int centerX, int centerY, float angle)
{
	tagZorder _zo(IMG_ROTATE, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.angle = angle;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX, int frameY)
{
	tagZorder _zo(IMG_ROTATE_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.angle = angle;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateAlphaRender(image* img, float z, float bottom, int centerX, int centerY, float angle, BYTE alpha)
{
	tagZorder _zo(IMG_ROTATE_ALPHA, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.alpha = alpha;
	_zo.angle = angle;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateAlphaFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha)
{
	tagZorder _zo(IMG_ROTATE_ALPHAFRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.alpha = alpha;
	_zo.angle = angle;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIStretchRender(image* img, float z, float bottom, int centerX, int centerY, float ratio)
{
	tagZorder _zo(IMG_STRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.ratio = ratio;
	_zo.stretchKind = STRETCH_WHOLE_RATIO;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIStretchRender(image* img, float z, float bottom, int centerX, int centerY, float newWidth, float newHeight)
{
	tagZorder _zo(IMG_STRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.newWidth = newWidth;
	_zo.newHeight = newHeight;
	_zo.stretchKind = STRETCH_EACH_SCALE;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float ratio)
{
	tagZorder _zo(IMG_STRETCH_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.ratio = ratio;
	_zo.stretchKind = STRETCH_WHOLE_RATIO;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float newWidth, float newHeight)
{
	tagZorder _zo(IMG_STRETCH_FRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.newWidth = newWidth;
	_zo.newHeight = newHeight;
	_zo.stretchKind = STRETCH_EACH_SCALE;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateStretchRender(image* img, float z, float bottom, int centerX, int centerY, float angle, float ratio)
{
	tagZorder _zo(IMG_ROTATESTRETCH, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.angle = angle;
	_zo.ratio = ratio;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRotateStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float angle, float ratio)
{
	tagZorder _zo(IMG_ROTATESTRETCHFRAME, img, z, centerX, centerY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.angle = angle;
	_zo.ratio = ratio;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIAniRender(image* img, float z, float bottom, int destX, int destY, animation* ani)
{
	tagZorder _zo(IMG_ANI, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.ani = ani;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIAniAlphaRender(image* img, float z, float bottom, int destX, int destY, animation* ani, BYTE alpha)
{
	tagZorder _zo(IMG_ANIALPHA, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.ani = ani;
	_zo.alpha = alpha;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRectangle(RECT rc, float z)
{
	tagZorder _zo(OBJ_RECT, nullptr, z, 0, 0);
	_zo.bottom = rc.bottom;
	_zo.rc = rc;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRectangleColor(RECT rc, float z, COLORREF color)
{
	tagZorder _zo(OBJ_COLORRECT, nullptr, z, 0, 0);
	_zo.bottom = rc.bottom;
	_zo.rc = rc;
	_zo.rectColor = color;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIRectangleRotate(RECT rc, float z, float angle)
{
	tagZorder _zo(OBJ_RECTROTATE, nullptr, z, 0, 0);

	int min = RotateRectBottom(rc, angle);

	_zo.bottom = min;
	_zo.rc = rc;
	_zo.angle = angle;
	_vUiZorder.push_back(_zo);
}

void Zorder::UITextOut(string txt, float z, int destX, int destY, COLORREF color)
{
	tagZorder _zo(TXT_TEXTOUT, nullptr, z, destX, destY);
	_zo.bottom = destY + 20;
	_zo.txt = txt;
	_zo.txtColor = color;
	_vUiZorder.push_back(_zo);
}

void Zorder::UIDrawText(string txt, float z, RECT txtRC, HFONT font, COLORREF color, UINT format)
{
	tagZorder _zo(TXT_DRAWTEXT, nullptr, z, 0, 0);
	_zo.bottom = txtRC.bottom;
	_zo.txt = txt;
	_zo.txtRC = txtRC;
	_zo.font = font;
	_zo.txtColor = color;
	_zo.format = format;
	_vUiZorder.push_back(_zo);
}

//여기부터 정렬

inline void Zorder::ZorderSort()
{
	stable_sort(_vZorder.begin(), _vZorder.end(), ZordorCompare);
}

inline void Zorder::UiZorderSort()
{
	stable_sort(_vUiZorder.begin(), _vUiZorder.end(), ZordorCompare);
}

void Zorder::Sort(int i, int j)
{
	if (i >= j) return;

	float pivot = _vZorder[(i + j) / 2].z;
	int left = i;
	int right = j;

	while (left <= right)
	{
		while (_vZorder[left].z > pivot) left++;
		while (_vZorder[right].z < pivot) right--;
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			left++; right--;
		}
	}

	Sort(i, right);
	Sort(left, j);
}

bool Zorder::ZordorCompare(const tagZorder& z1, const tagZorder& z2)
{
	if (z1.z < z2.z)
	{
		return true;
	}
	else if (z1.z == z2.z)
	{
		if (z1.bottom < z2.bottom)
		{
			return true;
		}
		else if (z1.bottom == z2.bottom)
		{
			if (z1.destX < z2.destX)
			{
				return true;
			}
			else if (z1.destX == z2.destX)
			{
				if (&z1 < &z2) return true;
			}
		}
	}
	return false;
}

void Zorder::ZorderTotalRender(HDC hdc)
{
	this->ZorderSort();

	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].kind)
		{
		case IMG_NOMAL:
			_vZorder[i].img->render(hdc, _vZorder[i].destX, _vZorder[i].destY);
			break;
		case IMG_NOMAL_SOUR:
			_vZorder[i].img->render(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].sourX, _vZorder[i].sourY, _vZorder[i].sourWidth, _vZorder[i].sourHeight);
			break;
		case IMG_FRAME:
			_vZorder[i].img->frameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY);
			break;
		case IMG_ALPHA:
			_vZorder[i].img->alphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].alpha);
			break;
		case IMG_ALPHA_SOUR:
			_vZorder[i].img->alphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].sourX, _vZorder[i].sourY, _vZorder[i].sourWidth, _vZorder[i].sourHeight, _vZorder[i].alpha);
			break;
		case IMG_ALPHA_FRAME:
			_vZorder[i].img->alphaFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].alpha);
			break;
		case IMG_ROTATE:
			_vZorder[i].img->rotateRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].angle);
			break;
		case IMG_ROTATE_FRAME:
			_vZorder[i].img->rotateFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].angle);
			break;
		case IMG_ROTATE_ALPHA:
			_vZorder[i].img->rotateAlphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].angle, _vZorder[i].alpha);
			break;
		case IMG_ROTATE_ALPHAFRAME:
			_vZorder[i].img->rotateAlphaFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].angle, _vZorder[i].alpha);
			break;
		case IMG_STRETCH:
			if (_vZorder[i].stretchKind == STRETCH_WHOLE_RATIO)
				_vZorder[i].img->stretchRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].ratio);
			if (_vZorder[i].stretchKind == STRETCH_EACH_SCALE)
				_vZorder[i].img->stretchRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].newWidth, _vZorder[i].newHeight);
			break;
		case IMG_STRETCH_FRAME:
			if (_vZorder[i].stretchKind == STRETCH_WHOLE_RATIO)
				_vZorder[i].img->stretchFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].ratio);
			if (_vZorder[i].stretchKind == STRETCH_EACH_SCALE)
				_vZorder[i].img->stretchFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].newWidth, _vZorder[i].newHeight);
			break;
		case IMG_ROTATESTRETCH:
			_vZorder[i].img->rotateStretchRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].angle, _vZorder[i].ratio);
			break;
		case IMG_ROTATESTRETCHFRAME:
			_vZorder[i].img->rotateStretchFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].angle, _vZorder[i].ratio);
			break;
		case IMG_ANI:
			_vZorder[i].img->aniRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].ani);
			break;
		case IMG_ANIALPHA:
			_vZorder[i].img->aniAlphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].ani, _vZorder[i].alpha);
			break;
		case OBJ_RECT:
			RectangleMake(hdc, _vZorder[i].rc);
			break;
		case OBJ_RECTROTATE:
			RectangleMakeRotateCenter(hdc, _vZorder[i].rc, _vZorder[i].angle);
			break;
		case OBJ_COLORRECT:
		{
			HBRUSH brush = CreateSolidBrush(_vZorder[i].rectColor);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			RectangleMake(hdc, _vZorder[i].rc);
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
			break;
		case TXT_TEXTOUT:
		{
			HFONT font = _vZorder[i].font;
			HFONT oFont = (HFONT)SelectObject(hdc, font);
			SetTextColor(hdc, _vZorder[i].txtColor);
			TextOut(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].txt.c_str(), _vZorder[i].txt.size());
			SelectObject(hdc, oFont);
			DeleteObject(font);
			SetTextColor(hdc, RGB(255, 255, 255));
		}
			break;
		case TXT_DRAWTEXT:
		{
			HFONT font = _vZorder[i].font;
			HFONT oFont = (HFONT)SelectObject(hdc, font);
			SetTextColor(hdc, _vZorder[i].txtColor);
			DrawText(hdc, _vZorder[i].txt.c_str(), -1, &_vZorder[i].txtRC, _vZorder[i].format);
			SelectObject(hdc, oFont);
			DeleteObject(font);
			SetTextColor(hdc, RGB(255, 255, 255));
		}
			break;
		}
	}
	//벡터초기화
	_vZorder.clear();
}

void Zorder::ZorderUITotalRender(HDC hdc)
{
	this->UiZorderSort();

	for (int i = 0; i < _vUiZorder.size(); i++)
	{
		switch (_vUiZorder[i].kind)
		{
		case IMG_NOMAL:
			_vUiZorder[i].img->render(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY);
			break;
		case IMG_NOMAL_SOUR:
			_vUiZorder[i].img->render(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].sourX, _vUiZorder[i].sourY, _vUiZorder[i].sourWidth, _vUiZorder[i].sourHeight);
			break;
		case IMG_FRAME:
			_vUiZorder[i].img->frameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY);
			break;
		case IMG_ALPHA:
			_vUiZorder[i].img->alphaRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].alpha);
			break;
		case IMG_ALPHA_SOUR:
			_vUiZorder[i].img->alphaRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].sourX, _vUiZorder[i].sourY, _vUiZorder[i].sourWidth, _vUiZorder[i].sourHeight, _vUiZorder[i].alpha);
			break;
		case IMG_ALPHA_FRAME:
			_vUiZorder[i].img->alphaFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].alpha);
			break;
		case IMG_ROTATE:
			_vUiZorder[i].img->rotateRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].angle);
			break;
		case IMG_ROTATE_FRAME:
			_vUiZorder[i].img->rotateFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].angle);
			break;
		case IMG_ROTATE_ALPHA:
			_vUiZorder[i].img->rotateAlphaRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].angle, _vUiZorder[i].alpha);
			break;
		case IMG_ROTATE_ALPHAFRAME:
			_vUiZorder[i].img->rotateAlphaFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].angle, _vUiZorder[i].alpha);
			break;
		case IMG_STRETCH:
			if (_vUiZorder[i].stretchKind == STRETCH_WHOLE_RATIO)
				_vUiZorder[i].img->stretchRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].ratio);
			if (_vUiZorder[i].stretchKind == STRETCH_EACH_SCALE)
				_vUiZorder[i].img->stretchRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].newWidth, _vUiZorder[i].newHeight);
			break;
		case IMG_STRETCH_FRAME:
			if (_vUiZorder[i].stretchKind == STRETCH_WHOLE_RATIO)
				_vUiZorder[i].img->stretchFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].ratio);
			if (_vUiZorder[i].stretchKind == STRETCH_EACH_SCALE)
				_vUiZorder[i].img->stretchFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].newWidth, _vUiZorder[i].newHeight);
			break;
		case IMG_ROTATESTRETCH:
			_vUiZorder[i].img->rotateStretchRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].angle, _vUiZorder[i].ratio);
			break;
		case IMG_ROTATESTRETCHFRAME:
			_vUiZorder[i].img->rotateStretchFrameRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].frameX, _vUiZorder[i].frameY, _vUiZorder[i].angle, _vUiZorder[i].ratio);
			break;
		case IMG_ANI:
			_vUiZorder[i].img->aniRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].ani);
			break;
		case IMG_ANIALPHA:
			_vUiZorder[i].img->aniAlphaRender(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].ani, _vUiZorder[i].alpha);
			break;
		case OBJ_RECT:
			RectangleMake(hdc, _vUiZorder[i].rc);
			break;
		case OBJ_RECTROTATE:
			RectangleMakeRotateCenter(hdc, _vUiZorder[i].rc, _vUiZorder[i].angle);
			break;
		case OBJ_COLORRECT:
		{
			HBRUSH brush = CreateSolidBrush(_vUiZorder[i].rectColor);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			RectangleMake(hdc, _vUiZorder[i].rc);
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		break;
		case TXT_TEXTOUT:
		{
			HFONT font = _vUiZorder[i].font;
			HFONT oFont = (HFONT)SelectObject(hdc, font);
			SetTextColor(hdc, _vUiZorder[i].txtColor);
			TextOut(hdc, _vUiZorder[i].destX, _vUiZorder[i].destY, _vUiZorder[i].txt.c_str(), _vUiZorder[i].txt.size());
			SelectObject(hdc, oFont);
			DeleteObject(font);
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		break;
		case TXT_DRAWTEXT:
		{
			HFONT font = _vUiZorder[i].font;
			//HFONT font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			//	0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕"));
			HFONT oFont = (HFONT)SelectObject(hdc, font);
			SetTextColor(hdc, _vUiZorder[i].txtColor);
			DrawText(hdc, _vUiZorder[i].txt.c_str(), -1, &_vUiZorder[i].txtRC, _vUiZorder[i].format);
			SelectObject(hdc, oFont);
			DeleteObject(font);
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		break;
		}
	}
	//벡터초기화
	for (int i = 0; i < _vUiZorder.size(); i++)
	{
		if (_vUiZorder[i].font) DeleteObject(_vUiZorder[i].font);
	}
	_vUiZorder.clear();
}
