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
    _mushman = new Cmushman;
    _mushman_mushroom = new Cmushman_mushroom;
    _fairy = new Cfairy;

    _snaby->addMonster(WINSIZEX / 2, 100);
    _slime->addMonster(WINSIZEX / 2, 300);
    _mushman->addMonster(WINSIZEX - 50, 300);
    _fairy->addMonster(50, 300);




    return S_OK;
}

void monsterManager::release()
{
    _snaby->release();
    _slime->release();
    _mushman->release();
    _mushman_mushroom->release();
    _fairy->release();

    SAFE_DELETE(_snaby);
    SAFE_DELETE(_slime);
    SAFE_DELETE(_mushman);
    SAFE_DELETE(_mushman_mushroom);
    SAFE_DELETE(_fairy);




}

void monsterManager::update()
{
    _snaby->update(_py, _bm);
    _slime->update(_py, _bm);
    _mushman->update(_py, _bm, _mushman_mushroom);
    _mushman_mushroom->update(_py, _bm);
    _fairy->update(_py, _bm);





}

void monsterManager::render()
{
    _snaby->render();
    _slime->render();
    _mushman->render();
    _mushman_mushroom->render();
    _fairy->render();





}
