#pragma once
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
inline void RectangleMakeRotate(HDC hdc,RECT rect, float degree)
{
	int topx = rect.left;
	int topy = rect.top;
	int leftx = rect.left;
	int lefty = rect.bottom;
	int bottomx = rect.right;
	int bottomy = rect.bottom;
	int rightx = rect.right;
	int righty = rect.top;
	float angle = static_cast<float> (degree * 3.14 / 180.0f);
	POINT pts[] = {
		{topx * cosf(angle) + topy * sinf(angle),-topx * sinf(angle) + topy * cosf(angle)},
		{leftx * cosf(angle) + lefty * sinf(angle),-leftx * sinf(angle) + lefty * cosf(angle)},
		{bottomx * cosf(angle) + bottomy * sinf(angle),-bottomx * sinf(angle) + bottomy * cosf(angle)},
		{rightx * cosf(angle) + righty * sinf(angle),-rightx * sinf(angle) + righty * cosf(angle)}
	};
	Polygon(hdc, pts, 4);
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