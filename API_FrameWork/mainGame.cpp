#include "framework.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);	//필요한동적할당
	_mDOL = new mainDOL;
	_mDOL->init();

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();	//해제
	SAFE_DELETE(_mDOL);

}

void mainGame::update()
{
	gameNode::update();

	_mDOL->update();
	ANIMATION->update();



	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//그림그리는곳
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//========================================================
						/*렌더링 공간*/
	_mDOL->render();



	//RECT rc = checkGameSize();
	//RECT wrc = getClRect();
	//HBRUSH brush = CreateSolidBrush(MINT);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	//RectangleMake(getMemDC(), rc);
	//SelectObject(getMemDC(), oldBrush);
	//DeleteObject(brush);
	//TCHAR str[128];
	//wsprintf(str, "%d, %d, %d, %d", rc.left, rc.top, rc.right, rc.bottom);
	//TextOut(getMemDC(), 0, 0, str, lstrlen(str));
	//wsprintf(str, "윈렉트 %d, %d, %d, %d", wrc.left, wrc.top, wrc.right, wrc.bottom);
	//TextOut(getMemDC(), 0, 20, str, lstrlen(str));


	//========================================================
	if (_showFPS) TIME->render(getMemDC());
	//백퍼버의 내용을 HDC에 그린다. (건드리지 말것)
	RECT rc = checkGameSize();
	this->getBackBuffer()->stretchRender(getHDC(), RecCenX(rc), RecCenY(rc), RecWidth(rc), RecHeight(rc));
}

RECT mainGame::checkGameSize()
{
	RECT rc = this->getClRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)GAMESIZEX / GAMESIZEY;
	float heiOverWid = (float)GAMESIZEY / GAMESIZEX;
	
	float w, h;
	//현재 가로에 맞춘 세로가 현재 창의 세로보다 크다면, 현재 세로에 맞춘다.
	(wid * heiOverWid > hei) ? w = hei * widOverHei, h = hei
		: w = wid, h = w * heiOverWid;

	int left, top, right, bottom;
	if (w < wid) {
		left = wid / 2 - w / 2;
		right = left + w;
		top = 0;
		bottom = h;
	}
	else {
		left = 0;
		right = w;
		top = hei / 2 - h / 2;
		bottom = top + h;
	}
	
	return { left, top, right, bottom };

}

