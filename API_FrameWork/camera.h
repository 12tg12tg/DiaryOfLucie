#pragma once
#include "singleton.h"

enum class CAMERASTATE			//¡Ú
{
	FOLLOWPIVOT,
	CHANGEPIVOT,
	SHAKE
};

struct tagShakeTime						//¡Ú
{
	int current;
	int max;
	int cool;
};

enum FADEKIND							//¡Ú
{
	FADE_IN, FADE_OUT
};

struct tagFadeInfo						//¡Ú
{
	FADEKIND fadeKind;
	bool isStart;
	int minus;
	int alpha;
};

class camera : public Singleton<camera>
{
private:
	CAMERASTATE _state;							//¡Ú
	RECT _cameraRect;
	float _pivotX, _pivotY;
	float _maxX, _maxY;
	float _minX, _minY;
	float _distanceX, _distanceY;
	float _absDistanceX, _absDistanceY;
	float _changePivotX;
	float _changePivotY;
	float _changeSpeed;
	POINT _moveToPivot;
	POINT _shakePivot;
	POINT _savePivot;
	float _shakePower;
	tagShakeTime _shakeTime;
	bool _isShake;											//¡Ú

	tagFadeInfo _fadeInfo;
public:
	camera();
	~camera();

	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);
	void update(float pivotX, float  pivotY);
	void release();

	void Rectangle(HDC hdc, RECT rc);				//------------------------------¡Ú
	void Rectangle(HDC hdc, int left, int top, int width, int height);
	void FrameRect(HDC hdc, RECT rc, COLORREF color);
	void LineMake(HDC hdc, int startX, int startY, int endX, int endY);
	RECT RectMake(float x, float y, int width, int height);
	void Render(HDC hdc, image* ig, int destX, int destY);
	void Render(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei);
	void FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX = 0, int frameY = 0);
	void StretchRender(HDC hdc, image* ig, int destX, int destY, float size);
	void StretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY);
	void StretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float size);
	void StretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY);
	void AlphaRender(HDC hdc, image* ig, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei, BYTE alpha);
	void AlphaFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha);
	void RotateRender(HDC hdc, image* img, int centerX, int centerY, float angle);
	void RotateFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX = 0, int frameY = 0);
	void RotateAlphaRender(HDC hdc, image* img, int centerX, int centerY, float angle, BYTE alpha);
	void RotateAlphaFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha);//------------------------------¡Ú

	void FadeInit(int time, FADEKIND fadeKind);			//------------------------------¡Ú
	void FadeStart();
	void FadeUpdate();
	void FadeRender(HDC hdc);
	bool& getFadeIsStart() { return _fadeInfo.isStart; }//------------------------------¡Ú

	void textOut(HDC hdc, int x, int y, const char* text, COLORREF color = RGB(255, 0, 0));

	void movePivot(float x, float y);
	void ChangePivot(float x, float y, float speed);
	void setShake(float power, int time, int cool);
	int getRelativeX(float x);
	int getRelativeY(float y);
	float getPivotX() { return _pivotX; }
	float getPivotY() { return _pivotY; }
	float getDistanceX() { return _distanceX; }
	float getDistanceY() { return _distanceY; }

	bool getIsShake() { return _isShake; }

	RECT getRect() { return _cameraRect; }
	POINT getRelativeMouse(POINT ptMouse);
	RECT getRelativeRect(RECT rc);

	void setCMState(CAMERASTATE state) { _state = state; }
	CAMERASTATE getCMState() { return _state; }
};

