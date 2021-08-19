#include "framework.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_isInvenON = false;
	_isDebug = false;
	this->imageInit();
	for (int i = 0; i < 15; i++)
	{
		_InvenSlot[i] = RectMake(1067+(i%5)* (_Bright_button_image->getWidth()+2), 256+(i/5)*( _Bright_button_image->getHeight()+5), _Bright_button_image->getWidth(), _Bright_button_image->getHeight());
	}
	return S_OK;
}

void Inventory::release(){}

void Inventory::update()
{

	if (INPUT->isOnceKeyDown('I')) {
		_isInvenON = !_isInvenON;
	}
}

void Inventory::render(HDC hdc)
{
	if (_isInvenON) {
		ZORDER->UIRender(_inventory_layout, ZUIFIRST, 0, 1033, 195);
		for (int i = 0; i < 15; i++)
		{
			if (PtInRect(&_InvenSlot[i], { m_ptMouse.x,m_ptMouse.y }))
			{
				ZORDER->UIAlphaRender(_Bright_button_image, ZUIFIRST, 2, _InvenSlot[i].left, _InvenSlot[i].top, 50);
			}
		}
	}
}

void Inventory::imageInit()
{
	_inventory_layout=IMAGE->addImage("인벤토리레이아웃", "images/UI/인벤layout2.bmp", 240 * 1.3, 296 * 1.3, 1);
	_Bright_button_image=IMAGE->addImage("버튼밝게", "images/UI/버튼밝게.bmp", 38 * 1.3, 38 * 1.3, 1);
}
