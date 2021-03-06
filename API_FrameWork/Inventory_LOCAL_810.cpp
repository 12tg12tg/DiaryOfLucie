#include "framework.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_isInvenON = false;
	_isDebug = false;

	this->imageInit();

	for (int i = 0; i < 15; i++)
	{
		_InvenSlot[i] = RectMake(1067 + (i % 5) * (_Bright_button_image->getWidth() + 2),
			256 + (i / 5) * (_Bright_button_image->getHeight() + 5),
			_Bright_button_image->getWidth(), _Bright_button_image->getHeight());
	}

	_vectItemData = ITEM->copyItemVect();

	return S_OK;
}

void Inventory::release() {}

void Inventory::update()
{

	if (INPUT->isOnceKeyDown('I'))
	{
		_isInvenON = !_isInvenON;
	}

	if (INPUT->isOnceKeyDown('K'))
	{
		randnum = RND->getFromInTo(0, _vectItemData.size() - 1);
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
								_vectInventory[i].isEquip = false;
							}
						}
					}
				}
				else if (INPUT->isOnceKeyDown(VK_RBUTTON) && i < _vectInventory.size())
				{
					if (!_vectInventory[i].isEquip)
					{
						_iterInventory = _vectInventory.begin() + i;
						_vectInventory.erase(_iterInventory);
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
				ZORDER->UIAlphaRender(_Bright_button_image, ZUIFIRST, 3, _InvenSlot[i].left, _InvenSlot[i].top, 50);
			}

			//현재아이템 인벤토리에 출력하는 부분
			if (i < _vectInventory.size())
			{
				if (_vectInventory[i].isEquip) {
					ZORDER->UIRender(_Equip_Mark_image, ZUIFIRST, 2, _InvenSlot[i].left, _InvenSlot[i].top);
				}
				for (auto& j : _vectItemData)
				{
					if (j.item_name == _vectInventory[i].item_name)
					{
						InventoryInfoRender(j,i);
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
		ZORDER->UIAlphaRender(i, ZUIFIRST, 0, WINSIZEX / 2 - (i->getWidth() / 2) * (_vectAccesory.size()) + accindex * i->getWidth(), 699, PLAYERDATA->getUIAlpha());
		accindex++;
	}

	
}

void Inventory::imageInit()
{
	IMAGE->addImage("인벤토리정보상자", "images/object/inventoryinfobox.bmp", WINSIZEX * 3 / 5, 150, false);
	_inventory_layout = IMAGE->addImage("인벤토리레이아웃", "images/UI/인벤layout2.bmp", 240 * 1.3, 296 * 1.3, 1);
	_Bright_button_image = IMAGE->addImage("버튼밝게", "images/UI/버튼밝게.bmp", 38 * 1.3, 38 * 1.3, 1);
	_Equip_Mark_image = IMAGE->addImage("장착표시", "images/UI/장착틀1.bmp", 38 * 1.3, 38 * 1.3, 1);
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


bool Inventory::inventoryEmptyCheck()
{
	if (_vectInventory.size() < 15) return true;
	else return false;
}

void Inventory::InventoryInfoRender(ITEMDATA itemdata, int index)
{
	//장비 설명
	if (PtInRect(&_InvenSlot[index], m_ptMouse))
	{
	infoRc = RectMake(300,1000,
		IMAGE->findImage("인벤토리정보상자")->getWidth(),
		IMAGE->findImage("인벤토리정보상자")->getHeight());
		RECT txtRc = RectMake(infoRc.left + 15, infoRc.top + 15, RecWidth(infoRc) - 30, RecHeight(infoRc) - 30);
		string str = itemdata.item_name; /*아이템 이름*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		//txtRc = RectMake(infoRc.left + 15, infoRc.top + 15 + 40, RecWidth(infoRc) - 30, RecHeight(infoRc) - 30 - 40);
		//str = itemdata.item_image; /*아이템 이미지*/
		//ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
		//	CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		//		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
		//	RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		ZORDER->UIRender(itemdata.item_image, ZUITHIRD, 3, _InvenSlot[index].left, _InvenSlot[index].top);

		txtRc = RectMake(infoRc.left + 15, infoRc.top + 15 + 40, RecWidth(infoRc) - 30, RecHeight(infoRc) - 30 - 120);
		str = itemdata.item_stat_Info; /*아이템 설명*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		txtRc = RectMake(infoRc.left + 15, infoRc.top + 15 + 40, RecWidth(infoRc) - 30, RecHeight(infoRc) - 30 - 160);
		str = itemdata.item_info; /*아이템 설명*/
		ZORDER->UIDrawText(str, ZUITHIRD, txtRc,
			CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY견고딕")),
			RGB(255, 255, 255), DT_LEFT | DT_VCENTER);

		ZORDER->UIAlphaRender(IMAGE->findImage("인벤토리정보상자"), ZUITHIRD, 0, m_ptMouse.x -500, m_ptMouse.y - 100, 150);
	}
}
