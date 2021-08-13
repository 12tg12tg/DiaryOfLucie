#include "framework.h"
#include "miniMap.h"
miniMap::miniMap()

{
	IMAGE->addImage("시작방", "images/minimap/minimap_cellIcon_start", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("전투방", "images/minimap/minimap_cell_off", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("깬방", "images/minimap/minimap_cell_on", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("상자방", "images/minimap/minimap_cellIcon_chest", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("이벤트방", "images/minimap/minimap_cellIcon_event", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("상점방", "images/minimap/minimap_cellIcon_shop", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("보스방", "images/minimap/minimap_cellIcon_boss", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("다음층", "images/minimap/minimap_cellIcon_goal", 30, 30, true, RGB(255, 0, 255));
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
		IMAGE->findImage("시작방");
	}
	if (MAPKIND::NORMAL)
	{
		IMAGE->findImage("전투방");
	}
	if (MAPKIND::CLEAR)
	{
		IMAGE->findImage("깬방");
	}
	if (MAPKIND::TRESUREROOM)
	{
		IMAGE->findImage("상자방");
	}
	if (MAPKIND::EVENTMAP)
	{
		IMAGE->findImage("이벤트방");
	}
	if (MAPKIND::SHOP)
	{
		IMAGE->findImage("상점방");
	}
	if (MAPKIND::BOSSROOM)
	{
		IMAGE->findImage("보스방");
	}
	if (MAPKIND::NEXSTAGE)
	{
		IMAGE->findImage("다음층");
	}*/
}



