#include "framework.h"
#include "monsterManager.h"
#include "Cplayer.h"
monsterManager::monsterManager()
{
}

monsterManager::~monsterManager()
{
}

HRESULT monsterManager::init()
{
    _snaby = new Csnaby;
    _snaby->addMonster(WINSIZEX / 2, 100);





    return S_OK;
}

void monsterManager::release()
{
    _snaby->release();
    SAFE_DELETE(_snaby);




}

void monsterManager::update()
{
    _snaby->update(_py);






}

void monsterManager::render()
{
    _snaby->render();





}
