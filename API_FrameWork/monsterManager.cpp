#include "framework.h"
#include "monsterManager.h"
#include "Cplayer.h"
#include "bulletManager.h"
monsterManager::monsterManager()
{
}

monsterManager::~monsterManager()
{
}

HRESULT monsterManager::init()
{
    _snaby = new Csnaby;
    _slime = new Cslime;

    _snaby->addMonster(WINSIZEX / 2, 100);
    _slime->addMonster(WINSIZEX / 2, 300);





    return S_OK;
}

void monsterManager::release()
{
    _snaby->release();
    _slime->release();

    SAFE_DELETE(_snaby);
    SAFE_DELETE(_slime);




}

void monsterManager::update()
{
    _snaby->update(_py, _bm);
    _slime->update(_py, _bm);





}

void monsterManager::render()
{
    _snaby->render();
    _slime->render();





}
