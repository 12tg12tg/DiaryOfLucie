#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"

#include "shop.h"

class mainDOL : public gameNode
{
//DOL 관련 매니저 인스턴스
private:
	bulletManager*		_bm;
	collisionManager*	_cm;
	monsterManager*		_mm;
	mapManager*			_mapm;
//-----------------------------
//각자의 브렌치 인스턴스
private:
	



	shop* _sp;





//-----------------------------
//디버그모드 관련
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
		_mapm->setIsDebug(_isDebug);
		BUTTON->setIsDebug(_isDebug);	
		PLAYER->setIsDebug(_isDebug);
		PLAYERDATA->setIsDebug(_isDebug);

		_sp->setIsDebug(_isDebug);
	}
};

