#pragma once
#include "singleton.h"
enum ITEMTYPE {
	equip,
	weapon,
	usefule
};
struct ITEMDATA 
{
	ITEMTYPE itemType;
	int equipHP = 0;
	int equipMaxHP =0;
	int equipMP = 0; 
	int equipMaxMP = 0;
	float equipSpeed = 0; 
	int equipAtk = 0;
	int equipAtkSpeed = 0;
	int equipCritical = 0; 
	int equipSkillPower = 0; 
	int equipSkillCollTime = 0;
};
class Item
{
};

