#include "framework.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
	SCENE->addScene("_Cmap1", new Cmap);
	SCENE->addScene("_Cmap2", new Cmap2);
	SCENE->addScene("_Cmap3", new Cmap3);
	SCENE->addScene("_Cmap4", new Cmap4);
	SCENE->addScene("_Cmap5", new Cmap5);


	_bottomDoor = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 200, 200);
	_topDoor = RectMakeCenter(WINSIZEX / 2, 0, 200, 200);
	_rightDoor = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 200, 200);
	_leftDoor = RectMakeCenter(0, WINSIZEY / 2, 200, 200);
	
	return S_OK;
}

void mapManager::release()
{
	SCENE->release();
}

void mapManager::update()
{	
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (stage1[i][k].positionNum == 0)
			{
				SCENE->changeScene("_Cmap1");
			}
			else if (stage1[i][k].positionNum == 1)
			{
				SCENE->changeScene("_Cmap2");
			}
			else if (stage1[i][k].positionNum == 2)
			{
				SCENE->changeScene("_Cmap3");
			}
			else if (stage1[i][k].positionNum == 3)
			{
				SCENE->changeScene("_Cmap4");
			}
			else if (stage1[i][k].positionNum == 4)
			{
				SCENE->changeScene("_Cmap5");
			}
		}
	}
	SCENE->update();
}

void mapManager::render()
{
	SCENE->render();
	RectangleMake(getMemDC(), _rightDoor);
}
