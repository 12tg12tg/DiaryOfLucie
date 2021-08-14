#pragma once
//===========================================================//
//	commonMacroFunction(�ʿ��� �κ��� ���� ���� ���)		//
//=========================================================//
//���⼭ UTIL namespace�� ����ϰ� ������,
//����������� util.h�� �׻� �� ������Ϻ��� ��������Ǿ����� Ȯ���Ͻÿ�.

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT�����(�»�ܱ���) (�׸��³��� ��������)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//RECT�����(�߽������� ����) 
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//RECT ����
inline int RecCenX(RECT& rc)
{
	return (rc.left + rc.right) / 2;
}
inline int RecCenY(RECT& rc)
{
	return (rc.top + rc.bottom) / 2;
}

//RECT ����/�ʺ�
inline int RecWidth(RECT& rc)
{
	return rc.right - rc.left;
}
inline int RecHeight(RECT& rc)
{
	return rc.bottom - rc.top;
}

//ȸ�� RECT �ٴ�(ZORDER bottom �� ���Ҷ� ����)
inline int RotateRectBottom(RECT& rc, float radian)
{
	int centerx = RecCenX(rc);
	int centery = RecCenY(rc);

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	float diagonal = sqrt(width * width + height * height);

	float leftTopPointAngle = UTIL::getAngle(centerx, centery, rc.left, rc.top);
	float rightTopPointAngle = UTIL::getAngle(centerx, centery, rc.right, rc.top);
	float rightBottomPointAngle = UTIL::getAngle(centerx, centery, rc.right, rc.bottom);
	float leftBottomPointAngle = UTIL::getAngle(centerx, centery, rc.left, rc.bottom);

	float max = centery - sinf(leftTopPointAngle + radian) * diagonal / 2;
	max = (max > centery - sinf(leftBottomPointAngle + radian) * diagonal / 2) ?
		max : centery - sinf(leftBottomPointAngle + radian) * diagonal / 2;
	max = (max > centery - sinf(rightBottomPointAngle + radian) * diagonal / 2) ?
		max : centery - sinf(rightBottomPointAngle + radian) * diagonal / 2;
	max = (max > centery - sinf(rightTopPointAngle + radian) * diagonal / 2) ?
		max : centery - sinf(rightTopPointAngle + radian) * diagonal / 2;

	return max;
}

//�簢�� �׸���(�»�ܱ���)
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
//�簢�� ȸ���׸���(�׵θ���)
inline void RectangleMakeRotateCenter(HDC hdc, RECT rect, float radianAngle)
{
	int centerx = rect.left + (rect.right - rect.left) / 2;
	int centery = rect.top + (rect.bottom - rect.top) / 2;

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	float leftTopPointAngle = UTIL::getAngle(centerx, centery, rect.left, rect.top);
	float rightTopPointAngle = UTIL::getAngle(centerx, centery, rect.right, rect.top);
	float rightBottomPointAngle = UTIL::getAngle(centerx, centery, rect.right, rect.bottom);
	float leftBottomPointAngle = UTIL::getAngle(centerx, centery, rect.left, rect.bottom);
	float hypotenuse = sqrt(width * width + height * height);

	LineMake(hdc,
		centerx + cosf(leftTopPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(leftTopPointAngle + radianAngle) * hypotenuse / 2,
		centerx + cosf(rightTopPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(rightTopPointAngle + radianAngle) * hypotenuse / 2);
	LineMake(hdc,
		centerx + cosf(rightTopPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(rightTopPointAngle + radianAngle) * hypotenuse / 2,
		centerx + cosf(rightBottomPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(rightBottomPointAngle + radianAngle) * hypotenuse / 2);
	LineMake(hdc,
		centerx + cosf(rightBottomPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(rightBottomPointAngle + radianAngle) * hypotenuse / 2,
		centerx + cosf(leftBottomPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(leftBottomPointAngle + radianAngle) * hypotenuse / 2);
	LineMake(hdc,
		centerx + cosf(leftBottomPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(leftBottomPointAngle + radianAngle) * hypotenuse / 2,
		centerx + cosf(leftTopPointAngle + radianAngle) * hypotenuse / 2,
		centery - sinf(leftTopPointAngle + radianAngle) * hypotenuse / 2);
}

//���׸���
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