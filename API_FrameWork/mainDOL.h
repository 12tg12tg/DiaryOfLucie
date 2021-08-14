#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
class mainDOL : public gameNode
{
//DOL °ü·Ã ¸Å´ÏÀú ÀÎ½ºÅÏ½º
private:
	bulletManager*		_bm;
	collisionManager*	_cm;
	monsterManager*		_mm;
	mapManager*			_mapm;
//-----------------------------
//°¢ÀÚÀÇ ºê·»Ä¡ ÀÎ½ºÅÏ½º
private:










//-----------------------------
//µð¹ö±×¸ðµå °ü·Ã
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
		BUTTON->setIsDebug(_isDebug);
>>>>>>> origin/ì˜ˆê· ìž‘ì—…
	}
};

