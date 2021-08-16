#pragma once
#include "singleton.h"

enum class CAMERASTATE
{
	FOLLOWPIVOT,
	CHANGEPIVOT,
	SHAKE
};

struct tagShakeTime	
{
	int current;
	int max;
	int cool;
};

enum FADEKIND
{
	FADE_IN, FADE_OUT
};

struct tagFadeInfo	
{
	FADEKIND fadeKind;
	bool isStart;
	int minus;
	int alpha;
};

class camera : public Singleton<camera>
{
private:
	//�ʱ�ȭ����
	float _cameraSizeX;
	float _cameraSizeY;
	CAMERASTATE _state;	
	RECT _cameraRect;
	float _pivotX, _pivotY;
	float _maxX, _maxY;
	float _minX, _minY;
	float _distanceX, _distanceY;

	//���밪
	float _absDistanceX, _absDistanceY;

	//�ǹ�����
	float _changePivotX;
	float _changePivotY;
	float _changeSpeed;

	//�ǹ���ǥ����
	POINT _moveToPivot;

	//ȭ�鶳��.
	POINT _shakePivot;
	POINT _savePivot;
	float _shakePower;
	tagShakeTime _shakeTime;
	bool _isShake;

	//���̵��ξƿ�
	tagFadeInfo _fadeInfo;
public:
	camera();
	~camera();

	//�ǹ���ǥ, ��ü������ �ִ�/�ּ�ũ��, �Ÿ�.
	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);
	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY, float sizeX, float sizeY);
	void update();
	void release();

	//�ǹ��ݿ��Ͽ� ��ǥ ��ܼ� �����ϱ�.
	//void RelativeRectangle(HDC hdc, RECT rc);
	//void RelativeRectangle(HDC hdc, int left, int top, int width, int height);
	//void RelativeFrameRect(HDC hdc, RECT rc, COLORREF color);
	//void RelativeLineMake(HDC hdc, int startX, int startY, int endX, int endY);
	//RECT RelativeRectMake(float x, float y, int width, int height);
	//void RelativeRender(HDC hdc, image* ig, int destX, int destY);
	//void RelativeRender(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei);
	//void RelativeFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX = 0, int frameY = 0);
	//void RelativeStretchRender(HDC hdc, image* ig, int destX, int destY, float size);
	//void RelativeStretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY);
	//void RelativeStretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float size);
	//void RelativeStretchFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY);
	//void RelativeAlphaRender(HDC hdc, image* ig, int destX, int destY, BYTE alpha);
	//void RelativeAlphaRender(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWid, int sourHei, BYTE alpha);
	//void RelativeAlphaFrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha);
	//void RelativeRotateRender(HDC hdc, image* img, int centerX, int centerY, float angle);
	//void RelativeRotateFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX = 0, int frameY = 0);
	//void RelativeRotateAlphaRender(HDC hdc, image* img, int centerX, int centerY, float angle, BYTE alpha);
	//void RelativeRotateAlphaFrameRender(HDC hdc, image* img, int centerX, int centerY, float angle, int frameX, int frameY, BYTE alpha);

	//���̵��ξƿ�
	void FadeInit(int time, FADEKIND fadeKind);	
	void FadeStart();
	void FadeUpdate();
	void FadeRender(HDC hdc);
	bool& getFadeIsStart() { return _fadeInfo.isStart; }

	//�۾� ��ܼ� ���.
	void textOut(HDC hdc, int x, int y, const char* text, COLORREF color = RGB(255, 0, 0));

	//ī�޶��� : �ǹ������̱�, �ǹ��ٲٱ�, ȭ�鶳��
	void movePivot(float x, float y);
	void ChangePivot(float x, float y, float speed);
	void setShake(float power, int time, int cool);

	//�ǹ��ݿ��� ��ǥ&���콺������ ���
	int getRelativeX(float x);
	int getRelativeY(float y);
	POINT getRelativePoint(POINT pt);
	POINT getRelativeMouse();

	//getter
	float getPivotX() { return _pivotX; }
	float getPivotY() { return _pivotY; }
	float getDistanceX() { return _distanceX; }
	float getDistanceY() { return _distanceY; }
	bool getIsShake() { return _isShake; }
	RECT getRect() { return _cameraRect; }
	RECT getRelativeRect(RECT rc);

	//ī�޶���� getter/setter
	void setCMState(CAMERASTATE state) { _state = state; }
	CAMERASTATE getCMState() { return _state; }
};

