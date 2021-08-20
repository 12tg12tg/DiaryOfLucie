#pragma once
#include"gameNode.h"
#include"motherMap.h"
#include"progressBar.h"
class Cmap : public motherMap
{
private:

public:
	Cmap();
	~Cmap();
	HRESULT init();
	void release();
	void update();
	void render();



};

class Cmap2 : public motherMap
{
private:

public:
	Cmap2();
	~Cmap2();
	HRESULT init();
	void release();
	void update();
	void render();


};


class Cmap3 : public motherMap
{
private:

public:
	Cmap3();
	~Cmap3();
	HRESULT init();
	void release();
	void update();
	void render();


};


class Cmap4 : public motherMap
{
private:

public:
	Cmap4();
	~Cmap4();
	HRESULT init();
	void release();
	void update();
	void render();


};


class Cmap5 : public motherMap
{
private:

public:
	Cmap5();
	~Cmap5();
	HRESULT init();
	void release();
	void update();
	void render();


};

class Cmap6 : public motherMap
{
private:

public:
	Cmap6();
	~Cmap6();
	HRESULT init();
	void release();
	void update();
	void render();


};
class Cmap7 : public motherMap
{
private:

public:
	Cmap7();
	~Cmap7();
	HRESULT init();
	void release();
	void update();
	void render();


};

class Cmap8 : public motherMap
{
private:

public:
	Cmap8();
	~Cmap8();
	HRESULT init();
	void release();
	void update();
	void render();


};

class Cmap9 : public motherMap
{
private:

public:
	Cmap9();
	~Cmap9();
	HRESULT init();
	void release();
	void update();
	void render();


};

class Cmap10 : public motherMap
{
private:

public:
	Cmap10();
	~Cmap10();
	HRESULT init();
	void release();
	void update();
	void render();


};
class chestMap : public motherMap
{
private:
	chest* _chest;
public:
	chestMap();
	~chestMap();
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setIsDebug(bool isDebug) {
		_isDebug = isDebug; 
		_chest->setIsDebug(_isDebug);
	}
};
class shopMap : public motherMap
{
private:
	shop* _shop;
public:
	shopMap();
	~shopMap();
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setIsDebug(bool isDebug)	{
		_isDebug = isDebug;
		_shop->setIsDebug(_isDebug);
	}
};
class statueMap : public motherMap
{
private:
	statue* _statue;
public:
	statueMap();
	~statueMap();
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_statue->setIsDebug(_isDebug);
	}
};


class moruMap : public motherMap
{
private:
	moru* _moru;
public:
	moruMap();
	~moruMap();
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_moru->setIsDebug(_isDebug);
	}
};

class fountainMap : public motherMap
{
private:
	fountain* _fountain;
public:
	fountainMap();
	~fountainMap();
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_fountain->setIsDebug(_isDebug);
	}
};

class stage1_Boss : public motherMap
{
private:
	int count;
	BYTE alpha;
	int totalhp;
	int currenthp;
	bool isShake;
	int shaketime;
	bool changePivot;
	progressBar* hpbar;
public:
	stage1_Boss(int currentboss);
	~stage1_Boss();
	HRESULT init();
	void release();
	void update();
	void render();


};
class nextStage : public motherMap
{
private:
	
public:
	nextStage();
	~nextStage();
	HRESULT init();
	void release();
	void update();
	void render();

};

class before_Boss : public motherMap
{
private:

public:
	before_Boss();
	~before_Boss();
	HRESULT init();
	void release();
	void update();
	void render();

};

class last_Boss : public motherMap
{
private:
	int count;
	int imgCount;
	BYTE alpha;
	int totalhp;
	int currenthp;
	bool isShake;
	int shaketime;
	bool changePivot;
	bool isWait;
	progressBar* hpbar;
	RECT icerc;
public:
	last_Boss();
	~last_Boss();
	HRESULT init();
	void release();
	void update();
	void render();

};

class newStage : public motherMap
{
private:

public:
	newStage();
	~newStage();
	HRESULT init();
	void release();
	void update();
	void render();
};
























