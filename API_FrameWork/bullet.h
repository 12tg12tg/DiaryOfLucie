#pragma once
#include "gameNode.h"

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float angle;
	float speed;
	bool fire;
	int count;
	bool isHit;
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();

	void removeMissile(int arrNum);
	vector<tagBullet> getVBullettoday() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullettoday() { return _viBullet; }

	//vector<tagBullet>* getVbullet() { return &_vBullet; }
	vector<tagBullet> getVbullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIbullet() { return _viBullet; }
};

class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;

public:
	missile();
	~missile();
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();

	vector<tagBullet>* getVmissile() { return &_vBullet; }
};

class nuclear : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	int _missileMax;
	float _range;


public:
	nuclear();
	~nuclear();

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();

	void removeNuclear(int arrNum);

	vector<tagBullet>* getVnucler() { return &_vBullet; }
	vector<tagBullet>::iterator getVIVnuclear() { return _viBullet; }
};
