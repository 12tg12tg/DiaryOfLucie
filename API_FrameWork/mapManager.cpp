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

	_Cmap1->setMonstermemoryLink(mm);
	_Cmap2->setMonstermemoryLink(mm);
	_Cmap3->setMonstermemoryLink(mm);
	_Cmap4->setMonstermemoryLink(mm);
	_Cmap5->setMonstermemoryLink(mm);

	MAP stage1[2][2] = { {{nullptr,"",false,true,NONE,},{_Cmap5,"_Cmap5",false,true,NONE}},{{_Cmap2,"_Cmap2",false,true,START},{_Cmap3,"_Cmap3",false,true,NONE}} };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
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
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			
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
		if (vMonster.size() != 0)
		{
			rightdoor_open = false;
			leftdoor_open = false;
			topdoor_open = false;
			bottomdoor_open = false;
		}
	}
}
