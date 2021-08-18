#include "framework.h"
#include "collisionManager.h"
#include"bulletManager.h"
#include"monsterManager.h"
#include"mapManager.h"
#include"Cplayer.h"
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
	bulletToMap();
	playerTomon();
	mapToplayer();
	playerToDoor();
	mapTomon();
	bulletTobullet();
}

void collisionManager::bulletToplayer()
{
	//cir충돌
	for (int i = 0; i < bm->getCirBulInstance()->getVBullet().size(); ) {
		if (IntersectRect(&temprc, &bm->getCirBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect)) {
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getCirBulInstance()->getVBullet()[i].x, bm->getCirBulInstance()->getVBullet()[i].y);
				bm->getCirBulInstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//flwbos1충돌
	for (int i = 0; i < bm->getFlwBos1Bullnstance()->getVBullet3().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getFlwBos1Bullnstance()->getVBullet3()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getFlwBos1Bullnstance()->getVBullet3()[i].x, bm->getFlwBos1Bullnstance()->getVBullet3()[i].y);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
	}
	//flwbos2충돌
	for (int i = 0; i < bm->getFlwBos2Bullnstance()->getVBullet2().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getFlwBos2Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getFlwBos2Bullnstance()->getVBullet2()[i].x, bm->getFlwBos2Bullnstance()->getVBullet2()[i].y);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}

	}
	//flwbos3충돌
	for (int i = 0; i < bm->getFlwBos3Bullnstance()->getVBullet().size(); )
	{
		if (IntersectRect(&temprc, &bm->getFlwBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getFlwBos3Bullnstance()->getVBullet()[i].x, bm->getFlwBos3Bullnstance()->getVBullet()[i].y);
				bm->getFlwBos3Bullnstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//long poison충돌
	for (int i = 0; i < bm->getLPsnBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getLPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getLPsnBulInstance()->getVBullet()[i].x, bm->getLPsnBulInstance()->getVBullet()[i].y);
				bm->getLPsnBulInstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
	}





	//niddle 충돌
	for (int i = 0; i < bm->getnidBulInstance()->getVBullet2().size(); i++)
	{
		if ( IntersectRect(&temprc, &bm->getnidBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getnidBulInstance()->getVBullet2()[i].x, bm->getnidBulInstance()->getVBullet2()[i].y);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
	}
	//poison 충돌
	for (int i = 0; i < bm->getPsnBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getPsnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getPsnBulInstance()->getVBullet()[i].x, bm->getPsnBulInstance()->getVBullet()[i].y);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}

	}
	//return1 충돌
	for (int i = 0; i < bm->getRtnBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getRtnBulInstance()->getVBullet()[i].x, bm->getRtnBulInstance()->getVBullet()[i].y);
				bm->getRtnBulInstance()->getVBullet()[i].iscollison = true;
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}

	}

	for (int i = 0; i < bm->getRtnBulInstance()->getVBullet2().size(); )
	{
		if (IntersectRect(&temprc, &bm->getRtnBulInstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getRtnBulInstance()->getVBullet2()[i].x, bm->getRtnBulInstance()->getVBullet2()[i].y);
				bm->getRtnBulInstance()->removeBullet2(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//slime boss 1 충돌
	for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getSlmBos1Bullnstance()->getVBullet()[i].x, bm->getSlmBos1Bullnstance()->getVBullet()[i].y);
				bm->getSlmBos1Bullnstance()->getVBullet()[i].iscollison = true;
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}

	}
	for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet2().size();)
	{
		if (IntersectRect(&temprc, &bm->getSlmBos1Bullnstance()->getVBullet2()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getSlmBos1Bullnstance()->getVBullet2()[i].x, bm->getSlmBos1Bullnstance()->getVBullet2()[i].y);
				bm->getSlmBos1Bullnstance()->removeBullet2(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else
		{
			i++;
		}

	}
	//tree boss 1 충돌
	for (int i = 0; i < bm->getTreBos1Bullnstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temprc, &bm->getTreBos1Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getTreBos1Bullnstance()->getVBullet()[i].x, bm->getTreBos1Bullnstance()->getVBullet()[i].y);
				bm->getTreBos1Bullnstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}

	}
	//tree boss 2 충돌
	for (int i = 0; i < bm->getTreBos2Bullnstance()->getVBullet().size(); )
	{
		if (IntersectRect(&temprc, &bm->getTreBos2Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getTreBos2Bullnstance()->getVBullet()[i].x, bm->getTreBos2Bullnstance()->getVBullet()[i].y);
				bm->getTreBos2Bullnstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//tree boss 3 충돌
	for (int i = 0; i < bm->getTreBos3Bullnstance()->getVBullet().size(); )
	{
		if (IntersectRect(&temprc, &bm->getTreBos3Bullnstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit|| PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getTreBos3Bullnstance()->getVBullet()[i].x, bm->getTreBos3Bullnstance()->getVBullet()[i].y);
				bm->getTreBos3Bullnstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//triple 충돌
	for (int i = 0; i < bm->getTriBulInstance()->getVBullet().size();)
	{
		if (IntersectRect(&temprc, &bm->getTriBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getTriBulInstance()->getVBullet()[i].x, bm->getTriBulInstance()->getVBullet()[i].y);
				bm->getTriBulInstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit|| PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//wide 충돌
	for (int i = 0; i < bm->getWidBulInstance()->getVBullet().size(); )
	{
		if (IntersectRect(&temprc, &bm->getWidBulInstance()->getVBullet()[i].rc, &PLAYER->getPlayerAddress().playerRect))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getWidBulInstance()->getVBullet()[i].x, bm->getWidBulInstance()->getVBullet()[i].y);
				bm->getWidBulInstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
		else {
			i++;
		}
	}
	//homing 충돌
	for (int i = 0; i < bm->getHomBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getHomBulInstance()->getVBullet()[i].rc, bm->getHomBulInstance()->getVBullet()[i].angle,
			PLAYER->getPlayerAddress().playerRect, 0))
		{
			if (!(PLAYER->getSTATEAddress() == STATE::DASH || PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT)) {
				PLAYER->hitPlayer(bm->getHomBulInstance()->getVBullet()[i].x, bm->getHomBulInstance()->getVBullet()[i].y);
				bm->getHomBulInstance()->removeBullet(i);
				break;
			}
			else if (PLAYER->getSTATEAddress() == STATE::DASH) {
				PLAYER->hitDash();
				break;
			}
			else if (PLAYER->getPlayerAddress().isHit || PLAYER->getSTATEAddress() == STATE::DASHATT) {
				break;
			}
		}
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

void collisionManager::mapToplayer()
{
	checkUp();
	checkDown();
	checkLeft();
	checkRight();

}

void collisionManager::checkUp()
{
	for (int i = PLAYER->getPlayerAddress().y - 1; i > PLAYER->getPlayerAddress().y - 10; i--)
	{
		COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), PLAYER->getPlayerAddress().x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			PLAYER->getPlayerAddress().y++;
		}

	}
}

void collisionManager::checkRight()
{
	for (int i = PLAYER->getPlayerAddress().x + 1; i < PLAYER->getPlayerAddress().x + 10; i++)
	{
		COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), i, PLAYER->getPlayerAddress().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			PLAYER->getPlayerAddress().x--;
		}
	}
}

void collisionManager::checkLeft()
{
	for (int i = PLAYER->getPlayerAddress().x - 1; i > PLAYER->getPlayerAddress().x - 10; i--)
	{
		COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), i, PLAYER->getPlayerAddress().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			PLAYER->getPlayerAddress().x++;
		}
	}
}

void collisionManager::checkDown()
{
	for (int i = PLAYER->getPlayerAddress().y + 1; i < PLAYER->getPlayerAddress().y + 10; i++)
	{
		COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), PLAYER->getPlayerAddress().x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			PLAYER->getPlayerAddress().y--;
		}

	}
}


void collisionManager::checkMonUp(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		for (int i = RecCenY(iter->footRc) - 1; i > iter->footRc.top - 10; i--)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), RecCenX(iter->footRc), i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				iter->y++;
				monster->makeCollisionRect(iter);
			}

		}
	}
}

void collisionManager::checkMonDown(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		for (int i = RecCenY(iter->footRc) + 1; i < RecCenY(iter->footRc) + 10; i++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), RecCenX(iter->footRc), i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				iter->y--;
				monster->makeCollisionRect(iter);
			}

		}
	}

}

void collisionManager::checkMonLeft(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		for (int i = RecCenX(iter->footRc) - 1; i > RecCenX(iter->footRc) - 10; i--)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), i, RecCenY(iter->footRc));

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				iter->x++;
				monster->makeCollisionRect(iter);
			}
		}
	}
}

void collisionManager::checkMonRight(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		for (int i = RecCenX(iter->footRc) + 1; i < RecCenX(iter->footRc) + 10; i++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), i, RecCenY(iter->footRc));

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				iter->x--;
				monster->makeCollisionRect(iter);
			}
		}
	}
}
void collisionManager::mapTomon()
{

	checkMonLeft(mm->getSnaby());
	checkMonLeft(mm->getSlime());
	checkMonLeft(mm->getMushman());
	checkMonLeft(mm->getMushman_Mushroom());
	checkMonLeft(mm->getFairy());
	checkMonLeft(mm->getFlime());
	checkMonLeft(mm->getBoss_Slime());
	checkMonLeft(mm->getSemiBoss_Slime());
	checkMonLeft(mm->getBoss_Flime());
	checkMonLeft(mm->getBoss_Mushmam());
	checkMonLeft(mm->getBoss_Mushroom_G());
	checkMonLeft(mm->getBoss_Mushroom_P());
	checkMonLeft(mm->getBoss_Mushroom_B());
	checkMonLeft(mm->getYggdrasil_Bomb());
	//checkMonLeft(mm->getYggdrasil());

	checkMonRight(mm->getSnaby());
	checkMonRight(mm->getSlime());
	checkMonRight(mm->getMushman());
	checkMonRight(mm->getMushman_Mushroom());
	checkMonRight(mm->getFairy());
	checkMonRight(mm->getFlime());
	checkMonRight(mm->getBoss_Slime());
	checkMonRight(mm->getSemiBoss_Slime());
	checkMonRight(mm->getBoss_Flime());
	checkMonRight(mm->getBoss_Mushmam());
	checkMonRight(mm->getBoss_Mushroom_G());
	checkMonRight(mm->getBoss_Mushroom_P());
	checkMonRight(mm->getBoss_Mushroom_B());
	checkMonRight(mm->getYggdrasil_Bomb());
	//checkMonRight(mm->getYggdrasil());

	checkMonUp(mm->getSnaby());
	checkMonUp(mm->getSlime());
	checkMonUp(mm->getMushman());
	checkMonUp(mm->getMushman_Mushroom());
	checkMonUp(mm->getFairy());
	checkMonUp(mm->getFlime());
	checkMonUp(mm->getBoss_Slime());
	checkMonUp(mm->getSemiBoss_Slime());
	checkMonUp(mm->getBoss_Flime());
	checkMonUp(mm->getBoss_Mushmam());
	checkMonUp(mm->getBoss_Mushroom_G());
	checkMonUp(mm->getBoss_Mushroom_P());
	checkMonUp(mm->getBoss_Mushroom_B());
	checkMonUp(mm->getYggdrasil_Bomb());
	//checkMonUp(mm->getYggdrasil());

	checkMonDown(mm->getSnaby());
	checkMonDown(mm->getSlime());
	checkMonDown(mm->getMushman());
	checkMonDown(mm->getMushman_Mushroom());
	checkMonDown(mm->getFairy());
	checkMonDown(mm->getFlime());
	checkMonDown(mm->getBoss_Slime());
	checkMonDown(mm->getSemiBoss_Slime());
	checkMonDown(mm->getBoss_Flime());
	checkMonDown(mm->getBoss_Mushmam());
	checkMonDown(mm->getBoss_Mushroom_G());
	checkMonDown(mm->getBoss_Mushroom_P());
	checkMonDown(mm->getBoss_Mushroom_B());
	checkMonDown(mm->getYggdrasil_Bomb());
	//checkMonDown(mm->getYggdrasil());

}

void collisionManager::playerToDoor()
{
	//Cmap
	if (mapm->getCurrentDoor()[0].isOpen && IntersectRect(&temprc, &mapm->getCurrentDoor()[0].Door, &PLAYER->getPlayerAddress().playerRect))
	{
		mapm->checkleftdoorcollison(true);
	}
	else
	{
		mapm->checkleftdoorcollison(false);
	}
	if (mapm->getCurrentDoor()[1].isOpen && IntersectRect(&temprc, &mapm->getCurrentDoor()[1].Door, &PLAYER->getPlayerAddress().playerRect))
	{
		mapm->checktopdoorcollison(true);
	}
	else
	{
		mapm->checktopdoorcollison(false);

	}
	if (mapm->getCurrentDoor()[2].isOpen && IntersectRect(&temprc, &mapm->getCurrentDoor()[2].Door, &PLAYER->getPlayerAddress().playerRect))
	{
		mapm->checkrightdoorcollison(true);
	}
	else
	{
		mapm->checkrightdoorcollison(false);
	}
	if (mapm->getCurrentDoor()[3].isOpen && IntersectRect(&temprc, &mapm->getCurrentDoor()[3].Door, &PLAYER->getPlayerAddress().playerRect))
	{
		mapm->checkdowndoorcollison(true);
	}
	else
	{
		mapm->checkdowndoorcollison(false);
	}
	if (IntersectRect(&temprc, &mapm->getMagicDoor()[0].Door, &PLAYER->getPlayerAddress().playerRect))
	{
		mapm->checkMagicDoorCollison(true);
	}
	else
	{
		mapm->checkMagicDoorCollison(false);
	}
}

void collisionManager::bulletToMap()
{
	//cir 불릿
	for (int i = 0; i < bm->getCirBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getCirBulInstance()->getVBullet()[i].x -1; k < bm->getCirBulInstance()->getVBullet()[i].x +1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getCirBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getCirBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//flowbos3 불릿
	for (int i = 0; i < bm->getFlwBos3Bullnstance()->getVBullet().size(); )
	{
		for (int k = bm->getFlwBos3Bullnstance()->getVBullet()[i].x - 1; k < bm->getFlwBos3Bullnstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getFlwBos3Bullnstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getFlwBos3Bullnstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	//Long poion 불릿
	for (int i = 0; i < bm->getLPsnBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getLPsnBulInstance()->getVBullet()[i].x - 1; k < bm->getLPsnBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getLPsnBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getLPsnBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//poion 불릿
	for (int i = 0; i < bm->getPsnBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getPsnBulInstance()->getVBullet()[i].x - 1; k < bm->getPsnBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getPsnBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getPsnBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//return 불릿
	for (int i = 0; i < bm->getRtnBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getRtnBulInstance()->getVBullet()[i].x - 1; k < bm->getRtnBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getRtnBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getRtnBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//return 불릿
	for (int i = 0; i < bm->getRtnBulInstance()->getVBullet2().size(); )
	{
		for (int k = bm->getRtnBulInstance()->getVBullet2()[i].x - 1; k < bm->getRtnBulInstance()->getVBullet2()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getRtnBulInstance()->getVBullet2()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getRtnBulInstance()->getVBullet2()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//slimboss1 불릿
	for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet().size(); )
	{
		for (int k = bm->getSlmBos1Bullnstance()->getVBullet()[i].x - 1; k < bm->getSlmBos1Bullnstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getSlmBos1Bullnstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getSlmBos1Bullnstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//slimboss1 불릿
	for (int i = 0; i < bm->getSlmBos1Bullnstance()->getVBullet2().size(); )
	{
		for (int k = bm->getSlmBos1Bullnstance()->getVBullet2()[i].x - 1; k < bm->getSlmBos1Bullnstance()->getVBullet2()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getSlmBos1Bullnstance()->getVBullet2()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getSlmBos1Bullnstance()->getVBullet2()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//treeboss1 불릿
	for (int i = 0; i < bm->getTreBos1Bullnstance()->getVBullet().size(); )
	{
		for (int k = bm->getTreBos1Bullnstance()->getVBullet()[i].x - 1; k < bm->getTreBos1Bullnstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getTreBos1Bullnstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getTreBos1Bullnstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}

	//treeboss2 불릿
	for (int i = 0; i < bm->getTreBos2Bullnstance()->getVBullet().size(); )
	{
		for (int k = bm->getTreBos2Bullnstance()->getVBullet()[i].x - 1; k < bm->getTreBos2Bullnstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getTreBos2Bullnstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getTreBos2Bullnstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}

	//triple 불릿
	for (int i = 0; i < bm->getTriBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getTriBulInstance()->getVBullet()[i].x - 1; k < bm->getTriBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getTriBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getTriBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//wide 불릿
	for (int i = 0; i < bm->getWidBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getWidBulInstance()->getVBullet()[i].x - 1; k < bm->getWidBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getWidBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getWidBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	
	//homing불릿
	for (int i = 0; i < bm->getHomBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getHomBulInstance()->getVBullet()[i].x - 1; k < bm->getHomBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getHomBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getHomBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	//FbossV1
	for (int i = 0; i < bm->getFlwBos1Bullnstance()->getVBullet().size(); )
	{
		for (int k = bm->getFlwBos1Bullnstance()->getVBullet()[i].x - 1; k < bm->getFlwBos1Bullnstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getFlwBos1Bullnstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getFlwBos1Bullnstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}

	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getMgcBulInstance()->getVBullet()[i].x - 1; k < bm->getMgcBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getMgcBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getMgcBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); )
	{
		for (int k = bm->getArwBulInstance()->getVBullet()[i].x - 1; k < bm->getArwBulInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getArwBulInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getArwBulInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	for (int i = 0; i < bm->getChargeInstance()->getVBullet().size(); )
	{
		for (int k = bm->getChargeInstance()->getVBullet()[i].x - 1; k < bm->getChargeInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getChargeInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getChargeInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
	for (int i = 0; i < bm->getIce_spearInstance()->getVBullet().size(); )
	{
		for (int k = bm->getIce_spearInstance()->getVBullet()[i].x - 1; k < bm->getIce_spearInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getIce_spearInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getIce_spearInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}

	for (int i = 0; i < bm->getLucky_starInstance()->getVBullet().size(); )
	{
		for (int k = bm->getLucky_starInstance()->getVBullet()[i].x - 1; k < bm->getLucky_starInstance()->getVBullet()[i].x + 1; k++)
		{
			COLORREF  color = GetPixel(mapm->getCurrentColMap()->getMemDC(), k, bm->getLucky_starInstance()->getVBullet()[i].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				bm->getLucky_starInstance()->getVBullet()[i].iscollison = true;
			}
		}
		i++;
	}
}

void collisionManager::bulletTobullet()
{
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &bm->getPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getMgcBulInstance()->getVBullet()[i].colPoison = true;
			}
		}

	}
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getLPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getMgcBulInstance()->getVBullet()[i].rc, &bm->getLPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getMgcBulInstance()->getVBullet()[i].colPoison = true;
			}
		}
	}

	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getArwBulInstance()->getVBullet()[i].rc, &bm->getPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getArwBulInstance()->getVBullet()[i].colPoison = true;
			}
		}

	}
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getLPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getArwBulInstance()->getVBullet()[i].rc, &bm->getLPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getArwBulInstance()->getVBullet()[i].colPoison = true;
			}
		}
	}

	for (int i = 0; i < bm->getChargeInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getChargeInstance()->getVBullet()[i].rc, &bm->getPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getChargeInstance()->getVBullet()[i].colPoison = true;
			}
		}

	}
	for (int i = 0; i < bm->getChargeInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getLPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getChargeInstance()->getVBullet()[i].rc, &bm->getLPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getChargeInstance()->getVBullet()[i].colPoison = true;
			}
		}
	}

	for (int i = 0; i < bm->getLucky_starInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getLucky_starInstance()->getVBullet()[i].rc, &bm->getPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getLucky_starInstance()->getVBullet()[i].colPoison = true;
			}
		}

	}
	for (int i = 0; i < bm->getLucky_starInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getLPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getLucky_starInstance()->getVBullet()[i].rc, &bm->getLPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getLucky_starInstance()->getVBullet()[i].colPoison = true;
			}
		}
	}

	for (int i = 0; i < bm->getIce_spearInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet()[i].rc, &bm->getPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getIce_spearInstance()->getVBullet()[i].colPoison = true;
			}
		}

	}
	for (int i = 0; i < bm->getIce_spearInstance()->getVBullet().size(); i++) {
		for (int k = 0; k < bm->getLPsnBulInstance()->getVBullet().size(); k++) {

			if (IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet()[i].rc, &bm->getLPsnBulInstance()->getVBullet()[k].rc))
			{
				bm->getIce_spearInstance()->getVBullet()[i].colPoison = true;
			}
		}
	}
}

void collisionManager::checkMonsterRectPlayer(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		RECT temp;
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
							PLAYERDATA->getDamage(),
							5, false);
					}
					bm->getMgcBulInstance()->removeBullet(i);
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
							PLAYERDATA->getDamage(),
							5, false);
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
							PLAYERDATA->getDamage(),
							5, false);
					}
					bm->getArwBulInstance()->removeBullet(i);
				}
			}
			//보스의경우 RECT가 두개이므로 따로진행
			else {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					(OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle,
						 iter->bossRc[0],0)) ||
					(OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle,
						iter->bossRc[1],0)))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getMgcBulInstance()->getVBullet()[i].x,
							bm->getMgcBulInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							5, false);
					}
					bm->getMgcBulInstance()->removeBullet(i);
				}
			}
		}

		//3. 아이스스피어
		for (int i = 0; i < bm->getIce_spearInstance()->getVBullet().size(); i++)
		{
			if (!isBoss) {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet()[i].rc, &iter->rc))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getIce_spearInstance()->getVBullet()[i].x,
							bm->getIce_spearInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
					
				}
			}
			//보스의경우 RECT가 두개이므로 따로진행
			else {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					(IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet()[i].rc, &iter->bossRc[0]) ||
						IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet()[i].rc, &iter->bossRc[1])))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getIce_spearInstance()->getVBullet()[i].x,
							bm->getIce_spearInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
				}
			}
		}
		for (int i = 0; i < bm->getIce_spearInstance()->getVBullet2().size(); i++)
		{
			if (!isBoss) {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet2()[i].rc, &iter->rc))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getIce_spearInstance()->getVBullet2()[i].x,
							bm->getIce_spearInstance()->getVBullet2()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
						
					}
				}
			}
			//보스의경우 RECT가 두개이므로 따로진행
			else {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					(IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet2()[i].rc, &iter->bossRc[0]) ||
						IntersectRect(&temprc, &bm->getIce_spearInstance()->getVBullet2()[i].rc, &iter->bossRc[1])))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getIce_spearInstance()->getVBullet2()[i].x,
							bm->getIce_spearInstance()->getVBullet2()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}

				}
			}
		}
		//4. 럭키스타
		for (int i = 0; i < bm->getLucky_starInstance()->getVBullet().size(); i++)
		{
			if (!isBoss) {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					IntersectRect(&temprc, &bm->getLucky_starInstance()->getVBullet()[i].rc, &iter->rc))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getLucky_starInstance()->getVBullet()[i].x,
							bm->getLucky_starInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
					bm->getLucky_starInstance()->removeBullet(i);
				}
			}
			//보스의경우 RECT가 두개이므로 따로진행
			else {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					(IntersectRect(&temprc, &bm->getLucky_starInstance()->getVBullet()[i].rc, &iter->bossRc[0]) ||
						IntersectRect(&temprc, &bm->getLucky_starInstance()->getVBullet()[i].rc, &iter->bossRc[1])))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getLucky_starInstance()->getVBullet()[i].x,
							bm->getLucky_starInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
					bm->getLucky_starInstance()->removeBullet(i);
				}
			}
		}
		//5. 차지샷
		for (int i = 0; i < bm->getChargeInstance()->getVBullet().size(); i++)
		{
			if (!isBoss) {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					IntersectRect(&temprc, &bm->getChargeInstance()->getVBullet()[i].rc, &iter->rc))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getChargeInstance()->getVBullet()[i].x,
							bm->getChargeInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
					bm->getChargeInstance()->removeBullet(i);
				}
			}
			//보스의경우 RECT가 두개이므로 따로진행
			else {
				if (iter->activestate != MONSTERACTIVE::DEATH &&
					(IntersectRect(&temprc, &bm->getChargeInstance()->getVBullet()[i].rc, &iter->bossRc[0]) ||
						IntersectRect(&temprc, &bm->getChargeInstance()->getVBullet()[i].rc, &iter->bossRc[1])))
				{
					if (!iter->isGraceperiod) {
						monster->knockback(iter,
							bm->getChargeInstance()->getVBullet()[i].x,
							bm->getChargeInstance()->getVBullet()[i].y,
							PLAYERDATA->getDamage(),
							10, false);
					}
					bm->getChargeInstance()->removeBullet(i);
				}
			}
		}
	}
}
