#pragma once
#include "gameNode.h"
class bulletManager;
struct tagSkill
{
	string name;
	string info;
	int burnMp;
	int frameX, frameY;
	int cooldown;
	int duration;
	char key;
};

class Cskill :public gameNode
{
private:
	//�ܺ� �ν��Ͻ�
	bulletManager* _bm;
private:
	//��ü��ų
	vector<tagSkill> vList;

	//������ų
	tagSkill storage[4];
	int currentIndex;

	//������ų ����
	int skillnum = 0;

	//��»簢��
	RECT skillUI[4];
	RECT curRc;
	RECT nameRc;
	RECT infoRc;
	RECT imgRc;

	//������������
	int count;
	bool isClick;
	bool isSkillInfo;
	tagSkill newSkill;

	//�����
	bool _isDebug;
public:
	Cskill();
	~Cskill();

	HRESULT init();
	void release();
	void update();
	void render();

	void initForSkill();
	void addSkill();			//����Ʈ���� �����̱� �� �迭�� �ֱ�.
	void skillFire();			//�߻� �Է��� ������ ���缱������ ��ų�� �߻��ϴ� �Լ�.
	void showNewSkillInfo();	//���� ��ų������ �˾�.
	void selectSKill();			//����Ű�� ��ų����
	void uirender();

	bool getIsSkillInfo() { return isSkillInfo; }
	void setBulletManagerMemoryLink(bulletManager* bm) { _bm = bm; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

