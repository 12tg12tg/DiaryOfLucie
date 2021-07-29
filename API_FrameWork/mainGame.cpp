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
	gameNode::init(true);	//�ʿ��ѵ����Ҵ�
	_mDOL = new mainDOL;
	_mDOL->init();

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();	//����
	SAFE_DELETE(_mDOL);

}

void mainGame::update()
{
	gameNode::update();

	_mDOL->update();




	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//�׸��׸��°�
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*������ ����*/
	_mDOL->render();





	//========================================================
	if (_showFPS) TIME->render(getMemDC());
	//���۹��� ������ HDC�� �׸���. (�ǵ帮�� ����)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

