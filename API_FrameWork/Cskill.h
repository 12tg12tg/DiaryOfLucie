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
	//외부 인스턴스
	bulletManager* _bm;
private:
	//전체스킬
	vector<tagSkill> vList;

	//보유스킬
	tagSkill storage[4];
	int currentIndex;

	//보유스킬 개수
	int skillnum = 0;

	//출력사각형
	RECT skillUI[4];
	RECT curRc;
	RECT nameRc;
	RECT infoRc;
	RECT imgRc;

	//습득시정보출력
	int count;
	bool isClick;
	bool isSkillInfo;
	tagSkill newSkill;

	//디버그
	bool _isDebug;
public:
	Cskill();
	~Cskill();

	HRESULT init();
	void release();
	void update();
	void render();

	void initForSkill();
	void addSkill();			//리스트에서 랜덤뽑기 및 배열에 넣기.
	void skillFire();			//발사 입력을 받으면 현재선택중인 스킬을 발사하는 함수.
	void showNewSkillInfo();	//얻은 스킬정보를 팝업.
	void selectSKill();			//숫자키로 스킬선택
	void uirender();

	bool getIsSkillInfo() { return isSkillInfo; }
	void setBulletManagerMemoryLink(bulletManager* bm) { _bm = bm; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

