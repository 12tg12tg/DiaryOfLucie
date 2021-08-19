#pragma once
#include "singleton.h"
enum ITEMTYPE {
	equip,
	weapon,
	usefule,//¹Ì±¸Çö
	accesory
};
enum WEAPON_TYPE
{
	bow,
	staff,
	sword
};

enum EQUIPTYPE 
{
	hat,
	armor,
	boot
};
struct ITEMDATA 
{
	image* item_image;
	RECT item_colbox;
	string item_name;
	string item_info;
	string item_shopInfo;
	WEAPON_TYPE weapon_type;
	EQUIPTYPE equip_type;
	int price = 0;
	int x, y;
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
class Item:public Singleton<Item>
{
private:

	vector<ITEMDATA> _vItem;
	vector<ITEMDATA>::iterator _viItem;
private:
	bool _isDebug;
public:
	Item();
	~Item();

	HRESULT init();
	void release();
	void update();
	void render();
	void removeitem(int arrNum);

	vector<ITEMDATA> getV_Item() { return _vItem; }
	vector<ITEMDATA>::iterator getVI_Item() { return _viItem; }
	vector<ITEMDATA> copyItemVect() { return _vItem; }
	vector<ITEMDATA>::iterator copyItemIter() { return _viItem; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

