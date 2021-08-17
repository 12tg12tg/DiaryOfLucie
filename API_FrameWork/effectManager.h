#pragma once
#include "singleton.h"
class effect;

struct tagParticle
{
	string imgKey;
	float angle;
	float z;
	float x, y;
	int frameX, frameY;
	bool isAlpha;
	BYTE alpha;
	int count;
	float speed;
	bool isPlay;
};


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
	//��ƼŬ����
	vector<tagParticle> _vParticle;
public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(string effectKey, char* imageName, float z, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer, BYTE alpha = 255);
	void play(string effectKey, int x, int y);

	HRESULT addParticle(string key, float z, float x, float y, float angle, int count = 20, bool isAlpha = false, BYTE alpha = 0);
};

