#pragma once
#include "singleton.h"
class effect;
class effectManager : public Singleton<effectManager>
{
private:
	//����Ʈ Ŭ���� ���� ����
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;

	//����Ʈ Ŭ���� ���� ���͸� ���� ��
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

	//��� ����Ʈ�� ������ ����
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;
private:
	//���� ��� ����Ʈ�� ����� �ִ� �༮
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

