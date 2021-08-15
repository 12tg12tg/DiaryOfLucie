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
    _flime = new Cflime;
    _bossSlime = new Cboss_slime;
    _semiBossSlime = new Csemiboss_slime;
    _bossflime = new Cboss_flime;
    _bossMushmam = new Cboss_mushmam;
    _mushmam_mushroom_G = new Cmushmam_mushroom_G;
    _mushmam_mushroom_P = new Cmushmam_mushroom_P;
    _mushmam_mushroom_B = new Cmushmam_mushroom_B;
    _yggdrasil = new Cyggdrasil;
    _yggdrasil_bomb = new Cyggdrasil_bomb;
    /*
    _snaby->addMonster(WINSIZEX / 2, 100);
    _slime->addMonster(WINSIZEX / 2, 300);
    _mushman_mushroom->addMonster(200, 300);
    _mushman->addMonster(WINSIZEX - 50, 300);
    _fairy->addMonster(50, 300);
    _flime->addMonster(WINSIZEX / 2, WINSIZEY / 2);
    _bossSlime->addMonster(WINSIZEX/2, WINSIZEY/2);
    _semiBossSlime->addMonster(WINSIZEX/2, WINSIZEY/2);
    _bossflime->addMonster(WINSIZEX/2, WINSIZEY/2);
    _bossMushmam->addMonster(WINSIZEX/2, WINSIZEY/2);
    _mushmam_mushroom_G->addMonster(100, 200);
    _mushmam_mushroom_P->addMonster(100, 300);
    _mushmam_mushroom_B->addMonster(100, 400);
    _yggdrasil_bomb->addMonster(WINSIZEX / 2, 100);
    _yggdrasil->addMonster(WINSIZEX / 2, 100);*/

    _ft = new fountain;
    _ft->add(WINSIZEX /2, WINSIZEY/2);
    _mr = new moru;
    _mr->add(WINSIZEX / 2 + 100, WINSIZEY / 2);

    return S_OK;
}

void monsterManager::release()
{
    _snaby->release();
    _slime->release();
    _mushman->release();
    _mushman_mushroom->release();
    _fairy->release();
    _flime->release();
    _bossSlime->release();
    _semiBossSlime->release();
    _bossflime->release();
    _bossMushmam->release();
    _mushmam_mushroom_G->release();
    _mushmam_mushroom_P->release();
    _mushmam_mushroom_B->release();
    _yggdrasil->release();
    _yggdrasil_bomb->release();


    SAFE_DELETE(_snaby);
    SAFE_DELETE(_slime);
    SAFE_DELETE(_mushman);
    SAFE_DELETE(_mushman_mushroom);
    SAFE_DELETE(_fairy);
    SAFE_DELETE(_flime);
    SAFE_DELETE(_bossSlime);
    SAFE_DELETE(_semiBossSlime);
    SAFE_DELETE(_bossflime);
    SAFE_DELETE(_bossMushmam);
    SAFE_DELETE(_mushmam_mushroom_G);
    SAFE_DELETE(_mushmam_mushroom_P);
    SAFE_DELETE(_mushmam_mushroom_B);
    SAFE_DELETE(_yggdrasil);
    SAFE_DELETE(_yggdrasil_bomb);


    SAFE_DELETE(_ft);
    SAFE_DELETE(_mr);

}

void monsterManager::update()
{
    _snaby->update(_py, _bm);
    _slime->update(_py, _bm);
    _mushman->update(_py, _bm, _mushman_mushroom);
    _mushman_mushroom->update(_py, _bm);
    _fairy->update(_py, _bm);
    _flime->update(_py, _bm);
    _bossSlime->update(_py, _bm, _semiBossSlime);
    _semiBossSlime->update(_py, _bm, _slime);
    _bossflime->update(_py, _bm);
    _bossMushmam->update(_py, _bm, _mushmam_mushroom_G, _mushmam_mushroom_P, _mushmam_mushroom_B, _mushman_mushroom);
    _mushmam_mushroom_G->update(_py, _bm);
    _mushmam_mushroom_P->update(_py, _bm);
    _mushmam_mushroom_B->update(_py, _bm);
    _yggdrasil->update(_py, _bm, _yggdrasil_bomb);
    _yggdrasil_bomb->update(_py, _bm);


    //static int count = 0;
    //count++;
    if (INPUT->isOnceKeyDown('N')) {
        _mushmam_mushroom_G->addMonster(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y);
    //    vector<tagMonster>& v = _yggdrasil->getVMonster();
    //    auto iter = v.begin();
    //    for (iter; iter != v.end(); ++iter)
    //    {
    //        _yggdrasil->knockback(iter, m_ptMouse.x, m_ptMouse.y, 30, 10, true);
    //    }
    //    //vector<tagMonster>& v2 = _semiBossSlime->getVMonster();
    //    //auto iter2 = v2.begin();
    //    //for (iter2; iter2 != v2.end(); ++iter2)
    //    //{
    //    //    _semiBossSlime->knockback(iter2, m_ptMouse.x, m_ptMouse.y, 10, 10, true);
    //    //}
    //    //vector<tagMonster>& v3 = _slime->getVMonster();
    //    //auto iter3 = v3.begin();
    //    //for (iter3; iter3 != v3.end(); ++iter3)
    //    //{
    //    //    _slime->knockback(iter3, m_ptMouse.x, m_ptMouse.y, 1, 10, true);
    //    //}
    }

    _ft->update(_bm);
    _mr->update(_bm);
}

void monsterManager::render()
{
    _snaby->render();
    _slime->render();
    _mushman->render();
    _fairy->render();
    _flime->render();
    _bossSlime->render();
    _semiBossSlime->render();
    _bossflime->render();
    _bossMushmam->render();
    _mushmam_mushroom_G->render();
    _mushmam_mushroom_P->render();
    _mushmam_mushroom_B->render();
    _mushman_mushroom->render();
    _yggdrasil->render();
    _yggdrasil_bomb->render();




    _ft->render();
    _mr->render();
}
