#pragma once
#include "singleton.h"

class progressBar;
/// //////////////////////

struct DATA 
{
	float walkspeed;
	float equipspeed;
	float presentSpeed;

	int Critical;

	int defaultAtk;
	int equipAtk;
	int presentAtk;

	int defaultSkillPower;
	int equipSkillPower;
	int presentSkillPower;

	int AtkSpeed;

	int equipSkillCoolTime;
};

////////////////////////////////

class CplayerData: public Singleton<CplayerData>
{
private:
	bool _isDebug;

	DATA _Data;
//UI
	int _level;

	int _lastMaxHP;
	int _defaultMaxHP;
	int	_equipMaxHP;
	int _presentHP;
	int _MaxHP;


	int _defaultMaxMP;
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
	int _heartstartY;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

private:
	void imageInit();

public:
	void changeHP(int HP);
	int costHP(int cost, bool check=false);
	void changeMP(int MP);
	int costMP(int cost, bool check=false);
	bool useStamina(int costStamina, bool check=false);
	void recoveryStamina(int recovery);
private:
	void recoveryStamina();
	
	void goldRender(HDC hdc);
	void renderUI(HDC hdc);
public:
	bool changeGold(int difference,bool check=false);

	void expUP(int exp);

	DATA& getData() { return _Data; }
	int getPresentHP() { return _presentHP; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

	void setEquip(int equipHP=0,int equipMaxHP=0,int equipMP=0,int equipMaxMP=0,float equipSpeed = 0,int equipAtk = 0,int equipAtkSpeed = 0,int equipCritical = 0,int equipSkillPower = 0,int equipSkillCollTime = 0);
	void takeOffEquip(int& equipHP,int equipMaxHP,int& equipMP,int equipMaxMP,float equipSpeed = 0,int equipAtk = 0,int equipAtkSpeed = 0,int equipCritical = 0,int equipSkillPower = 0,int equipSkillCollTime = 0);
};