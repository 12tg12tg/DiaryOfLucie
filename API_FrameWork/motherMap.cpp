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
	if (isClear)
	{
		stage++;
	}
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

void motherMap::summonBoss(int x)
{
	
	if (x == 1)
	{
		mm->getBoss_Slime()->addMonster(552,480);
	}
	if (x == 2)
	{
		mm->getBoss_Flime()->addMonster(552, 480);
	}
	if (x == 3)
	{
		mm->getBoss_Mushmam()->addMonster(552, 480);
	}
	if (x == 4)
	{
		mm->getYggdrasil()->addMonster(650, 349);
	}
}
