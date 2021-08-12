#include "framework.h"
#include "mapManager.h"

mapManager::mapManager(int x, int y, int floor)
{
	_x = x;
	_y = y;

	/*switch (floor)
	{
	case 1:

	}*/
}

HRESULT mapManager::init()
{

	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
}

void mapManager::render()
{
}

void mapManager::setStartMap()
{
}

void mapManager::setRandomMap(mapManager** map)
{
}

void mapManager::connectMap(mapManager** map)
{
}

void mapManager::bossMapDfs()
{
}

void mapManager::setBossMap(mapManager** map, int percent)
{
}

void mapManager::dgDoorRender()
{
}

void mapManager::dgDoorUpdate()
{
}

void mapManager::dgDoorOpen()
{
}

void mapManager::dgDoorClose()
{
}

void mapManager::enemyUpdate()
{
}

void mapManager::popEnemy(int arr)
{
}

void mapManager::checkColiMoveBen()
{
}

void mapManager::checkColiHole()
{
}

void mapManager::checkCollisionSpa()
{
}

void mapManager::checkColiArrow()
{
}

mapManager* mapManager::findMap(POINT pos)
{
	return nullptr;
}

bool mapManager::isFindMap(POINT pos)
{
	return false;
}

mapManager* mapManager::moveDungeon(RECT rc)
{
	return nullptr;
}

bool mapManager::isMoveBen(RECT rc)
{
	return false;
}

RECT mapManager::getMoveBenTile(RECT rc)
{
	return RECT();
}

RECT mapManager::getHoleTile(RECT rc)
{
	return RECT();
}
