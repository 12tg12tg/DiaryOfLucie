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
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	
	image* getcolMap() { return _collisionMap; }
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
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	image* getcolMap() { return _collisionMap; }
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
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	image* getcolMap() { return _collisionMap; }
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
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	image* getcolMap() { return _collisionMap; }
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
	image* getcolMap() { return _collisionMap; }
	
};


