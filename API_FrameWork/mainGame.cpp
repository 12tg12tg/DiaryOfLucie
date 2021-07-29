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




	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//그림그리는곳
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*렌더링 공간*/
	_mDOL->render();





	//========================================================
	if (_showFPS) TIME->render(getMemDC());
	//백퍼버의 내용을 HDC에 그린다. (건드리지 말것)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

