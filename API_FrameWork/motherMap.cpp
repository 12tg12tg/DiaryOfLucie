#include "framework.h"
#include "motherMap.h"

motherMap::motherMap()
{
}

motherMap::~motherMap()
{
}

HRESULT motherMap::init()
{
	
	mm->init();
	return S_OK;
}

void motherMap::release()
{
}

void motherMap::update()
{
}

void motherMap::render()
{
}

void motherMap::summonMon(int x)
{
	for (int i = 0; i < monNum; i++)
	{
		chooseMon = RND->getFromInTo(0, x);

		if (chooseMon == MONKIND::SNABY)
		{
			mm->getSnaby()->addMonster(monpos[i].x, monpos[i].y);
		}
		if (chooseMon == MONKIND::SLIME)
		{
			mm->getSlime()->addMonster(monpos[i].x, monpos[i].y);
		}
		if (chooseMon == MONKIND::MUSHMAN)
		{
			mm->getMushman()->addMonster(monpos[i].x, monpos[i].y);
		}
		if (chooseMon == MONKIND::FAIRY)
		{
			mm->getFairy()->addMonster(monpos[i].x, monpos[i].y);
		}
		if (chooseMon == MONKIND::FLIME)
		{
			mm->getFlime()->addMonster(monpos[i].x, monpos[i].y);
		}
	}
}
