#pragma once
#include "object.h"
class fountain : public object
{
private:
//	RECT _hitRc;
//	RECT _footRc;
//	RECT _interRc;
//	image* _img;
//	float _x, _y;
//	int _hp;
//	animation* _ani;

	float _neverChangeX;
	float _neverChangeY;
	BYTE boxAlpha;

//	bool _isDebug;
public:
	fountain();
	~fountain();

	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();

	void setBox();
};

