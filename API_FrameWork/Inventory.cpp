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
	//_iterItemData= ITEM->copyItemIter();

	return S_OK;
}

void Inventory::release(){}

void Inventory::update()
{

	if (INPUT->isOnceKeyDown('I')) {
		_isInvenON = !_isInvenON;
	}

	if (INPUT->isOnceKeyDown('K')) {
		int i=RND->getFromInTo(0, _vectItemData.size()-1);
		InventoryDataPushBack(_vectItemData[i].item_name, _vectItemData[i].equipHP, _vectItemData[i].equipMP);
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
				ZORDER->UIAlphaRender(_Bright_button_image, ZUIFIRST, 2, _InvenSlot[i].left, _InvenSlot[i].top, 50);

				if (INPUT->isOnceKeyDown(VK_LBUTTON)&& i<_vectInventory.size())
				{
					for (auto& j : _vectItemData)
					{
						if (j.item_name == _vectInventory[i].item_name) {
							switch (j.itemType) {
								case equip://������ ����
									break;
								case weapon://�������� ����
									break;
								case usefule://��� ���� ��� �̸��� ����
									break;
								case accesory://�׳� �ɷ�ġ ���
									break;
							}
						}
					}
				}
			}
			if (i < _vectInventory.size()) {
				for (auto& j : _vectItemData)
				{
					if (j.item_name == _vectInventory[i].item_name) {
						ZORDER->UIRender(j.item_image, ZUIFIRST, 1, _InvenSlot[i].left, _InvenSlot[i].top);
					}
				}
			}
		}
	}
}

void Inventory::imageInit()
{
	_inventory_layout=IMAGE->addImage("�κ��丮���̾ƿ�", "images/UI/�κ�layout2.bmp", 240 * 1.3, 296 * 1.3, 1);
	_Bright_button_image=IMAGE->addImage("��ư���", "images/UI/��ư���.bmp", 38 * 1.3, 38 * 1.3, 1);
}


void Inventory::InventoryDataPushBack(string item_name, int equipHP, int equipMP)
{
	InventoryData temp = { item_name,0,equipHP,equipMP };
	_vectInventory.push_back(temp);
}

void Inventory::InventoryItemRender()
{
}


void Inventory::itemErase()
{
}
