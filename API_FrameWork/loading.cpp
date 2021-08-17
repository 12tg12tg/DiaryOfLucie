#include "framework.h"
#include "loading.h"
#include "mapManager.h"

loading::loading(mapManager* mm) : mm(mm)
{
	bg = IMAGE->addImage("�ε����", WINSIZEX, WINSIZEY);
	loadingbar = IMAGE->addFrameImage("�ε���", "images/title/loading.bmp", 420, 437, 1, 4, true);
	ANIMATION->addAnimation("�ε��ִ�", "�ε���", 0, 3, 6, false, true);
	ANIMATION->start("�ε��ִ�");
}

loading::~loading()
{
}

HRESULT loading::init()
{
	barX = WINSIZEX - loadingbar->getFrameWidth() - 100;
	barY = WINSIZEY - loadingbar->getFrameHeight() - 100;
	loadingCount = 0;
	_isLodingDone = false;
	loadingTime = 450 + RND->getInt(50);
	return S_OK;
}

void loading::release()
{
}

void loading::update()
{
	loadingCount++;
	if (loadingCount == 450) {
		_isLodingDone = true;
		mm->init();
		CAMERA->FadeInit(100, FADE_IN);
		CAMERA->FadeStart();
		//�ʸŴ����� init�Ǹ� ���������迭�� �籸����. �װ����� �˾Ƽ� changeScene��.
	}
	else {
		if(loadingCount%5==0)
			barX++;
	}
}

void loading::render()
{
	ZORDER->ZorderRender(bg, ZFLOORMAP, 0, 0, 0);
	ZORDER->ZorderAniRender(loadingbar, ZUNIT, barY, barX, barY, ANIMATION->findAnimation("�ε��ִ�"));
	ZORDER->ZorderTotalRender(getMemDC());
}
