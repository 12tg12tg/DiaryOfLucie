#pragma once
#include "gameNode.h"

enum class MOVESTATE
{
	RIGHTUPIDLE,
	RIGHTIDLE,
	RIGHTDOWNIDLE,
	DOWNIDLE,
	LEFTDOWNIDLE,
	LEFTIDLE,
	LEFTUPIDLE,
	UPIDLE,//
	RIGHTUPWALK,
	RIGHTWALK,
	RIGHTDOWNWALK,
	DOWNWALK,
	LEFTDOWNWALK,
	LEFTWALK,
	LEFTUPWALK,
	UPWALK,
	RIGHTUPRUN,
	RIGHTRUN,
	RIGHTDOWNRUN,
	DOWNRUN,
	LEFTDOWNRUN,
	LEFTRUN,
	LEFTUPRUN,
	UPRUN
};

enum WEAPONKIND
{
	NULLWEAPON,
	SWORD,
	BOW,
	STAFF
};

struct Player
{
	RECT playerRect;
	bool isATT;
	int HealthPoint;
	int ManaPoint;
};
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////

class Cplayer : public gameNode
{
private:

private:
	bool _isDebug;
public:
	Cplayer();
	~Cplayer();

	HRESULT init();
	HRESULT init(int setX,int setY);
	void release();
	void update();
	void render();



	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};