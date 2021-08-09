#pragma once
#include "gameNode.h"
#include "Cmonsters.h"
class Cplayer;
class bulletManager;
class monsterManager : public gameNode
{
private:
	Cplayer* _py;
	bulletManager* _bm;
private:
	Csnaby* _snaby;
	Cslime* _slime;
	Cmushman* _mushman;
	Cmushman_mushroom* _mushman_mushroom;
	Cfairy* _fairy;
	Cflime* _flime;
	Cboss_slime* _bossSlime;
	Csemiboss_slime* _semiBossSlime;
	Cboss_flime* _bossflime;
	Cboss_mushmam* _bossMushmam;
	Cmushmam_mushroom_G* _mushmam_mushroom_G;
	Cmushmam_mushroom_P* _mushmam_mushroom_P;
	Cmushmam_mushroom_B* _mushmam_mushroom_B;
	Cyggdrasil* _yggdrasil;
	Cyggdrasil_bomb* _yggdrasil_bomb;

private:
	bool _isDebug;
public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();



	void setPlayerMemoryLink(Cplayer* py) { _py = py; }
	void setBulletManagerMemoryLink(bulletManager* bm) { _bm = bm; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_snaby->setIsDebug(_isDebug);
		_slime->setIsDebug(_isDebug);
		_mushman->setIsDebug(_isDebug);
		_mushman_mushroom->setIsDebug(_isDebug);
		_fairy->setIsDebug(_isDebug);
		_flime->setIsDebug(_isDebug);
		_bossSlime->setIsDebug(_isDebug);
		_semiBossSlime->setIsDebug(_isDebug);
		_bossflime->setIsDebug(_isDebug);
		_bossMushmam->setIsDebug(_isDebug);
		_mushmam_mushroom_G->setIsDebug(_isDebug);
		_mushmam_mushroom_P->setIsDebug(_isDebug);
		_mushmam_mushroom_B->setIsDebug(_isDebug);
		_yggdrasil->setIsDebug(_isDebug);
		_yggdrasil_bomb->setIsDebug(_isDebug);
	}
};

