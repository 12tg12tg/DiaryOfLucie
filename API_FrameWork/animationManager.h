#pragma once
#include "singleton.h"
class animationManager : public Singleton<animationManager>
{
private:

	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterArrAnimation;

	//--------------------------20210808 �߰� ����-----------------------------------
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

	//ó������ ������
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//�迭�� ��Ƽ�
	void addAnimation(string animationKeyName, char* imageKeyName, int* playarr, int arrLen, int fps, bool loop = false);
	//���� �� �ε���
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	//--------------------------20210808 �߰� ����-----------------------------------
	//Ű������ ������, �������Ͱ� �ϳ��� Ű�� �ִ� ������¸� �����ϰ� �Ǵ� ������ �ִ�.
	//�� ������ �غ��ϱ����� Ű������ �ִϸ��̼��� �߰��ϴ� �Լ��� �߰���.
	//1. ������ �����ϰ� �ڵ����� init ���ش�.(init, setPlayFrame, setFPS �ڵ�ȣ��)
	//2. ������ �����ϰ� �ڵ����� ������Ʈ ���ش�.(frameUpdate �ڵ�ȣ��)
	//3. Ű������ �����Ҽ��� �����Ƿ�, �����ϱ� ���� �ν��Ͻ��� ��ȯ���ִ� �� �޾ƾ��Ѵ�.
	//4. ������ ���� ������ changeNoneKeyAnimation�Լ��� ȣ���ϸ� �ȴ�.
	// 	 �̶�, �ν��Ͻ��� �ݵ�� �����ϵ��� �Ѵ�.
	//���� ������ ��ü�� ���� �ν��Ͻ��� �ִϸ��̼��� ���������� ����� �� �ִ�.
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

	//ã��
	animation* findAnimation(string animationKeyName);

	void deleteAll();
};

