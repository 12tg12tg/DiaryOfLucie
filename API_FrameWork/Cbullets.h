#pragma once
#include "gameNode.h"
//////////////////////////전방선언영역/////////////////////////


//////////////////////////////////////////////////////////////
struct tagBullet
{
	image* bulletImage;
	image* bulletImage2;
	image* bulletImage3;
	animation* bulletAni;
	RECT rc;
	float x,y ;
	float fireX, fireY;
	float radius;
	float angle;
	float angle2;
	float omega;
	float rotateangle;
	float speed;
	float speed2;
	bool fire;
	int count;
	int rendercount;
	float plussize;
	bool isPlayerBullet;
	bool iscollison;
	int alpha;
	bool colPoison;
	bool checksound = true;
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

	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }

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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmReturnBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;

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
	void fire2(float x, float y, float angle, int plussize);
	void move();
	void move2();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }
	
	vector<tagBullet> &getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator &getVIBullet2() { return _viBullet2; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmWideBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
	int Maxi = 13;
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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

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

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class CmNiddleBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;

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
	void fire2(float x, float y, float angle, int plussize);
	void move();
	void move2();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	vector<tagBullet> &getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator &getVIBullet2() { return _viBullet2; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class CmLongPoisonBullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmLongPoisonBullet();
	~CmLongPoisonBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class CmSBoss1Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;
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
	void fire2(float x, float y, float angle, int plussize);
	void move();
	void move2();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	vector<tagBullet> &getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator &getVIBullet2() { return _viBullet2; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class CmFBoss1Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;
	vector<tagBullet> _vBullet3;
	vector<tagBullet>::iterator _viBullet3;
private:
	bool _isDebug;
public:
	CmFBoss1Bullet();
	~CmFBoss1Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, bool isleft, int plussize);
	void fire2(float x, float y, int plussize);
	void fire3(float x, float y, int plussize);
	void move();
	void move2();
	void move3();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);
	void removeBullet3(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	vector<tagBullet> &getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator &getVIBullet2() { return _viBullet2; }

	vector<tagBullet> &getVBullet3() { return _vBullet3; }
	vector<tagBullet>::iterator &getVIBullet3() { return _viBullet3; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmFBoss2Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;

private:
	bool _isDebug;
public:
	CmFBoss2Bullet();
	~CmFBoss2Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, int maxSize);
	void fire2(float x, float y,int plussize);

	void move();
	void move2();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);


	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	vector<tagBullet> &getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator &getVIBullet2() { return _viBullet2; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmFBoss3Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


private:
	bool _isDebug;
public:
	CmFBoss3Bullet();
	~CmFBoss3Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, int plussize);
	
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class CmTBoss1Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmTBoss1Bullet();
	~CmTBoss1Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, bool isLeft, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CmTBoss2Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmTBoss2Bullet();
	~CmTBoss2Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, bool isLeft, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class CmTBoss3Bullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	bool _isDebug;
public:
	CmTBoss3Bullet();
	~CmTBoss3Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, bool isLeft, int plussize);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet() { return _viBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};


class CpSword : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;

	vector<tagBullet> _vBullet3;
	vector<tagBullet>::iterator _viBullet3;
private:
	bool _isDebug;
public:
	CpSword();
	~CpSword();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void fire2(float x, float y, float angle,  int plussize);
	void fire3(float x, float y, float angle, int plussize);
	void move();
	void move2();
	void move3();
	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);
	void removeBullet3(int arrNum);

	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }

	vector<tagBullet>& getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator& getVIBullet2() { return _viBullet2; }

	vector<tagBullet>& getVBullet3() { return _vBullet3; }
	vector<tagBullet>::iterator& getVIBullet3() { return _viBullet3; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CpSkil_LuckyStar : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


private:
	bool _isDebug;
public:
	CpSkil_LuckyStar();
	~CpSkil_LuckyStar();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();

	void removeBullet(int arrNum);

	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CpSkil_Ice_spear : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vBullet2;
	vector<tagBullet>::iterator _viBullet2;




private:
	bool _isDebug;
public:
	CpSkil_Ice_spear();
	~CpSkil_Ice_spear();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void fire2(float x, float y, float angle, int plussize);
	void move();
	void move2();

	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);

	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }
	vector<tagBullet>& getVBullet2() { return _vBullet2; }
	vector<tagBullet>::iterator& getVIBullet2() { return _viBullet2; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CpSkil_Haste : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


private:
	bool _isDebug;
public:
	CpSkil_Haste();
	~CpSkil_Haste();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();

	void removeBullet(int arrNum);
	
	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

class CpSkil_Charge : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


private:
	bool _isDebug;
	float _range;
public:
	CpSkil_Charge();
	~CpSkil_Charge();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, int plussize);
	void move();

	void removeBullet(int arrNum);

	vector<tagBullet>& getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator& getVIBullet() { return _viBullet; }


	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};









