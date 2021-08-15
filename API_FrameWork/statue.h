#pragma once
#include "object.h"
class statue_red : public object
{
private:
//	RECT _hitRc;
//	RECT _footRc;
//	RECT _interRc;
//	image* _img;
//	float _x, _y;
//	int _hp;
//	animation* _ani;





//	bool _isDebug;
public:
	statue_red();
	~statue_red();

	virtual HRESULT add();
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	virtual void playerCollision();
	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();
};


