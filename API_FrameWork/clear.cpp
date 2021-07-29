#include "framework.h"
#include "clear.h"

clear::clear()
{
}

clear::~clear()
{
}

HRESULT clear::init()
{
	IMAGE->addFrameImage("클리어", "images/ponpoko/clear.bmp", 636, 64, 2, 1, true);
	return S_OK;
}

void clear::release()
{
}

void clear::update()
{
	frameCount++;
	int nowframe = IMAGE->findImage("클리어")->getFrameX();
	if (frameCount % 5 == 0) {
		nowframe++;
		if (nowframe > IMAGE->findImage("클리어")->getMaxFrameX()) {
			nowframe = 0;
		}
		IMAGE->findImage("클리어")->setFrameX(nowframe);
	}

	if (InputManager->isOnceKeyDown('R')) {
		SCENE->changeScene("시작화면");
	}
}

void clear::render()
{
	IMAGE->frameRender("클리어", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("클리어")->getFrameWidth()/2, WINSIZEY / 2 - IMAGE->findImage("클리어")->getFrameHeight()/2);
}
