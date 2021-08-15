#pragma once
#include "gameNode.h"
#include "Cmonsters.h"
//테에에에에에스으으으으응으으으트
#include "fountain.h"
#include "moru.h"
class Cplayer;
class bulletManager;
class monsterManager : public gameNode
{
private:
	Cplayer* _py;
	bulletManager* _bm;
private:
	Csnaby*					_snaby;
	Cslime*					_slime;
	Cmushman*				_mushman;
	Cmushman_mushroom*		_mushman_mushroom;
	Cfairy*					_fairy;
	Cflime*					_flime;
	Cboss_slime*			_bossSlime;
	Csemiboss_slime*		_semiBossSlime;
	Cboss_flime*			_bossflime;
	Cboss_mushmam*			_bossMushmam;
	Cmushmam_mushroom_G*	_mushmam_mushroom_G;
	Cmushmam_mushroom_P*	_mushmam_mushroom_P;
	Cmushmam_mushroom_B*	_mushmam_mushroom_B;
	Cyggdrasil*				_yggdrasil;
	Cyggdrasil_bomb*		_yggdrasil_bomb;

	fountain* _ft;
	moru* _mr;

private:
	bool _isDebug;
public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//몬스터 인스턴스 getter
	Csnaby* getSnaby() { return _snaby; }
	Cslime* getSlime() { return _slime; }
	Cmushman* getMushman() { return _mushman; }
	Cmushman_mushroom* getMushman_Mushroom() { return _mushman_mushroom; }
	Cfairy* getFairy() { return _fairy; }
	Cflime* getFlime() { return _flime; }
	Cboss_slime* getBoss_Slime() { return _bossSlime; }
	Csemiboss_slime* getSemiBoss_Slime() { return _semiBossSlime; }
	Cboss_flime* getBoss_Flime() { return _bossflime; }
	Cboss_mushmam* getBoss_Mushmam() { return _bossMushmam; }
	Cmushmam_mushroom_G* getBoss_Mushroom_G() { return _mushmam_mushroom_G; }
	Cmushmam_mushroom_P* getBoss_Mushroom_P() { return _mushmam_mushroom_P; }
	Cmushmam_mushroom_B* getBoss_Mushroom_B() { return _mushmam_mushroom_B; }
	Cyggdrasil* getYggdrasil() { return _yggdrasil; }
	Cyggdrasil_bomb* getYggdrasil_Bomb() { return _yggdrasil_bomb; }

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

