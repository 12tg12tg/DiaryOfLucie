#include "framework.h"
#include "mapManager.h"
#include"monsterManager.h"


mapManager::mapManager()
{
	_curstage = 1;
}
mapManager::~mapManager()
{
	
}
HRESULT mapManager::init()
{
	_Cmap10 = nullptr;
	_chestMap = nullptr;
	_shopMap = nullptr;
	_statueMap = nullptr;
	_moruMap = nullptr;
	_fountainMap = nullptr;
	_stage1_Boss = nullptr;
	_nextStage = nullptr;
	_before_boss = nullptr;
	_last_boss = nullptr;

	_none = IMAGE->addImage("빈방", "images/minimap/minimap_none.bmp", 30, 30, true, RGB(255, 0, 255));
	_start = IMAGE->addImage("시작방", "images/minimap/minimap_cellIcon_start.bmp", 30, 30, true, RGB(255, 0, 255));
	_fight = IMAGE->addImage("전투방", "images/minimap/minimap_cell_on.bmp", 30, 30, true, RGB(255, 0, 255));
	_chest = IMAGE->addImage("상자방", "images/minimap/minimap_cellIcon_chest.bmp", 30, 30, true, RGB(255, 0, 255));
	_event = IMAGE->addImage("이벤트방", "images/minimap/minimap_cellIcon_event.bmp", 30, 30, true, RGB(255, 0, 255));
	_shop = IMAGE->addImage("상점방", "images/minimap/minimap_cellIcon_shop.bmp", 30, 30, true, RGB(255, 0, 255));
	_boss = IMAGE->addImage("보스방", "images/minimap/minimap_cellIcon_boss.bmp", 30, 30, true, RGB(255, 0, 255));
	_goal = IMAGE->addImage("다음층", "images/minimap/minimap_cellIcon_goal.bmp", 30, 30, true, RGB(255, 0, 255));
	_back = IMAGE->addImage("바탕", "images/minimap/minimap_backSpriteL.bmp", 455, 317, true, RGB(255, 0, 255));

	if (_curstage < 4)
	{
		while (remainRoom >= 1 || checkNextStage() == false)
		{
			makeclear();
			makestage1((MAXSIZE - 1) / 2, (MAXSIZE + 1) / 2);
			mapSize = 11 - remainRoom;
			setNormal();
			setBossRoom();
			setstatueRoom();
			setchestRoom();
			setMORURoom();
			setShopRoom();
			setfountainMap();
			setNextRoom();
		}
		_Cmap10 = dynamic_cast<Cmap10*>(SCENE->addScene("_Cmap10", new Cmap10));
		_chestMap = dynamic_cast<chestMap*>(SCENE->addScene("_chestMap", new chestMap));
		_chestMap->setbulletmemoryLink(bm);
		_shopMap = dynamic_cast<shopMap*>(SCENE->addScene("_shopMap", new shopMap));
		_statueMap = dynamic_cast<statueMap*>(SCENE->addScene("_statueMap", new statueMap));
		_statueMap->setbulletmemoryLink(bm);
		_moruMap = dynamic_cast<moruMap*>(SCENE->addScene("_moruMap", new moruMap));
		_moruMap->setbulletmemoryLink(bm);
		_fountainMap = dynamic_cast<fountainMap*>(SCENE->addScene("_fountainMap", new fountainMap));
		_fountainMap->setbulletmemoryLink(bm);
		_stage1_Boss = dynamic_cast<stage1_Boss*>(SCENE->addScene("_stage1_Boss", new stage1_Boss(_curstage)));
		_nextStage = dynamic_cast<nextStage*>(SCENE->addScene("_nextStage", new nextStage));
			
		_Cmap10->setMonstermemoryLink(mm);
		_chestMap->setMonstermemoryLink(mm);
		_shopMap->setMonstermemoryLink(mm);
		_statueMap->setMonstermemoryLink(mm);
		_moruMap->setMonstermemoryLink(mm);
		_stage1_Boss->setMonstermemoryLink(mm);
		_nextStage->setMonstermemoryLink(mm);
		_fountainMap->setMonstermemoryLink(mm);
		



		for (int i = 0; i < MAXSIZE; i++)
		{
			for (int k = 0; k < MAXSIZE; k++)
			{
				if (stage1[i][k].mapkind != MAPKIND::NONE)
				{
					switch (stage1[i][k].mapkind)
					{
					case START:
						stage1[i][k]._motherMap = _Cmap10;
						break;
					case SHOP:
						stage1[i][k]._motherMap = _shopMap;
						break;
					case MORUROOM:
						stage1[i][k]._motherMap = _moruMap;
						break;
					case STATUEROOM:
						stage1[i][k]._motherMap = _statueMap;
						break;
					case CHESTROOM:
						stage1[i][k]._motherMap = _chestMap;
						break;
					case FOUNTAIN:
						stage1[i][k]._motherMap = _fountainMap;
						break;
					case BOSSROOM:
						stage1[i][k]._motherMap = _stage1_Boss;
						break;
					case NEXTSTAGE:
						stage1[i][k]._motherMap = _nextStage;
						break;
					}
					_mStage1.insert(pair<string, motherMap*>(stage1[i][k].sceneKey, stage1[i][k]._motherMap));
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
	}
	else
	{
		remainRoom = 2;
		while (remainRoom >= 1 )
		{
			makeclear2();
			makestage4((MAXSIZE - 1) / 2, (MAXSIZE -3) / 2);
			mapSize = 1 - remainRoom;
			setNormal();
			setBossRoom2();
		}
		_before_boss = dynamic_cast<before_Boss*>(SCENE->addScene("_before_boss", new before_Boss));
		_last_boss = dynamic_cast<last_Boss*>(SCENE->addScene("_last_boss", new last_Boss));
		_before_boss->setMonstermemoryLink(mm);
		_last_boss->setMonstermemoryLink(mm);

		for (int i = 0; i < MAXSIZE; i++)
		{
			for (int k = 0; k < MAXSIZE; k++)
			{
				if (stage1[i][k].mapkind != MAPKIND::NONE)
				{
					switch (stage1[i][k].mapkind)
					{
					case START:
						stage1[i][k]._motherMap = _before_boss;
						break;
					case BOSSROOM:
						stage1[i][k]._motherMap = _last_boss;
						break;
					}
					_mStage1.insert(pair<string, motherMap*>(stage1[i][k].sceneKey, stage1[i][k]._motherMap));
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
	}
	goNextStage = false;
	PLAYER->getDIRECTIONAddress() = DOWN;
	return S_OK;
}

void mapManager::release()
{
	SCENE->releaseLight();
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
		checkright = false;
		checkleft = false;
		checkleft = false;
		checkbottom = false;

	}
	else
	{	
		UseableDoor();
		stage1[currentIndex.x][currentIndex.y]._motherMap->setClear(true);
	}
	if (checkright)
	{
		if (currentIndex.x < 8)
		{
			currentIndex.x = currentIndex.x + 1;
			currentIndex.y = currentIndex.y;
			PLAYER->getPlayerAddress().x = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[0].Door.right + 20;
			PLAYER->getPlayerAddress().y = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[0].Door.bottom - (stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[0].Door.bottom - stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[0].Door.top) / 2;
			SCENE->changeScene(stage1[currentIndex.x][currentIndex.y].sceneKey);
			currentMap = stage1[currentIndex.x][currentIndex.y].sceneKey;
			clearbullet();

		}
	}
	if (checkleft)
	{
		if (currentIndex.x > 0)
		{
			currentIndex.x = currentIndex.x - 1;
			currentIndex.y = currentIndex.y;
			PLAYER->getPlayerAddress().x = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[2].Door.left - 20;
			PLAYER->getPlayerAddress().y = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[2].Door.bottom - (stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[2].Door.bottom - stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[2].Door.top) / 2;
			SCENE->changeScene(stage1[currentIndex.x][currentIndex.y].sceneKey);

			currentMap = stage1[currentIndex.x][currentIndex.y].sceneKey;
			clearbullet();
		}
	}
	if (checkbottom)
	{
		if (currentIndex.y <8)
		{
			currentIndex.x = currentIndex.x;
			currentIndex.y = currentIndex.y + 1;
			PLAYER->getPlayerAddress().x = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[1].Door.right - (stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[1].Door.right - stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[1].Door.left) / 2;
			PLAYER->getPlayerAddress().y = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[1].Door.bottom + 20;
			SCENE->changeScene(stage1[currentIndex.x][currentIndex.y].sceneKey);

			currentMap = stage1[currentIndex.x][currentIndex.y].sceneKey;
			clearbullet();
		}
	}
	if (checktop)
	{
		if (currentIndex.y >= 0)
		{
			currentIndex.x = currentIndex.x;
			currentIndex.y = currentIndex.y - 1;
			PLAYER->getPlayerAddress().x = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[3].Door.right - (stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[3].Door.right - stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[3].Door.left) / 2;
			PLAYER->getPlayerAddress().y = stage1[currentIndex.x][currentIndex.y]._motherMap->getDungeonDoor()[3].Door.top - 20;
			SCENE->changeScene(stage1[currentIndex.x][currentIndex.y].sceneKey);

			currentMap = stage1[currentIndex.x][currentIndex.y].sceneKey;
			clearbullet();
		}
	}
	if (checkMagicDoor)
	{
		//if (stage < 4)
		{
			checkMagicDoor = false;
			goNextStage = true;
			remainRoom = 12;
			_curstage++;
			_mStage1.clear();
			SCENE->changeScene("로딩");
		}
		/*else
		{
			checkMagicDoor = false;
			goNextStage = true;
			remainRoom = 12;
			_mStage1.clear();
			SCENE->changeScene("로딩");
		}*/
	}
	SCENE->update();
}

void mapManager::render()
{

	SCENE->render();
	if (InputManager->isToggleKey(VK_TAB))
	{
		ZORDER->UIAlphaRender(_back, ZUIFIRTH, 501, 300+160, 180, 170);
		for (size_t i = 0; i < MAXSIZE; i++)
		{
			for (size_t j = 0; j < MAXSIZE; j++)
			{
				if (stage1[i][j].mapkind == MAPKIND::START)
				{
					ZORDER->UIAlphaRender(_start, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::NORMAL)
				{
					ZORDER->UIAlphaRender(_fight, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::BOSSROOM)
				{
					ZORDER->UIAlphaRender(_boss, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::NEXTSTAGE)
				{
					ZORDER->UIAlphaRender(_goal, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::CHESTROOM)
				{
					ZORDER->UIAlphaRender(_chest, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::FOUNTAIN)
				{
					ZORDER->UIAlphaRender(_event, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::MORUROOM)
				{
					ZORDER->UIAlphaRender(_event, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::SHOP)
				{
					ZORDER->UIAlphaRender(_shop, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (stage1[i][j].mapkind == MAPKIND::STATUEROOM)
				{
					ZORDER->UIAlphaRender(_event, ZUIFIRTH, 501, 400 + i * 30 + 160, 200 + j * 30, 170);
				}
				if (currentIndex.x == i && currentIndex.y == j)
				{
					if (isAlphaDownward) {
						alpha-=7;
						if (alpha < 50) isAlphaDownward = false;
					}
					else {
						alpha+=7;
						if (alpha > 240) isAlphaDownward = true;
					}
					ZORDER->UIAlphaRender(_none, ZUIFIRTH, 501, 400 + currentIndex.x * 30 + 160, 200 + currentIndex.y * 30, alpha);
				}
			}
		}
		//for (size_t i = 0; i < MAXSIZE; i++)
		//{
		//	for (size_t j = 0; j < MAXSIZE; j++)
		//	{
		//		string str;
		//		//str = to_string((int)stage1[i][j].mapkind);
		//		//ZORDER->ZorderTextOut(str, ZMAXLAYER, 100 + 20 * i, 100 + 20 * j, RGB(0, 0, 0));
		//		str = stage1[i][j].sceneKey;
		//		ZORDER->UITextOut(str, ZUIFIRST, 300 + 70 * i, 100 + 20 * j, RGB(0, 0, 0));
		//	}
		//}

		//string str;
		//str = to_string((int)currentIndex.x);
		//ZORDER->UITextOut(str, ZMAXLAYER, 100 + 20, 300, RGB(0, 0, 0));
		//string str2;
		//str2 = to_string((int)currentIndex.y);
		//ZORDER->UITextOut(str2, ZMAXLAYER, 100 + 40, 300, RGB(0, 0, 0));
		//str = currentMap;
		//ZORDER->UITextOut(str, ZMAXLAYER, WINSIZEX / 2, WINSIZEY / 2, RGB(0, 0, 0));
	}
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
	//왼쪽문
	if (currentIndex.x-1 >= 0&& stage1[currentIndex.x - 1][currentIndex.y].mapkind != MAPKIND::NONE)
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[0].isOpen = true;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setleftDoor(true);
	}
	else
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[0].isOpen = false;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setleftDoor(false);
	}
	//위쪽문
	if (currentIndex.y-1 >=0 && stage1[currentIndex.x][currentIndex.y - 1].mapkind != MAPKIND::NONE)
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[1].isOpen = true;
		stage1[currentIndex.x][currentIndex.y]._motherMap->settopDoor(true);
	}
	else
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[1].isOpen = false;
		stage1[currentIndex.x][currentIndex.y]._motherMap->settopDoor(false);
	}
	//오른쪽문
	if (currentIndex.x+1<9 && stage1[currentIndex.x + 1][currentIndex.y].mapkind != MAPKIND::NONE)
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[2].isOpen = true;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setrightDoor(true);
	}
	else
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[2].isOpen = false;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setrightDoor(false);
	}
	//아래쪽문
	if (currentIndex.y+1 < 9 && stage1[currentIndex.x][currentIndex.y + 1].mapkind != MAPKIND::NONE)
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[3].isOpen = true;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setbotDoor(true);
	}
	else
	{
		_mStage1.find(currentMap)->second->getDungeonDoor()[3].isOpen = false;
		stage1[currentIndex.x][currentIndex.y]._motherMap->setbotDoor(false);
	}

}
void mapManager::makestage1(int i, int k)
{
	if (remainRoom <= 0 ||
		i < 0 ||
		i >= MAXSIZE ||
		k < 0 ||
		k >= MAXSIZE ||
		stage1[i][k].mapkind != MAPKIND::NONE)
		return;

	remainRoom--;
	stage1[i][k].mapkind = MAPKIND::NORMAL;
	if (!(bool)(RND->getInt(4)))
	{
		makestage1(i + 1, k);//r

	}
	if (!(bool)(RND->getInt(4)))
	{
		makestage1(i - 1, k);//l

	}
	if (!(bool)(RND->getInt(4)))
	{
		makestage1(i, k - 1);//u

	}
	if (!(bool)(RND->getInt(4)))
	{
		makestage1(i, k + 1);//d

	}

}
void mapManager::makestage4(int i, int k)
{
	if (remainRoom <= 0 ||
		i < 0 ||
		i >= MAXSIZE ||
		k < 0 ||
		k >= MAXSIZE ||
		stage1[i][k].mapkind != MAPKIND::NONE)
		return;

	remainRoom--;
	stage1[i][k].mapkind = MAPKIND::NORMAL;
}
bool mapManager::setstatueRoom()
{
	int setstatue = mapSize - 1;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setstatue--;
				if (RND->getInt(100) > 50 || setstatue == 0)
				{
					stage1[i][k] = { _statueMap,"_statueMap",STATUEROOM};
					return true;
				}
			}
		}
	}
	return false;
}
bool mapManager::setchestRoom()
{
	int setchest = mapSize - 2;
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
					return true;
				}
			}
		}
	}
	return false;
}



bool mapManager::setMORURoom()
{
	int setMORU = mapSize - 3;
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
					return true;
				}
			}
		}
	}
	return false;
}



bool mapManager::setShopRoom()
{
	int setShop = mapSize - 4;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setShop--;
				if (RND->getInt(100) > 50 || setShop == 0)
				{
					stage1[i][k] = { _shopMap,"_shopMap",SHOP };
					return true;
				}
			}
		}
	}
	return false;
}
bool mapManager::setBossRoom()
{
	int setBoss = mapSize;
	for (int k = 0; k < MAXSIZE; k++)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setBoss--;
				if (setBoss == 0)
				{
					stage1[i][k] = { _stage1_Boss,"_stage1_Boss",BOSSROOM };
					return true;
				}
			}
		}
	}
	return false;
}
bool mapManager::setBossRoom2()
{
	int setBoss = mapSize;
	for (int k = 0; k < MAXSIZE; k++)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				setBoss--;
				if (setBoss == 0)
				{
					stage1[i][k] = { _last_boss,"_last_boss",BOSSROOM };
					return true;
				}
			}
		}
	}
	return false;
}
void mapManager::setNextRoom()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind != MAPKIND::BOSSROOM)
			{
			}
			else
			{
				if (stage1[i + 1][k].mapkind == NONE)
				{
					if ((stage1[i + 2][k].mapkind == NONE &&
						stage1[i + 1][k + 1].mapkind == NONE &&
						stage1[i + 1][k - 1].mapkind == NONE))
					{
						remainNextStage--;
						stage1[i + 1][k] = { _nextStage,"_nextStage",NEXTSTAGE };
						break;
					}
				}
				if ((i > 1) && stage1[i - 1][k].mapkind == NONE)
				{
					if ((stage1[i - 2][k].mapkind == NONE &&
						stage1[i - 1][k + 1].mapkind == NONE &&
						stage1[i - 1][k - 1].mapkind == NONE))
					{
						remainNextStage--;
						stage1[i - 1][k] = { _nextStage,"_nextStage",NEXTSTAGE };
						break;
					}
				}
				if (stage1[i][k + 1].mapkind == NONE)
				{
					if ((stage1[i][k + 2].mapkind == NONE &&
						stage1[i - 1][k + 1].mapkind == NONE &&
						stage1[i + 1][k + 1].mapkind == NONE))
					{
						remainNextStage--;
						stage1[i][k + 1] = { _nextStage,"_nextStage",NEXTSTAGE };
						break;
					}
				}
				if ((k > 1) && stage1[i][k - 1].mapkind == NONE)
				{
					if ((stage1[i][k - 2].mapkind == NONE &&
						stage1[i + 1][k].mapkind == NONE &&
						stage1[i - 1][k].mapkind == NONE))
					{
						remainNextStage--;
						stage1[i][k - 1] = { _nextStage,"_nextStage",NEXTSTAGE };
						break;
					}
				}
			}
		}
	}
}

bool mapManager::setNormal()
{

	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				switch (RND->getInt(9))
				{
				case 0:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);

				}	break;
				case 1:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap2*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap2));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 2:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap3*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap3));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 3:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap4*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap4));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 4:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap5*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap5));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 5:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap6*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap6));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 6:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap7*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap7));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 7:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap8*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap8));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				case 8:
				{
					string temp;
					temp = "_Cmap"+to_string(i)+to_string(k);
					stage1[i][k].sceneKey = temp;
					stage1[i][k]._motherMap = dynamic_cast<Cmap9*>(SCENE->addScene(stage1[i][k].sceneKey, new Cmap9));
					stage1[i][k]._motherMap->setMonstermemoryLink(mm);
				}
				break;
				}
			}
		}
	}
	return true;
}

bool mapManager::checkNextStage()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == NEXTSTAGE)
			{
				if (stage1[i + 1][k].mapkind == BOSSROOM)
				{
					return true;
				}
				else if (i < 0)
				{
					return false;

					if (stage1[i - 1][k].mapkind == BOSSROOM)
					{
						return true;
					}
				}
				else if (stage1[i][k + 1].mapkind == BOSSROOM)
				{
					return true;
				}
				else if (k < 0)
				{
					return false;

					if (stage1[i][k - 1].mapkind == BOSSROOM)
					{
						return true;
					}
				}
			}
		}
	}
return false;
}

bool mapManager::setfountainMap()
{
	int fountain = mapSize - 7;
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].mapkind == MAPKIND::NORMAL)
			{
				fountain--;
				if (RND->getInt(100) > 50 || fountain == 0)
				{
					stage1[i][k] = {_fountainMap,"_fountainMap",FOUNTAIN};
					return true;
				}
			}
		}
	}
	return false;
}

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
	remainRoom = 12;
	stage1[(MAXSIZE - 1) / 2][(MAXSIZE - 1) / 2] = { _Cmap10,"_Cmap10",START};
	remainRoom--;
	SCENE->releaseLight();
}
void mapManager::makeclear2() {
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			stage1[i][k].mapkind = NONE;
			stage1[i][k].sceneKey = "";
			stage1[i][k]._motherMap = nullptr;
		}
	}
	remainRoom = 2;
	stage1[(MAXSIZE - 1) / 2][(MAXSIZE - 1) / 2] = { _before_boss,"_before_boss",START };
	remainRoom--;
	SCENE->releaseLight();
}

image* mapManager::getCurrentColMap()
{

	if (_mStage1.find(currentMap) != _mStage1.end())
	{
		return	_mStage1.find(currentMap)->second->getcolMap();
	}
	else
	{
		return nullptr;
	}
}
DungeonDoor* mapManager::getCurrentDoor()
{
	if (_mStage1.find(currentMap) != _mStage1.end())
	{
		return	_mStage1.find(currentMap)->second->getDungeonDoor();
	}
	else
	{
		return nullptr;
	}
}
MagicDoor* mapManager::getMagicDoor()
{
	if (_mStage1.find(currentMap) != _mStage1.end())
	{
		return	_mStage1.find(currentMap)->second->getMagicNextStage();
	}
	else
	{
		return nullptr;
	}
}

void mapManager::clearbullet()
{
	bm->getArwBulInstance()->getVBullet().clear();
	bm->getChargeInstance()->getVBullet().clear();
	bm->getCirBulInstance()->getVBullet().clear();
	bm->getFlwBos1Bullnstance()->getVBullet().clear();
	bm->getFlwBos2Bullnstance()->getVBullet().clear();
	bm->getFlwBos3Bullnstance()->getVBullet().clear();
	bm->getHasteInstance()->getVBullet().clear();
	bm->getHomBulInstance()->getVBullet().clear();
	bm->getIce_spearInstance()->getVBullet().clear();
	bm->getLPsnBulInstance()->getVBullet().clear();
	bm->getLucky_starInstance()->getVBullet().clear();
	bm->getMgcBulInstance()->getVBullet().clear();
	bm->getnidBulInstance()->getVBullet().clear();
	bm->getPsnBulInstance()->getVBullet().clear();
	bm->getRtnBulInstance()->getVBullet().clear();
	bm->getSlmBos1Bullnstance()->getVBullet().clear();
	bm->getTreBos1Bullnstance()->getVBullet().clear();
	bm->getTreBos2Bullnstance()->getVBullet().clear();
	bm->getTreBos3Bullnstance()->getVBullet().clear();
	bm->getTriBulInstance()->getVBullet().clear();
	bm->getWidBulInstance()->getVBullet().clear();

}