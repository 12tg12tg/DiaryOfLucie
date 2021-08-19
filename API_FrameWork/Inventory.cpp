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
				//Ŭ�������� ������ Ÿ�Կ� ���� ��ȣ�ۿ�
				if (INPUT->isOnceKeyDown(VK_LBUTTON) && i < _vectInventory.size())
				{
					for (auto& j : _vectItemData)
					{
						if (j.item_name == _vectInventory[i].item_name)
						{
							if (!_vectInventory[i].isEquip)
							{//�������� ������
								if (PLAYERDATA->PartsEquipCheck(j))
								{//���밡��
									PLAYERDATA->setEquip(j, _vectInventory[i].equipHP, _vectInventory[i].equipMP);
									_vectInventory[i].isEquip = true;
								}
							}
							else if (_vectInventory[i].isEquip)
							{//��������
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
		//���̾ƿ� ���
		ZORDER->UIRender(_inventory_layout, ZUIFIRST, 0, 1033, 195);

		for (int i = 0; i < 15; i++)
		{
			if (PtInRect(&_InvenSlot[i], { m_ptMouse.x,m_ptMouse.y }))
			{
				//����ϱ� ���
				ZORDER->UIAlphaRender(_Bright_button_image, ZUIFIRST, 3, _InvenSlot[i].left, _InvenSlot[i].top, 50);
			}

			//��������� �κ��丮�� ����ϴ� �κ�
			if (i < _vectInventory.size())
			{
				if (_vectInventory[i].isEquip) {
					ZORDER->UIRender(_Equip_Mark_image, ZUIFIRST, 2, _InvenSlot[i].left, _InvenSlot[i].top);
				}
				for (auto& j : _vectItemData)
				{
					if (j.item_name == _vectInventory[i].item_name)
					{
						ZORDER->UIRender(j.item_image, ZUIFIRST, 1, _InvenSlot[i].left + 11, _InvenSlot[i].top + 11);
					}
				}
			}
		}
	}

	//����Ǽ����� ��ºκ�
	int accindex = 0;
	for (auto& i : _vectAccesory)
	{
		ZORDER->UIAlphaRender(i, ZUIFIRST, 0, WINSIZEX / 2 - (i->getWidth() / 2) * (_vectAccesory.size()) + accindex * i->getWidth(), 699, PLAYERDATA->getUIAlpha());
		accindex++;
	}

	//�����������
	showInvenUi();
}

void Inventory::imageInit()
{
	_inventory_layout = IMAGE->addImage("�κ��丮���̾ƿ�", "images/UI/�κ�layout2.bmp", 240 * 1.3, 296 * 1.3, 1);
	_Bright_button_image = IMAGE->addImage("��ư���", "images/UI/��ư���.bmp", 38 * 1.3, 38 * 1.3, 1);
	_Equip_Mark_image = IMAGE->addImage("����ǥ��", "images/UI/����Ʋ1.bmp", 38 * 1.3, 38 * 1.3, 1);
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

void Inventory::showInvenUi()
{
	//�÷��̾����� ���
	if (!_isInvenON) return;
	ZORDER->UITextOut(to_string(PLAYERDATA->getMaxHP()), ZUISECOND, 1165, 424, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getMaxMP()), ZUISECOND, 1280, 424, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getData().presentAtk), ZUISECOND, 1165-7, 424+23, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getData().AtkSpeed), ZUISECOND, 1280, 424 + 23, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getData().presentSkillPower), ZUISECOND, 1165-7, 424 + 23*2, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getData().equipSkillCoolTime), ZUISECOND, 1280, 424 + 23 * 2, RGB(0, 0, 0));
	TCHAR str[128];
	_stprintf_s(str, "%.1f", PLAYERDATA->getData().presentSpeed);
	string speed(str);
	ZORDER->UITextOut(speed, ZUISECOND, 1165-6, 424 + 23*3, RGB(0, 0, 0));
	ZORDER->UITextOut(to_string(PLAYERDATA->getData().Critical), ZUISECOND, 1280, 424 + 23 * 3, RGB(0, 0, 0));
	//�κ������ۼ�, ���
	ZORDER->UITextOut(to_string(_vectInventory.size()), ZUISECOND, 1074, 541, RGB(120, 112, 98));
	ZORDER->UITextOut(to_string(PLAYERDATA->getGold()), ZUISECOND, 1273, 538, RGB(0, 0, 0));
}