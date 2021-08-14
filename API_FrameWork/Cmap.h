#pragma once
#include"gameNode.h"

struct MAP {
	int startX;
	int startY;
	
	int monsterNum;
	int monsterX;
	int monsterY;

	
};
class Cmap : public gameNode
{
private:
	
	bool _isDebug;
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;

public:
	Cmap();
	~Cmap();
	HRESULT init();
	void release();
	void update();
	void render();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	
};

class Cmap2 : public gameNode
{
private:
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
	bool _isDebug;
public:
	Cmap2();
	~Cmap2();
	HRESULT init();
	void release();
	void update();
	void render();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class Cmap3 : public gameNode
{
private:
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
	bool _isDebug;
public:
	Cmap3();
	~Cmap3();
	HRESULT init();
	void release();
	void update();
	void render();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class Cmap4 : public gameNode
{
private:
	bool _isDebug;
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
public:
	Cmap4();
	~Cmap4();
	HRESULT init();
	void release();
	void update();
	void render();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class Cmap5 : public gameNode
{
private:
	bool _isDebug ;
	RECT _bottomDoor;
	RECT _topDoor;
	RECT _rightDoor;
	RECT _leftDoor;
public:
	Cmap5();
	~Cmap5();
	HRESULT init();
	void release();
	void update();
	void render();
	
};


