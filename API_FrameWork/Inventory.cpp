#include "framework.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_isInvenON = false;
	_isDebug = false;

	this->imageInit();
	
	for (int i = 0; i < 15; i++)
	{
		_InvenSlot[i] = RectMake(1067+(i%5)* (_Bright_button_image->getWidth()+2), 
			256+(i/5)*( _Bright_button_image->getHeight()+5),
			_Bright_button_image->getWidth(), _Bright_button_image->getHeight());
	}

	_vectItemData= ITEM->copyItemVect();

	return S_OK;
}

void Inventory::release(){}

void Inventory::update()
{

	if (INPUT->isOnceKeyDown('I')) 
	{
		_isInvenON = !_isInvenON;
	}

	if (INPUT->isOnceKeyDown('K')) 
	{
		randnum=RND->getFromInTo(0, _vectItemData.size()-1);
		InventoryDataPushBack(_vectItemData[randnum].item_name, _vectItemData[randnum].equipHP, _vectItemData[randnum].equipMP);
	}

	if (_isInvenON)
	{
		for (int i = 0; i < 15; i++)
		{
			if (PtInRect(&_InvenSlot[i], { m_ptMouse.x,m_ptMouse.y }))
			{
				//클릭햇을때 아이템 타입에 따라 상호작용
				if (INPUT->isOnceKeyDown(VK_LBUTTON) && i < _vectInventory.size())
				{
					for (auto& j : _vectItemData)
					{
						if (j.item_name == _vectInventory[i].item_name)
						{
							if (!_vectInventory[i].isEquip)
							{//미착용중 아이템
								if (PLAYERDATA->PartsEquipCheck(j))
								{//착용가능
									PLAYERDATA->setEquip(j, _vectInventory[i].equipHP, _vectInventory[i].equipMP);
									_vectInventory[i].isEquip = true;
								}
							}
							else if (_vectInventory[i].isEquip)
							{//착용해제
								PLAYERDATA->takeOffEquip(j, _vectInventory[i].equipHP, _vectInventory[i].equipMP);
							}
						}
					}
				}
			}
		}
	}
}

void Inventory::render(HDC hdc)
{
	if (_isInvenON) 
	{
		//레이아웃 출력
		ZORDER->UIRender(_inventory_layout, ZUIFIRST, 0, 1033, 195);
		
		for (int i = 0; i < 15; i++)
		{
			if (PtInRect(&_InvenSlot[i], { m_ptMouse.x,m_ptMouse.y }))
			{
				//밝게하기 출력
				ZORDER->UIAlphaRender(_Bright_button_image, ZUIFIRST, 2, _InvenSlot[i].left, _InvenSlot[i].top, 50);

			}

			//현재아이템 인벤토리에 출력하는 부분
			if (i < _vectInventory.size()) 
			{
				for (auto& j : _vectItemData)
				{
					if (j.item_name == _vectInventory[i].item_name) 
					{
						ZORDER->UIRender(j.item_image, ZUIFIRST, 1, _InvenSlot[i].left+11, _InvenSlot[i].top+11);
					}
				}
			}
		}
	}

	//현재악세서리 출력부분
	int accindex = 0;
	for (auto& i : _vectAccesory)
	{
		ZORDER->UIAlphaRender(i, ZUIFIRST, 0, WINSIZEX / 2 - (i->getWidth() / 2) * (_vectAccesory.size()) + accindex * i->getWidth() , 699, PLAYERDATA->getUIAlpha());
		accindex++;
	}
}

void Inventory::imageInit()
{
	_inventory_layout=IMAGE->addImage("인벤토리레이아웃", "images/UI/인벤layout2.bmp", 240 * 1.3, 296 * 1.3, 1);
	_Bright_button_image=IMAGE->addImage("버튼밝게", "images/UI/버튼밝게.bmp", 38 * 1.3, 38 * 1.3, 1);
}

void Inventory::InventoryDataPushBack(string item_name, int equipHP, int equipMP)
{
	for (auto& i : _vectItemData)
	{
		if (i.item_name == item_name) {
			if (i.itemType != ITEMTYPE::accesory) {
				InventoryData temp = { item_name,0,equipHP,equipMP };
				_vectInventory.push_back(temp);
			}
			else {
				_vectAccesory.push_back(i.item_image);
				PLAYERDATA->setEquip(_vectItemData[randnum], _vectItemData[randnum].equipHP, _vectItemData[randnum].equipMP);
			}
		}
	}
}

void Inventory::itemErase()
{

}

bool Inventory::inventoryEmptyCheck()
{
	if (_vectInventory.size() < 15) return true;
	else return false;
}