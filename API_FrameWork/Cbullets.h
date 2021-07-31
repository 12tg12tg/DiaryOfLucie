#pragma once
#include "gameNode.h"
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float angle;
	float angle2;
	float speed;
	bool fire;
	int count;
	bool isPlayerBullet;
};

class CpMagicBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;



private:
	bool _isDebug;
public:
	CpMagicBullet();
	~CpMagicBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CpArrowBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;


private:
	bool _isDebug;
public:
	CpArrowBullet();
	~CpArrowBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class CmTripleBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	bool _isDebug;
public:
	CmTripleBullet();
	~CmTripleBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmCircleBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmCircleBullet();
	~CmCircleBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmReturnBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmReturnBullet();
	~CmReturnBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmWideBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmWideBullet();
	~CmWideBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmHomingBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmHomingBullet();
	~CmHomingBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);
	void move();
	void removeBullet(int arrNum);
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};