#include "framework.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}

monsterManager::~monsterManager()
{
}

HRESULT monsterManager::init()
{
    _snaby = new Csnaby;






    return S_OK;
}

void monsterManager::release()
{
    _snaby->release();
    SAFE_DELETE(_snaby);




}

void monsterManager::update()
{
    _snaby->update();






}

void monsterManager::render()
{
    _snaby->render();





}
