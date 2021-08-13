#pragma once
#include "singleton.h"

struct PlayerData 
{
};

class CplayerData: public Singleton<CplayerData>
{
	//공격력 마법력 공속 경험치
	//스킬쿨감수치
	//이속 최대체력 최대마나 
	
	//장비의 마나는 마지막에 사용됨
	//장비마나까지 소비하면 빈마나상태가됨
	//빈마나인 장비를 마나가 잇을때 착용시 장비의 빈마나를 현재마나로 채움
	//마나의소비는 오른쪽에서 왼쪽으로

	//빈하트의 장비를 체력이 잇을때 착용시 체력을 뺏어감
	//소비는 오른쪽에서 왼쪽

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

