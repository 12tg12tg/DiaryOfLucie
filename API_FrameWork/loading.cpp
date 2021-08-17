#include "framework.h"
#include "loading.h"
#include "mapManager.h"

loading::loading(mapManager* mm) : mm(mm)
{
	bg = IMAGE->addImage("로딩배경", WINSIZEX, WINSIZEY);
	loadingbar = IMAGE->addFrameImage("로딩바", "images/title/loading.bmp", 420, 437, 1, 4, true);
	ANIMATION->addAnimation("로딩애니", "로딩바", 0, 3, 6, false, true);
	ANIMATION->start("로딩애니");
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
		//맵매니저가 init되면 스테이지배열을 재구성함. 그곳에서 알아서 changeScene됨.
	}
	else {
		if(loadingCount%5==0)
			barX++;
	}
}

void loading::render()
{
	ZORDER->ZorderRender(bg, ZFLOORMAP, 0, 0, 0);
	ZORDER->ZorderAniRender(loadingbar, ZUNIT, barY, barX, barY, ANIMATION->findAnimation("로딩애니"));
	ZORDER->ZorderTotalRender(getMemDC());
}
