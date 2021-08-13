#pragma once
#include "singleton.h"

struct PlayerData {

};

class CplayerData: public Singleton<CplayerData>
{
	//플레이어가 필요한 수치
	//기본체력 기본마나 돈 스테미나
	//레벨 크확 공격력 마법력 공속 경험치
	//스킬 쿨타임감소 수치
	//이속 최대체력 최대마나 
private:
	bool _isDebug;

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


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

