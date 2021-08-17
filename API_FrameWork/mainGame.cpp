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
	ANIMATION->update();



	setIsDebug();
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//�׸��׸��°�
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//========================================================
						/*������ ����*/
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
	//wsprintf(str, "����Ʈ %d, %d, %d, %d", wrc.left, wrc.top, wrc.right, wrc.bottom);
	//TextOut(getMemDC(), 0, 20, str, lstrlen(str));


	//========================================================
	if (_showFPS) TIME->render(getMemDC());
	//���۹��� ������ HDC�� �׸���. (�ǵ帮�� ����)
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
	//���� ���ο� ���� ���ΰ� ���� â�� ���κ��� ũ�ٸ�, ���� ���ο� �����.
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

