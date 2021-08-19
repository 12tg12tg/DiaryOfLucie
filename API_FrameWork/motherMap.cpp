#include "framework.h"
#include "motherMap.h"

motherMap::motherMap()
{
	_gold_coin = new goldCoin;
	_silver_coin = new silverCoin;
	_bronze_coin = new bronzeCoin;
}

motherMap::~motherMap()
{
}

HRESULT motherMap::init()
{
	
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
		mm->getYggdrasil()->addMonster(650, 349 + 117);
	}
}

void motherMap::dropCoin(int x , int y)
{
	
	int rand = RND->getInt(6);
	if (rand == 0)
	{
	_gold_coin->drop(x,y);
	}
	else if (1 <= rand && rand <= 2)
	{
	_silver_coin->drop(x,y);
	}
	else
	{
	_bronze_coin->drop(x,y);
	}
}
