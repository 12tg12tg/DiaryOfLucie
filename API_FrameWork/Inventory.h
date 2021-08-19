#pragma once
#include "singleton.h"
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
};

