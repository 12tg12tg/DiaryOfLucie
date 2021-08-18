#pragma once
#include "gameNode.h"
struct tagcoin {

	image* coinImage;
	animation* coinAni;
	RECT rc;
	float angle;
	int howmuch;
	float x, y;
	float realX, realY;
	bool isCollison;
};
class goldCoin : public gameNode
{
private:
	vector<tagcoin> _vCoin;
	vector<tagcoin>::iterator _viCoin;
private:
	bool _isDebug;
public:
	goldCoin();
	~goldCoin();

	HRESULT init();
	void release();
	void update();
	void render();

	void drop(float x, float y);
	void move();
	void removecoin(int arrNum);

	vector<tagcoin>& getVCoin() { return _vCoin; }
	vector<tagcoin>::iterator& getVICoin() { return _viCoin; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class silverCoin : public gameNode
{
private:
	vector<tagcoin> _vCoin;
	vector<tagcoin>::iterator _viCoin;
private:
	bool _isDebug;
public:
	silverCoin();
	~silverCoin();

	HRESULT init();
	void release();
	void update();
	void render();

	void drop(float x, float y);
	void move();
	void removecoin(int arrNum);

	vector<tagcoin>& getVCoin() { return _vCoin; }
	vector<tagcoin>::iterator& getVICoin() { return _viCoin; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
class bronzeCoin : public gameNode
{
private:
	vector<tagcoin> _vCoin;
	vector<tagcoin>::iterator _viCoin;
private:
	bool _isDebug;
public:
	bronzeCoin();
	~bronzeCoin();

	HRESULT init();
	void release();
	void update();
	void render();

	void drop(float x, float y);
	void move();
	void removecoin(int arrNum);

	vector<tagcoin>& getVCoin() { return _vCoin; }
	vector<tagcoin>::iterator& getVICoin() { return _viCoin; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
