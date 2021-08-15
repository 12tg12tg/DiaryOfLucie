#pragma once
#include "object.h"
class statue : public object
{
private:
	RECT _hitRc;
	RECT _hitRc2;
	RECT _footRc;
	RECT _footRc2;
	image* _img;
	image* _img2;
	float _x, _y;
	float _x2, _y2;
	animation* _ani;
	animation* _ani2;
	int _neverChangeX;
	int _neverChangeY;
	int _neverChangeX2;
	int _neverChangeY2;

	int plusIndex;
	int plusIndex2;

	bool isHit;

	bool _isDebug;
public:
	statue();
	~statue();

	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	virtual void playerCollision();
	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();
};


