#pragma once
#include "singleton.h"
class animationManager : public Singleton<animationManager>
{
private:

	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterArrAnimation;

	arrAnimation _animation;
public:
	animationManager();
	~animationManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//처음부터 끝까지
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//배열에 담아서
	void addAnimation(string animationKeyName, char* imageKeyName, int* playarr, int arrLen, int fps, bool loop = false);
	//시작 끝 인덱스
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	//찾기
	animation* findAnimation(string animationKeyName);

	void deleteAll();
};

