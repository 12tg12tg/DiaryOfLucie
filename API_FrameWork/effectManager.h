#pragma once
#include "singleton.h"
class effect;
class effectManager : public Singleton<effectManager>
{
private:
	//이펙트 클래스 담은 벡터
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;

	//이펙트 클래스 담은 벡터를 담은 맵
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

	//모든 이펙트를 관리할 벡터
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;
private:
	//실제 모든 이펙트가 담겨져 있는 녀석
	vTotalEffect m_vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(string effectKey, char* imageName, float z, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer, BYTE alpha = 255);
	void play(string effectKey, int x, int y);
};

