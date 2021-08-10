#pragma once
#include "utils.h"
//===========================================================//
//	commonMacroFunction(필요한 부분은 직접 만들어서 사용)		//
//=========================================================//

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT만들기(좌상단기준) (그리는놈은 따로있음)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//RECT만들기(중심점으로 부터) 
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형 그리기(좌상단기준)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
inline void RectangleMakeRotateCenter(HDC hdc, RECT rect, float degree)
{
	int width = rect.right - (rect.right - rect.left) / 2;
	int height = rect.bottom - (rect.bottom - rect.top) / 2;
	POINT center = { width , height };

	int width2 = rect.right - rect.left;
	int height2 = rect.bottom - rect.top;
	float angle = static_cast<float> (degree * 3.141592 / 180.0f);
	//POINT pts[] = {}
	
	float leftTopPointAngle = UTIL::getAngle(width, height, rect.left, rect.top);
	float rightTopPointAngle = UTIL::getAngle(width, height, rect.right, rect.top);
	float rightBottomPointAngle = UTIL::getAngle(width, height, rect.right, rect.bottom);
	float leftBottomPointAngle = UTIL::getAngle(width, height, rect.left, rect.bottom);
	float hypotenuse = sqrt(width2 * width2 + height2 * height2);


	LineMake(hdc, width + cosf(leftTopPointAngle + degree) * hypotenuse / 2, height - sinf(leftTopPointAngle + degree) * hypotenuse / 2,
		width + cosf(rightTopPointAngle + degree) * hypotenuse / 2, height - sinf(rightTopPointAngle + degree) * hypotenuse / 2);
	LineMake(hdc, width + cosf(rightTopPointAngle + degree) * hypotenuse / 2, height - sinf(rightTopPointAngle + degree) * hypotenuse / 2,
		width + cosf(rightBottomPointAngle + degree) * hypotenuse / 2, height - sinf(rightBottomPointAngle + degree) * hypotenuse / 2);
	LineMake(hdc, width + cosf(rightBottomPointAngle + degree) * hypotenuse / 2, height - sinf(rightBottomPointAngle + degree) * hypotenuse / 2,
		width + cosf(leftBottomPointAngle + degree) * hypotenuse / 2, height - sinf(leftBottomPointAngle + degree) * hypotenuse / 2);
	LineMake(hdc, width + cosf(leftBottomPointAngle + degree) * hypotenuse / 2, height - sinf(leftBottomPointAngle + degree) * hypotenuse / 2,
		width + cosf(leftTopPointAngle + degree) * hypotenuse / 2, height - sinf(leftTopPointAngle + degree) * hypotenuse / 2);
}

//원그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color)
{
	*brush = CreateSolidBrush(color);
	*brush = (HBRUSH)SelectObject(hdc, *brush);
}