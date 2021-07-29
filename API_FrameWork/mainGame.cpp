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



	return S_OK;
}

void mainGame::release()
{
	gameNode::release();	//����


}

void mainGame::update()
{
	gameNode::update();






	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//�׸��׸��°�
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*������ ����*/






	//========================================================
	if (showFPS) TIME->render(getMemDC());
	//���۹��� ������ HDC�� �׸���. (�ǵ帮�� ����)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

