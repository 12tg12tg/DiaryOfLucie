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
	playerTomon();
}

void collisionManager::bulletToplayer()
{
	//cir충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getCirBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getCirBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getCirBulInstance()->removeBullet(i);
					PLAYER->hitPlayer(bm->getCirBulInstance()->getVBullet()[i].x, bm->getCirBulInstance()->getVBullet()[i].y);
				}
			}
		}
	}
	else
	{
		;
	}
	//flwbos1충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getFlwBos1Bullnstance()->getVBullet3().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getFlwBos1Bullnstance()->getVBullet3()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//flwbos2충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getFlwBos2Bullnstance()->getVBullet2().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getFlwBos2Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//flwbos3충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getFlwBos3Bullnstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getFlwBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getFlwBos3Bullnstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//long poison충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getLPsnBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getLPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//niddle 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getnidBulInstance()->getVBullet2().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getnidBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//poison 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getPsnBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//return1 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getRtnBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getRtnBulInstance()->getVBullet()[i].iscollison = true;
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getRtnBulInstance()->getVBullet2().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getRtnBulInstance()->removeBullet2(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//slime boss 1 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getSlmBos1Bullnstance()->getVBullet()[i].iscollison = true;
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet2().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getSlmBos1Bullnstance()->removeBullet2(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//tree boss 1 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getTreBos1Bullnstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getTreBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//tree boss 2 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getTreBos2Bullnstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getTreBos2Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getTreBos2Bullnstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//tree boss 3 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getTreBos3Bullnstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getTreBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getTreBos3Bullnstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//triple 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getTriBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getTriBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getTriBulInstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//wide 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getWidBulInstance()->getVBullet().size(); i++)
			{
				if (IntersectRect(&temprc, &bm->getWidBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
				{
					bm->getWidBulInstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}
		}
	}
	else
	{
		;
	}
	//homing 충돌
	if (PLAYER->getSTATEAddress() != STATE::DASH)
	{
		if (PLAYER->getPlayerAddress().isHit == false)
		{
			for (int i = 0; i < bm->getHomBulInstance()->getVBullet().size(); i++)
			{
				if (OBB->isOBBCollision(bm->getHomBulInstance()->getVBullet()[i].rc, bm->getHomBulInstance()->getVBullet()[i].angle,
					PLAYER->getPlayerAddress().playerRect, 0))
				{
					bm->getHomBulInstance()->removeBullet(i);
					PLAYER->getPlayerAddress().isHit = true;
				}
			}

		}
	}
	else
	{
		;
	}
}
void collisionManager::bulletTomon()
{                                                      
    checkMonsterRectColl(mm->getSnaby(), false);               //★몬스터 생성시 여기에 추가. //오브젝트도 같이 추가하면 좋을듯.
    checkMonsterRectColl(mm->getSlime(), false);
    checkMonsterRectColl(mm->getMushman(), false);
    checkMonsterRectColl(mm->getMushman_Mushroom(), false);
    checkMonsterRectColl(mm->getFairy(), false);
    checkMonsterRectColl(mm->getFlime(), false);
    checkMonsterRectColl(mm->getBoss_Slime(), false);
    checkMonsterRectColl(mm->getSemiBoss_Slime(), false);
    checkMonsterRectColl(mm->getBoss_Flime(), false);
    checkMonsterRectColl(mm->getBoss_Mushmam(), false);
    checkMonsterRectColl(mm->getBoss_Mushroom_G(), false);
    checkMonsterRectColl(mm->getBoss_Mushroom_P(), false);
    checkMonsterRectColl(mm->getBoss_Mushroom_B(), false);
    checkMonsterRectColl(mm->getYggdrasil_Bomb(), false);
    checkMonsterRectColl(mm->getYggdrasil(), true);


}

void collisionManager::playerTomon()
{
	checkMonsterRectPlayer(mm->getSnaby());               //★몬스터 생성시 여기에 추가. //오브젝트도 같이 추가하면 좋을듯.
	checkMonsterRectPlayer(mm->getSlime());
	checkMonsterRectPlayer(mm->getMushman());
	checkMonsterRectPlayer(mm->getMushman_Mushroom());
	checkMonsterRectPlayer(mm->getFairy());
	checkMonsterRectPlayer(mm->getFlime());
	checkMonsterRectPlayer(mm->getBoss_Slime());
	checkMonsterRectPlayer(mm->getSemiBoss_Slime());
	checkMonsterRectPlayer(mm->getBoss_Flime());
	checkMonsterRectPlayer(mm->getBoss_Mushmam());
	checkMonsterRectPlayer(mm->getBoss_Mushroom_G());
	checkMonsterRectPlayer(mm->getBoss_Mushroom_P());
	checkMonsterRectPlayer(mm->getBoss_Mushroom_B());
	checkMonsterRectPlayer(mm->getYggdrasil_Bomb());
	checkMonsterRectPlayer(mm->getYggdrasil());
}

void collisionManager::checkMonsterRectPlayer(monster* monster)
{
    vector<tagMonster>& vMonster = monster->getVMonster();
    vector<tagMonster>::iterator iter = vMonster.begin();
    for (iter; iter != vMonster.end(); ++iter)
    {
        RECT temp ;
        RECT* rc1 = &PLAYER->getPlayerAddress().playerRect;
        RECT* rc2 = &iter->footRc;
        if (IntersectRect(&temp, rc1, rc2))
        {
            int fromtop, frombottom, fromleft, fromright;
            int centerx, centery;
            int min;
            centerx = temp.left + (temp.right - temp.left) / 2;
            centery = temp.top + (temp.bottom - temp.top) / 2;
            fromtop = centery - rc2->top;
            frombottom = rc2->bottom - centery;
            fromleft = centerx - rc2->left;
            fromright = rc2->right - centerx;

			min = (fromtop >= frombottom) ? frombottom : fromtop;
			min = (min >= fromleft) ? fromleft : min;
			min = (min >= fromright) ? fromright : min;
			if (min == fromtop && min <= 50)
			{
				if (PLAYER->getSTATEAddress() != STATE::DASH)
				{
					PLAYER->getPlayerAddress().y = rc2->top - (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
				}
				else
				{
					;
				}

			}
			else if (min == frombottom)
			{
				if (PLAYER->getSTATEAddress() != STATE::DASH)
				{
					PLAYER->getPlayerAddress().y = rc2->bottom + (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
				}
				else
				{
					;
				}
			}
			else if (min == fromleft)
			{
				if (PLAYER->getSTATEAddress() != STATE::DASH)
				{
					PLAYER->getPlayerAddress().x = rc2->left - (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
				}
				else
				{
					;
				}
			}
			else if (min == fromright)
			{
				if (PLAYER->getSTATEAddress() != STATE::DASH)
				{
					PLAYER->getPlayerAddress().x = rc2->right + (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
				}
				else
				{
					;
				}
			}
		}

	}
}

void collisionManager::checkMonsterRectColl(monster* monster, bool isBoss)            //★플레이어의 공격수단 생성시 여기에 꼭 추가.
{
    vector<tagMonster>& vMonster = monster->getVMonster();
    vector<tagMonster>::iterator iter = vMonster.begin();
    for (iter; iter != vMonster.end(); ++iter)
    {
        //1. 플레이어매직블릿
        for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
        {
            if (!isBoss) {
                if (iter->activestate != MONSTERACTIVE::DEATH &&
                    IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->rc))
                {
                    if (!iter->isGraceperiod) {
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
            //보스의경우 RECT가 두개이므로 따로진행
            else {
                if (iter->activestate != MONSTERACTIVE::DEATH &&
                    (IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->bossRc[0])||
                        IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->bossRc[1])))
                {
                    if (!iter->isGraceperiod) {
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
        }
        //2. 플레이어 화살
        for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
        {
            if (!isBoss) {
                if (iter->activestate != MONSTERACTIVE::DEATH &&
                    OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle,
                        iter->rc, 0))
                {
                    if (!iter->isGraceperiod) {
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
            //보스의경우 RECT가 두개이므로 따로진행
            else {
                if (iter->activestate != MONSTERACTIVE::DEATH &&
                    (IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->bossRc[0]) ||
                        IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &iter->bossRc[1])))
                {
                    if (!iter->isGraceperiod) {
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
        }

        //3. 


	}
}
