#pragma once
#include "gameNode.h"
class effect :public gameNode
{
private:
	image* _effectImage;		//����Ʈ �̹���
	animation* _effectAni;		//����Ʈ �ִϸ��̼�
	
	int _x, _y;					//����Ʈ �Ͷ߸� ��ǥ
	float _elapsedTime;			//����Ʈ ����ð�(�ӵ�)
	bool _isRunning;			//�����?
	
	int _frameW, _frameH;
	float _z;					//20210812 - Zorder�� �Բ� �߰�.

	BYTE _alpha;
public:
	effect();
	~effect();

	HRESULT init(image* effectImage, float z, int frameW, int frameH, int FPS, float elapsedTime, BYTE alpha = 255);
	void release();
	void update();
	void render();
	
	//���ϴ� ��ǥ�� ����Ʈ �Ͷ߸���
	void startEffect(int x, int y);
	//����Ʈ ���߱�
	void stopEffect();
	//����Ʈ ��������� ���°� ��������
	bool getIsRunning()const {	return _isRunning;	}

};

