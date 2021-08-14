#include "framework.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
	_Cmap1 = dynamic_cast<Cmap*>(SCENE->addScene("_Cmap1", new Cmap));
	_Cmap2 = dynamic_cast<Cmap2*>(SCENE->addScene("_Cmap2", new Cmap2));
	_Cmap3 = dynamic_cast<Cmap3*>(SCENE->addScene("_Cmap3", new Cmap3));
	_Cmap4 = dynamic_cast<Cmap4*>(SCENE->addScene("_Cmap4", new Cmap4));
	_Cmap5 = dynamic_cast<Cmap5*>(SCENE->addScene("_Cmap5", new Cmap5));

	MAP stage1[2][2] = { {{nullptr,"",false,true,NONE},{_Cmap5,"_Cmap5",false,true,NONE}},{{_Cmap2,"_Cmap2",false,true,START},{_Cmap3,"_Cmap3",false,true,NONE}} };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			if (stage1[i][k].mapkind != MAPKIND::NONE)
			{
				_mStage1.insert(pair<string, motherMap*>(stage1[i][k].sceneKey, stage1[i][k]._motherMap));
				if (stage1[i][k].mapkind == MAPKIND::START)
				{
					//맵을 다시돌면서 값을 넣어줌
					currentMap = stage1[i][k].sceneKey;
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
	SCENE->update();
}

void mapManager::render()
{
	SCENE->render();
	
}
