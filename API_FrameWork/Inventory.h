#pragma once
#include "singleton.h"

struct ITEMDATA;
enum ITEMTYPE;

struct InventoryData {
	string item_name;
	bool isEquip;
	int equipHP;
	int equipMP;
};


class Inventory : public Singleton<Inventory>
{
private:
	bool _isDebug;
	bool _isInvenON;

public:
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

private:
	int randnum;

	void imageInit();
	image* _inventory_layout;
	image* _Bright_button_image;

	RECT _InvenSlot[15];
	RECT infoRc;
	bool isclicked = true;
	vector<ITEMDATA> _vectItemData;

	vector<InventoryData> _vectInventory;
	vector<InventoryData>::iterator _iterInventory;
	vector<image*> _vectAccesory;
public:
	void InventoryDataPushBack(string item_name,int equipHP = 0,int equipMP = 0);
	
	void itemErase();

	bool inventoryEmptyCheck();

	void InventoryInfoRender(int array);
};