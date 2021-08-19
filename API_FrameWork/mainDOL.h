#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
#include "DOL_Title.h"
#include "loading.h"

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
	DOL_Title* _DOLtitle;
	loading* _loading;
	bool canUpdate;

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
		if (!canUpdate) {
			BUTTON->setIsDebug(_isDebug);
		}
		if (canUpdate) {
			_bm->setIsDebug(_isDebug);
			_cm->setIsDebug(_isDebug);
			_mm->setIsDebug(_isDebug);
			_mapm->setIsDebug(_isDebug);
			BUTTON->setIsDebug(_isDebug);
			PLAYER->setIsDebug(_isDebug);
			PLAYERDATA->setIsDebug(_isDebug);
			ITEM->setIsDebug(_isDebug);
		}
	}
};

