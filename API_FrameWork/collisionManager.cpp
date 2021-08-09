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
 
}

void collisionManager::bulletToplayer()
{
    //cir面倒
    for (int i = 0; i < bm->getCirBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getCirBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getCirBulInstance()->removeBullet(i);
            //damage
        }
    }
    //flwbos1面倒
    for (int i = 0; i < bm->getFlwBos1Bullnstance()->getVBullet3().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos1Bullnstance()->getVBullet3()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //flwbos2面倒
    for (int i = 0; i < bm->getFlwBos2Bullnstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos2Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {  
            //damage
        }
    }
    //flwbos3面倒
    for (int i = 0; i < bm->getFlwBos3Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getFlwBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getFlwBos3Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //long poison面倒
    for (int i = 0; i < bm->getLPsnBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getLPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //niddle 面倒
    for (int i = 0; i < bm->getnidBulInstance()->getVBullet2().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getnidBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //poison 面倒
    for (int i = 0; i < bm->getPsnBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //return1 面倒
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
    //slime boss 1 面倒
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
    //tree boss 1 面倒
    for (int i = 0; i < bm->getTreBos1Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            //damage
        }
    }
    //tree boss 2 面倒
    for (int i = 0; i < bm->getTreBos2Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos2Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTreBos2Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //tree boss 3 面倒
    for (int i = 0; i < bm->getTreBos3Bullnstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTreBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTreBos3Bullnstance()->removeBullet(i);
            //damage
        }
    }
    //triple 面倒
    for (int i = 0; i < bm->getTriBulInstance()->getVBullet().size(); i++)
    {
        if (IntersectRect(&temprc, &bm->getTriBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
        {
            bm->getTriBulInstance()->removeBullet(i);
            //damage
        }
    }
    //wide 面倒
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


}

void collisionManager::playerTomon()
{
}

