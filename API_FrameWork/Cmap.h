#pragma once
#include"gameNode.h"
#include"motherMap.h"
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


};
class shopMap : public motherMap
{
private:
	
public:
	shopMap();
	~shopMap();
	HRESULT init();
	void release();
	void update();
	void render();


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
};
class stage1_Boss : public motherMap
{
private:

public:
	stage1_Boss();
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

























