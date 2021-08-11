#pragma once
#include"monster.h"
	enum DOORSTATE
	{
		OPEN,
		CLOSE
	};
	enum DOOR
	{
		LEFT_DOOR,
		RIGHT_DOOR,
		UP_DOOR,
		DOWN_DOOR,
	};
	enum MONSTERKIND
	{
		Csnaby,
		Cslime,
		Cmushman,
		Cmushman_mushroom,
		Cfairy,
		Cflime,
		Cboss_slime,
		Cboss_flime,
		Cboss_mushmam,
		Cyggdrasil,
		NONE
	};
	enum MAPKIND
	{
		NORMAL,
		TRESUREROOM,
		BOSSROOM,
		NEXSTAGE,
		EVENTMAP,
		SHOP
	};
class Cmap
{
private:
	RECT RightDoor;
	RECT LeftDoor;
	RECT UpDoor;
	RECT DownDoor;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	
};

