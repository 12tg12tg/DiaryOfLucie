#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
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
<<<<<<< HEAD

		PLAYER->setIsDebug(_isDebug);
		PLAYERDATA->setIsDebug(_isDebug);
=======
		_mapm->setIsDebug(_isDebug);
>>>>>>> 370b858d67108523dd88b6033a8562da6a2674e5
	}
};

