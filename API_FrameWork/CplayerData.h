#pragma once
#include "singleton.h"

struct PlayerData 
{
};

class CplayerData: public Singleton<CplayerData>
{
	//���ݷ� ������ ���� ����ġ
	//��ų�𰨼�ġ
	//�̼� �ִ�ü�� �ִ븶�� 
	
	//����� ������ �������� ����
	//��񸶳����� �Һ��ϸ� �󸶳����°���
	//�󸶳��� ��� ������ ������ ����� ����� �󸶳��� ���縶���� ä��
	//�����ǼҺ�� �����ʿ��� ��������

	//����Ʈ�� ��� ü���� ������ ����� ü���� ���
	//�Һ�� �����ʿ��� ����

private:
	bool _isDebug;

private:

	int _level;
	int _Critical;

	int _lastHP;
	int _defaultHp;
	int _defaultMaxHp;
	int _equipHP;
	int _presentHP;
	int	_MaxequipHP;
	int _MaxHP;


	int _defaultMP;
	int _equipMP;
	int _presentMP;
	int _MaxequipMP;
	int _MaxMP;

	int _defaultAtk;
	int _defaultStamina;

	int _money;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void hitPlayer();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

