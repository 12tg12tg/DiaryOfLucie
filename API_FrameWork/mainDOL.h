#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
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

	void setIsdebug(bool isDebug) {
		_isDebug = isDebug;
		_bm->setIsDebug(_isDebug);
		_cm->setIsDebug(_isDebug);
		_mm->setIsDebug(_isDebug);
		
	}
};

