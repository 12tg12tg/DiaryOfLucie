#include "framework.h"
#include "miniMap.h"
miniMap::miniMap()

{
	IMAGE->addImage("���۹�", "images/minimap/minimap_cellIcon_start", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("������", "images/minimap/minimap_cell_off", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("����", "images/minimap/minimap_cell_on", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("���ڹ�", "images/minimap/minimap_cellIcon_chest", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("�̺�Ʈ��", "images/minimap/minimap_cellIcon_event", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("������", "images/minimap/minimap_cellIcon_shop", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("������", "images/minimap/minimap_cellIcon_boss", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("������", "images/minimap/minimap_cellIcon_goal", 30, 30, true, RGB(255, 0, 255));
}

miniMap::~miniMap()
{
}

HRESULT miniMap::init()
{

	return S_OK;
}

void miniMap::release()
{
}

void miniMap::update()
{
}

void miniMap::render()
{
	/*if (MAPKIND::START)
	{
		IMAGE->findImage("���۹�");
	}
	if (MAPKIND::NORMAL)
	{
		IMAGE->findImage("������");
	}
	if (MAPKIND::CLEAR)
	{
		IMAGE->findImage("����");
	}
	if (MAPKIND::TRESUREROOM)
	{
		IMAGE->findImage("���ڹ�");
	}
	if (MAPKIND::EVENTMAP)
	{
		IMAGE->findImage("�̺�Ʈ��");
	}
	if (MAPKIND::SHOP)
	{
		IMAGE->findImage("������");
	}
	if (MAPKIND::BOSSROOM)
	{
		IMAGE->findImage("������");
	}
	if (MAPKIND::NEXSTAGE)
	{
		IMAGE->findImage("������");
	}*/
}



