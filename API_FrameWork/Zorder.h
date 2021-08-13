#pragma once
#include "singleton.h"

enum ZORDERKIND
{
	IMG_NOMAL, IMG_NOMAL_SOUR, IMG_FRAME, IMG_ALPHA, IMG_ALPHA_SOUR, IMG_ALPHA_FRAME,
	IMG_ROTATE, IMG_ROTATE_FRAME, IMG_ROTATE_ALPHA, IMG_ROTATE_ALPHAFRAME,
	IMG_STRETCH, IMG_STRETCH_FRAME, IMG_ROTATESTRETCH, IMG_ROTATESTRETCHFRAME,
	IMG_ANI, IMG_ANIALPHA, OBJ_RECT, OBJ_COLORRECT, OBJ_RECTROTATE,
	TXT_TEXTOUT, TXT_DRAWTEXT
};

enum STRETCHRENDERKIND
{
	STRETCH_WHOLE_RATIO, STRETCH_EACH_SCALE
};

struct tagZorder
{
	ZORDERKIND kind;	
	STRETCHRENDERKIND stretchKind;
	image* img;
	float destX, destY;
	float z;
	float bottom;
	int frameX, frameY;
	int sourX, sourY;
	int sourWidth, sourHeight;
	float angle;
	float ratio;
	float newWidth;
	float newHeight;
	BYTE alpha;
	animation* ani;
	string txt;				// �ؽ�Ʈ
	HFONT font;				//������Ʈ
	RECT txtRC;				//���ڸ� ����� ��ġ
	UINT format;			//drawText ����
	COLORREF txtColor;		//���ڻ�
	COLORREF rectColor;		//���ڻ�
	RECT rc;

	tagZorder(ZORDERKIND _kind, image* _img, int _z, int _x, int _y)
	{
		kind = _kind;
		img = _img;
		z = _z;
		destX = _x;
		destY = _y;
		frameX = frameY = sourX = sourY = sourWidth = sourHeight = alpha = angle = ratio = alpha = newWidth = newHeight = bottom = format = NULL;
		ani = nullptr;
		stretchKind;
	}
};

class Zorder : public Singleton<Zorder>
{
private :
	vector<tagZorder> _vZorder;
public:
	Zorder() {}
	~Zorder() {}

	void release();

	//��������
	void ZorderRender(image* img, float z, float bottom, int destX, int destY);
	void ZorderRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void ZorderFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX = 0, int frameY = 0);
	void ZorderAlphaRender(image* img, float z, float bottom, int destX, int destY, BYTE alpha);
	void ZorderAlphaRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void ZorderAlphaFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY, BYTE alpha);
	void ZorderRotateRender(image* img, float z, float bottom, int centerX, int centerY, float angle);
	void ZorderRotateFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX = 0, int frameY = 0);
	void ZorderRotateAlphaRender(image* img, float z, float bottom, int centerX, int centerY, float angle, BYTE alpha);
	void ZorderRotateAlphaFrameRender(image* img, float z, float bottom, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha);
	void ZorderStretchRender(image* img, float z, float bottom, int centerX, int centerY, float ratio);
	void ZorderStretchRender(image* img, float z, float bottom, int centerX, int centerY, float newWidth, float newHeight);
	void ZorderStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float ratio);
	void ZorderStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float newWidth, float newHeight);
	void ZorderRotateStretchRender(image* img, float z, float bottom, int centerX, int centerY, float angle, float ratio);
	void ZorderRotateStretchFrameRender(image* img, float z, float bottom, int centerX, int centerY, int frameX, int frameY, float angle, float ratio);
	void ZorderAniRender(image* img, float z, float bottom, int destX, int destY, animation* ani);
	void ZorderAniAlphaRender(image* img, float z, float bottom, int destX, int destY, animation* ani, BYTE alpha);

	//����,�۾�
	void ZorderRectangle(RECT rc, float z);
	void ZorderRectangleColor(RECT rc, float z, COLORREF color);
	void ZorderRectangleRotate(RECT rc, float z, float angle);
	void ZorderTextOut(string txt, float z, int destX, int destY, COLORREF color);
	void ZorderDrawText(string txt, float z, RECT txtRC, HFONT font, COLORREF color, UINT format);

	//����
	void Sort(int i, int j);	//Z�� ���Ľ�Ű�� ������.
	inline void ZorderSort();	//Z���� X, Y ������ �����ϴ� ������.
	static bool ZordorCompare(const tagZorder& z1, const tagZorder& z2);	//�񱳱���.

	//���
	void ZorderTotalRender(HDC hdc);


};
