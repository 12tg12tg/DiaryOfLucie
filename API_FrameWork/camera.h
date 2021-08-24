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

	//���̵��ξƿ�
	void FadeInit(int time, FADEKIND fadeKind);	
	void FadeStart();
	void FadeUpdate();
	void FadeRender(HDC hdc);
	bool& getFadeIsStart() { return _fadeInfo.isStart; }

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

