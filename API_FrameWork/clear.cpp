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
	IMAGE->addFrameImage("Ŭ����", "images/ponpoko/clear.bmp", 636, 64, 2, 1, true);
	return S_OK;
}

void clear::release()
{
}

void clear::update()
{
	frameCount++;
	int nowframe = IMAGE->findImage("Ŭ����")->getFrameX();
	if (frameCount % 5 == 0) {
		nowframe++;
		if (nowframe > IMAGE->findImage("Ŭ����")->getMaxFrameX()) {
			nowframe = 0;
		}
		IMAGE->findImage("Ŭ����")->setFrameX(nowframe);
	}

	if (InputManager->isOnceKeyDown('R')) {
		SCENE->changeScene("����ȭ��");
	}
}

void clear::render()
{
	IMAGE->frameRender("Ŭ����", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("Ŭ����")->getFrameWidth()/2, WINSIZEY / 2 - IMAGE->findImage("Ŭ����")->getFrameHeight()/2);
}
