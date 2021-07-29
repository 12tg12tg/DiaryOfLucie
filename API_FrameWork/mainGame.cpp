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



	return S_OK;
}

void mainGame::release()
{
	gameNode::release();	//해제


}

void mainGame::update()
{
	gameNode::update();






	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//그림그리는곳
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*렌더링 공간*/






	//========================================================
	if (showFPS) TIME->render(getMemDC());
	//백퍼버의 내용을 HDC에 그린다. (건드리지 말것)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

