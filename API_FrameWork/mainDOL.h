#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
#include "DOL_Title.h"

#include "shop.h"

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
	



	shop* _sp;

	DOL_Title* _DOLtitle;
	bool gameStart;


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

	void gameInit();

	void setIsdebug(bool isDebug) {
		_isDebug = isDebug;
		if (!gameStart) {
			BUTTON->setIsDebug(_isDebug);
		}
		if (gameStart) {
			_bm->setIsDebug(_isDebug);
			_cm->setIsDebug(_isDebug);
			_mm->setIsDebug(_isDebug);
			_mapm->setIsDebug(_isDebug);
			BUTTON->setIsDebug(_isDebug);
			PLAYER->setIsDebug(_isDebug);
			PLAYERDATA->setIsDebug(_isDebug);

			_sp->setIsDebug(_isDebug);
		}
	}
};

