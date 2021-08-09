#include "framework.h"
#include "collisionManager.h"
#include"bulletManager.h"
#include"monsterManager.h"

collisionManager::collisionManager()
{
}

collisionManager::~collisionManager()
{
}

HRESULT collisionManager::init()
{
    return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::update()
{
    bulletToplayer();
    bulletTomon();
}

void collisionManager::bulletToplayer()
{
    //cir충돌
    for (int i = 0; i < bm->getCirBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getCirBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getCirBulInstance()->removeBullet(i);
            //damage
        }
    }
    //flwbos1충돌
    for (int i = 0; i < bm->getFlwBos1Bullnstance()->getVBullet3().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos1Bullnstance()->getVBullet3()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //flwbos2충돌
    for (int i = 0; i < bm->getFlwBos2Bullnstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos2Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {  
            //damage
        }
    }
    //flwbos3충돌
    for (int i = 0; i < bm->getFlwBos3Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getFlwBos3Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //long poison충돌
    for (int i = 0; i < bm->getLPsnBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getLPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //niddle 충돌
    for (int i = 0; i < bm->getnidBulInstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getnidBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //poison 충돌
    for (int i = 0; i < bm->getPsnBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //return1 충돌
    for (int i = 0; i < bm->getRtnBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getRtnBulInstance()->getVBullet()[i].iscollison = true;
                //damage
        }
    }
    for (int i = 0; i < bm->getRtnBulInstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getRtnBulInstance()->removeBullet2(i);
            //damage
        }
    }
    //slime boss 1 충돌
    for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getSlmBos1Bullnstance()->getVBullet()[i].iscollison = true;
            //damage
        }
    }
    for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getSlmBos1Bullnstance()->removeBullet2(i);
            //damage
        }
    }
    //tree boss 1 충돌
    for (int i = 0; i < bm->getTreBos1Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //tree boss 2 충돌
    for (int i = 0; i < bm->getTreBos2Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos2Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTreBos2Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //tree boss 3 충돌
    for (int i = 0; i < bm->getTreBos3Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTreBos3Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //triple 충돌
    for (int i = 0; i < bm->getTriBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTriBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTriBulInstance()->removeBullet(i);
            //damage
        }
    }
    //wide 충돌
    for (int i = 0; i < bm->getWidBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getWidBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getWidBulInstance()->removeBullet(i);
            //damage
        }
    }
    for (int i = 0; i < bm->getHomBulInstance()->getVBullet().size(); i++)
    {
       
        
    }


}

void collisionManager::bulletTomon()
{                                                      
    checkMonsterRectColl(mm->getSnaby());               //★몬스터 생성시 여기에 추가. //오브젝트도 같이 추가하면 좋을듯.
    checkMonsterRectColl(mm->getSlime());
    checkMonsterRectColl(mm->getMushman());
    checkMonsterRectColl(mm->getMushman_Mushroom());
    checkMonsterRectColl(mm->getFairy());
    checkMonsterRectColl(mm->getFlime());
    checkMonsterRectColl(mm->getBoss_Slime());
    checkMonsterRectColl(mm->getSemiBoss_Slime());
    checkMonsterRectColl(mm->getBoss_Flime());
    checkMonsterRectColl(mm->getBoss_Mushmam());
    checkMonsterRectColl(mm->getBoss_Mushroom_G());
    checkMonsterRectColl(mm->getBoss_Mushroom_P());
    checkMonsterRectColl(mm->getBoss_Mushroom_B());
    checkMonsterRectColl(mm->getYggdrasil_Bomb());
    checkMonsterRectColl(mm->getYggdrasil());

}

void collisionManager::playerTomon()
{
}

void collisionManager::checkMonsterRectColl(monster* monster)            //★플레이어의 공격수단 생성시 여기에 꼭 추가.
{
    vector<tagMonster>& vMonster = monster->getVMonster();
    vector<tagMonster>::iterator iter = vMonster.begin();
    for (iter; iter != vMonster.end(); ++iter)
    {
        //1. 플레이어매직블릿
        for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
        {
            if (iter->activestate!=MONSTERACTIVE::DEATH &&
                IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->rc))
            {
                if (!iter->isInvincible) {
                    monster->knockback(iter,
                        bm->getMgcBulInstance()->getVBullet()[i].x,
                        bm->getMgcBulInstance()->getVBullet()[i].y,
                        //PLAYER->getPlayerAddress().damage,
                        10,     //데미지 부분 꼭 수정. 여기 한줄 지우고 윗줄 주석 해제할 것.
                        10, false);
                }
                bm->getMgcBulInstance()->removeBullet(i);
            }
        }
        //2. 플레이어 화살
        for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
        {
            if (iter->activestate != MONSTERACTIVE::DEATH && 
                IntersectRect(&temprc, &bm->getArwBulInstance()->getVBullet()[i].rc, &iter->rc))
            {
                if (!iter->isInvincible) {
                    monster->knockback(iter,
                        bm->getArwBulInstance()->getVBullet()[i].x,
                        bm->getArwBulInstance()->getVBullet()[i].y,
                        //PLAYER->getPlayerAddress().damage,
                        10,     //데미지 부분 꼭 수정. 여기 한줄 지우고 윗줄 주석 해제할 것.
                        10, false);
                }
                bm->getArwBulInstance()->removeBullet(i);
            }
        }
        //3. 


    }
}
