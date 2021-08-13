#pragma once
#include "singleton.h"

struct PlayerData {

};

class CplayerData: public Singleton<CplayerData>
{
	//�÷��̾ �ʿ��� ��ġ
	//�⺻ü�� �⺻���� �� ���׹̳�
	//���� ũȮ ���ݷ� ������ ���� ����ġ
	//��ų ��Ÿ�Ӱ��� ��ġ
	//�̼� �ִ�ü�� �ִ븶�� 
private:
	int _MaxhealthPoint;
	int _MaxmanaPoint;

	int _defaultHp;
	int _defaultAtk;
	int _defaultSpd;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};
