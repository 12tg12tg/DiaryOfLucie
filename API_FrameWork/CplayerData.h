#pragma once
#include "singleton.h"

class progressBar;

class CplayerData: public Singleton<CplayerData>
{
	//공격력 마법력 공속 경험치
	//스킬쿨감수치
	//이속

private:
	bool _isDebug;

private:
	int _Critical;
	int _defaultAtk;

	//UI
	int _level;

	int _lastHP;
	int _lastMaxHP;
	int _defaultHP;
	int _defaultMaxHP;
	int _equipHP;
	int	_equipMaxHP;
	int _presentHP;
	int _MaxHP;


	int _defaultMP;
	int _defaultMaxMP;
	int _equipMP;
	int _equipMaxMP;
	int _presentMP;
	int _MaxMP;

	float _defaultStamina;
	int _recoveryStaminaCoolTimeCount;
	
	int _EXP;

	bool _getSkill;
	
	int _gold;

private:
	int UIalpha;
	progressBar* _EXPBar;
	progressBar* _StaminaBar;

private:
	image* _layout_image;
	image* _gold_G;
	int _heartstartX;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void imageInit();

	void hitPlayer(int damage);
	void healPlayer(int recovery);
	bool useMana(int manaCost, bool Check=false);
	void recoveryMana(int recovery);
	bool useStamina(int costStamina, bool check=false);
	void recoveryStamina();
	void recoveryStamina(int recovery);
	
	void goldRender(HDC hdc);
	bool changeGold(int difference,bool check=false);

	void expUP(int exp);

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	int getPresentHP() { return _presentHP; }
};