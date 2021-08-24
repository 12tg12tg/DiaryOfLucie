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
	//초기화정보
	float _cameraSizeX;
	float _cameraSizeY;
	CAMERASTATE _state;	
	RECT _cameraRect;
	float _pivotX, _pivotY;
	float _maxX, _maxY;
	float _minX, _minY;
	float _distanceX, _distanceY;

	//절대값
	float _absDistanceX, _absDistanceY;

	//피벗변경
	float _changePivotX;
	float _changePivotY;
	float _changeSpeed;

	//피벗좌표갱신
	POINT _moveToPivot;

	//화면떨림.
	POINT _shakePivot;
	POINT _savePivot;
	float _shakePower;
	tagShakeTime _shakeTime;
	bool _isShake;

	//페이드인아웃
	tagFadeInfo _fadeInfo;
public:
	camera();
	~camera();

	//피벗좌표, 전체공간의 최대/최소크기, 거리.
	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);
	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY, float sizeX, float sizeY);
	void update();
	void release();

	//페이드인아웃
	void FadeInit(int time, FADEKIND fadeKind);	
	void FadeStart();
	void FadeUpdate();
	void FadeRender(HDC hdc);
	bool& getFadeIsStart() { return _fadeInfo.isStart; }

	//카메라기능 : 피벗움직이기, 피벗바꾸기, 화면떨림
	void movePivot(float x, float y);
	void ChangePivot(float x, float y, float speed);
	void setShake(float power, int time, int cool);

	//피벗반영한 좌표&마우스포인터 얻기
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

	//카메라상태 getter/setter
	void setCMState(CAMERASTATE state) { _state = state; }
	CAMERASTATE getCMState() { return _state; }
};

