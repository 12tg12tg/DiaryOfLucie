#pragma once
#include "gameNode.h"
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////
struct tagBullet
{
	image* bulletImage;
	image* bulletImage2;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float angle;
	float angle2;
	float rotateangle;
	float speed;
	bool fire;
	int count;
	int plussize;
	bool isPlayerBullet;
	bool iscollison;
	int alpha;
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

	void fire(float x, float y, float angle,int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

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

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmPoisonBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmPoisonBullet();
	~CmPoisonBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmWarningBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmWarningBullet();
	~CmWarningBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmNiddleBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmNiddleBullet();
	~CmNiddleBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmSBoss1Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmSBoss1Bullet();
	~CmSBoss1Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};