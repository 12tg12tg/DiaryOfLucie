#pragma once
#include "gameNode.h"
class effect :public gameNode
{
private:
	image* _effectImage;		//이펙트 이미지
	animation* _effectAni;		//이펙트 애니메이션
	
	int _x, _y;					//이펙트 터뜨릴 좌표
	float _elapsedTime;			//이펙트 경과시간(속도)
	bool _isRunning;			//재생중?
	
	int _frameW, _frameH;
	float _z;					//20210812 - Zorder와 함께 추가.

	BYTE _alpha;
public:
	effect();
	~effect();

	HRESULT init(image* effectImage, float z, int frameW, int frameH, int FPS, float elapsedTime, BYTE alpha = 255);
	void release();
	void update();
	void render();
	
	//원하는 좌표에 이펙트 터뜨리기
	void startEffect(int x, int y);
	//이펙트 멈추기
	void stopEffect();
	//이펙트 재생중인지 상태값 가져오기
	bool getIsRunning()const {	return _isRunning;	}

};

