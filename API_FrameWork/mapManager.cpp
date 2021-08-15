#include "framework.h"
#include "mapManager.h"
#include"monsterManager.h"
HRESULT mapManager::init()
{
	_Cmap1 = dynamic_cast<Cmap*>(SCENE->addScene("_Cmap1", new Cmap));
	_Cmap2 = dynamic_cast<Cmap2*>(SCENE->addScene("_Cmap2", new Cmap2));
	_Cmap3 = dynamic_cast<Cmap3*>(SCENE->addScene("_Cmap3", new Cmap3));
	_Cmap4 = dynamic_cast<Cmap4*>(SCENE->addScene("_Cmap4", new Cmap4));
	_Cmap5 = dynamic_cast<Cmap5*>(SCENE->addScene("_Cmap5", new Cmap5));
	_Cmap6 = dynamic_cast<Cmap6*>(SCENE->addScene("_Cmap6", new Cmap6));
	_Cmap7 = dynamic_cast<Cmap7*>(SCENE->addScene("_Cmap7", new Cmap7));
	_Cmap8 = dynamic_cast<Cmap8*>(SCENE->addScene("_Cmap8", new Cmap8));
	_Cmap9 = dynamic_cast<Cmap9*>(SCENE->addScene("_Cmap9", new Cmap9));
	_Cmap10 = dynamic_cast<Cmap10*>(SCENE->addScene("_Cmap10", new Cmap10));
	_chestMap = dynamic_cast<chestMap*>(SCENE->addScene("_chestMap", new chestMap));
	_shopMap = dynamic_cast<shopMap*>(SCENE->addScene("_shopMap", new shopMap));
	_statueMap = dynamic_cast<statueMap*>(SCENE->addScene("_statueMap", new statueMap));
	_moruMap = dynamic_cast<moruMap*>(SCENE->addScene("_moruMap", new moruMap));


	_Cmap1->setMonstermemoryLink(mm);
	_Cmap2->setMonstermemoryLink(mm);
	_Cmap3->setMonstermemoryLink(mm);
	_Cmap4->setMonstermemoryLink(mm);
	_Cmap5->setMonstermemoryLink(mm);
	_Cmap6->setMonstermemoryLink(mm);
	_Cmap7->setMonstermemoryLink(mm);
	_Cmap8->setMonstermemoryLink(mm);
	_Cmap9->setMonstermemoryLink(mm);
	_Cmap10->setMonstermemoryLink(mm);
	_chestMap->setMonstermemoryLink(mm);
	_shopMap->setMonstermemoryLink(mm);
	_statueMap->setMonstermemoryLink(mm);
	_moruMap->setMonstermemoryLink(mm);

	
	while (remainRoom > 4 )
	{
		makeclear();
		remainRoom = mapSize;
		makestage1((MAXSIZE - 1) / 2,(MAXSIZE+1)/2);
		setstatueRoom();
		setchestRoom();
		setMORURoom();
		setShopRoom();
	}


	//MAP stage1[2][2] = { {{nullptr,"",false,true,NONE,},{_Cmap5,"_Cmap5",false,true,NONE}},{{_Cmap2,"_Cmap2",false,true,START},{_Cmap3,"_Cmap3",false,true,NONE}} };
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind != MAPKIND::NONE)
			{
				_mStage1.insert(pair<string, motherMap*>(stage1[i][k].sceneKey, stage1[i][k]._motherMap));
				//stage1[i][k]._motherMap->setPoint({ i,k });
				if (stage1[i][k].mapkind == MAPKIND::START)
				{
					//맵을 다시돌면서 값을 넣어줌
					currentMap = stage1[i][k].sceneKey;
					currentIndex.x = i;
					currentIndex.y = k;
					SCENE->changeScene(currentMap);
				}
			}
		}
	}


	return S_OK;
}

void mapManager::release()
{
	SCENE->release();
}

void mapManager::update()
{
	currentMonNum = 0;
	doorstate(mm->getSnaby());
	doorstate(mm->getSlime());
	doorstate(mm->getMushman());
	doorstate(mm->getMushman_Mushroom());
	doorstate(mm->getFairy());
	doorstate(mm->getFlime());
	doorstate(mm->getBoss_Slime());
	doorstate(mm->getSemiBoss_Slime());
	doorstate(mm->getBoss_Flime());
	doorstate(mm->getBoss_Mushmam());
	doorstate(mm->getBoss_Mushroom_G());
	doorstate(mm->getBoss_Mushroom_P());
	doorstate(mm->getBoss_Mushroom_B());
	doorstate(mm->getYggdrasil_Bomb());
	doorstate(mm->getYggdrasil());
	if (currentMonNum != 0)
	{
		/*rightdoor_open = false;
		leftdoor_open = false;
		topdoor_open = false;
		bottomdoor_open = false;*/
	}
	else
	{
		UseableDoor();
	}
	if (checkright)
	{
		SCENE->changeScene(stage1[currentIndex.x + 1][currentIndex.y].sceneKey);
	}
	if (checkleft)
	{
		SCENE->changeScene(stage1[currentIndex.x - 1][currentIndex.y].sceneKey);
	}
	if (checkbottom)
	{
		SCENE->changeScene(stage1[currentIndex.x][currentIndex.y+1].sceneKey);
	}
	if (checktop)
	{
		SCENE->changeScene(stage1[currentIndex.x ][currentIndex.y-1].sceneKey);
	}
	SCENE->update();
}

void mapManager::render()
{
	SCENE->render();

}



void mapManager::doorstate(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		currentMonNum += monster->getVMonster().size();
	}
}

void mapManager::UseableDoor()
{
	//if (stage1[currentIndex.x - 1][currentIndex.y].KINDMAKE != KINDMAKE::NONE)
	//{
	//	_mStage1.find(currentMap)->second->getDungeonDoor()[0].isOpen = true;
	//}
	//if (stage1[currentIndex.x][currentIndex.y - 1].KINDMAKE != KINDMAKE::NONE)
	//{
	//	_mStage1.find(currentMap)->second->getDungeonDoor()[1].isOpen = true;
	//}
	//if (stage1[currentIndex.x + 1][currentIndex.y].KINDMAKE != KINDMAKE::NONE)
	//{
	//	_mStage1.find(currentMap)->second->getDungeonDoor()[2].isOpen = true;
	//}
	//if (stage1[currentIndex.x][currentIndex.y + 1].KINDMAKE != KINDMAKE::NONE)
	//{
	//	_mStage1.find(currentMap)->second->getDungeonDoor()[3].isOpen = true;
	//}

}
void mapManager::makestage1(int i, int k)
{
	if (remainRoom < 0 ||
		i < 0 ||
		i >= MAXSIZE ||
		k < 0 ||
		k >= MAXSIZE ||
		stage1[i][k].mapkind != MAPKIND::NONE)
		return;

	remainRoom--;
	stage1[i][k].mapkind = MAPKIND::NORMAL;
	if (!(bool)(RND->getInt(4))) makestage1(i + 1, k);//r
	if (!(bool)(RND->getInt(4))) makestage1(i -1, k);//l
	if (!(bool)(RND->getInt(4))) makestage1(i, k-1);//u
	if (!(bool)(RND->getInt(4))) makestage1(i, k +1);//d

}

bool mapManager::setstatueRoom()
{
	int setstatue = mapSize - 6;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setstatue--;
				if (RND->getInt(100) > 50 || setstatue == 0)
				{
					stage1[i][k] = { _statueMap,"_statueMap",STATUEROOM };

				}
				return true;
			}
		}
	}
	return false;
}
bool mapManager::setchestRoom()
{
	int setchest = mapSize-5;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setchest--;
				if (RND->getInt(100) > 50 || setchest == 0)
				{
					stage1[i][k] = { _chestMap,"_chestMap",CHESTROOM };

				}
				return true;
			}
		}
	}
	return false;
}


bool mapManager::setMORURoom()
{
	int setMORU = mapSize-4;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setMORU--;
				if (RND->getInt(100) > 50 || setMORU == 0)
				{
					stage1[i][k] = { _moruMap,"_moruMap",MORUROOM };

				}
				return true;
			}
		}
	}
	return false;
}

bool mapManager::setShopRoom()
{
	int setShop = mapSize-3;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setShop--;
				if ( RND->getInt(100) >50 || setShop == 0)
				{
					stage1[i][k] = { _shopMap,"_shopMap",SHOP };
					
				}
				return true;
			}
		}
	}
	return false;
}




//bool mapManager::setBossRoom()
//{
//
//}
//
//bool mapManager::setNextRoom()
//{
//
//}





void mapManager::makeclear() {
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			stage1[i][k].mapkind = NONE;
			stage1[i][k].sceneKey = "";
			stage1[i][k]._motherMap = nullptr;
		}
	}
	stage1[(MAXSIZE - 1) / 2][(MAXSIZE - 1) / 2] = { _Cmap9,"_Cmap9",START };
	remainRoom = 12;
	remain_SHOP = 1;
	remain_MORUROOM = 1;
	remain_statueROOM = 1;
	remain_CHESTROOM = 1;
}