#pragma once
#include "singleton.h"
class animationManager : public Singleton<animationManager>
{
private:

	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterArrAnimation;

	//--------------------------20210808 추가 제작-----------------------------------
	vector<animation*> _vAnimation;
	vector<animation*>::iterator _viAnimation;
	//------------------------------------------------------------------------------
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

	//--------------------------20210808 추가 제작-----------------------------------
	//키값으로 관리시, 여러몬스터가 하나의 키의 애니 재생상태를 공유하게 되는 단점이 있다.
	//이 단점을 극복하기위해 키값없이 애니메이션을 추가하는 함수를 추가함.
	//1. 기존과 동일하게 자동으로 init 해준다.(init, setPlayFrame, setFPS 자동호출)
	//2. 기존과 동일하게 자동으로 업데이트 해준다.(frameUpdate 자동호출)
	//3. 키값으로 관리할수는 없으므로, 관리하기 위한 인스턴스를 반환해주니 꼭 받아야한다.
	//4. 프레임 정보 수정은 changeNoneKeyAnimation함수를 호출하면 된다.
	// 	 이때, 인스턴스를 반드시 전달하도록 한다.
	//이제 동일한 객체의 여러 인스턴스의 애니메이션을 개별적으로 재생할 수 있다.
	animation* addNoneKeyAnimation(char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	animation* addNoneKeyAnimation(char* imageKeyName, int* playarr, int arrLen, int fps, bool loop = false);
	animation* addNoneKeyAnimation(char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	void changeNonKeyAnimation(animation* ani, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	void changeNonKeyAnimation(animation* ani, char* imageKeyName, int* playarr, int arrLen, int fps, bool loop = false);
	void changeNonKeyAnimation(animation* ani, char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);
	//------------------------------------------------------------------------------



	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	//찾기
	animation* findAnimation(string animationKeyName);

	void deleteAll();
};

