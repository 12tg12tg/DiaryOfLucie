#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
#define RATIO 1.5
#define CAMERASIZEX WINSIZEX/RATIO
#define CAMERASIZEY WINSIZEY/RATIO
class mainDOL : public gameNode
{
//DOL ���� �Ŵ��� �ν��Ͻ�
private:
	bulletManager*		_bm;
	collisionManager*	_cm;
	monsterManager*		_mm;
	mapManager*			_mapm;
//-----------------------------
//������ �귻ġ �ν��Ͻ�
private:
	









//-----------------------------
//����׸�� ����
private:
	bool _isDebug;
//-----------------------------
public:
	mainDOL();
	~mainDOL();

	HRESULT init();
	void release();
	void update();
	void render();

	POINT getCamMouse() {
		POINT newPt;
		newPt.x = (m_ptMouse.x / RATIO) + CAMERA->getRect().left;
		newPt.y = (m_ptMouse.y / RATIO) + CAMERA->getRect().top;
		return newPt;
	}
	void setIsdebug(bool isDebug) {
		_isDebug = isDebug;
		_bm->setIsDebug(_isDebug);
		_cm->setIsDebug(_isDebug);
		_mm->setIsDebug(_isDebug);
		_mapm->setIsDebug(_isDebug);
		BUTTON->setIsDebug(_isDebug);	
		PLAYER->setIsDebug(_isDebug);
		PLAYERDATA->setIsDebug(_isDebug);
	}
};

