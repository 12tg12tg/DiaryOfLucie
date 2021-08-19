#pragma once
#include "singleton.h"

struct ITEMDATA;


class Inventory : public Singleton<Inventory>
{
	bool _isDebug;
	bool _isInvenON;
public:
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

private:
	void imageInit();
	image* _inventory_layout;
	image* _Bright_button_image;
	RECT _InvenSlot[15];

	vector<ITEMDATA> _vectItemData;
	vector<ITEMDATA>::iterator _iterItemData;

	vector<ITEMDATA> _vectInventory;
	vector<ITEMDATA>::iterator _iterInventory;

public:
	void itemPushBack();
	void itemErase();
};

