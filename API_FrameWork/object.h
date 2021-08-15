#pragma once
#include "gameNode.h"
class object : public gameNode
{
protected:
	RECT _hitRc;
	RECT _footRc;
	RECT _interRc;
	image* _img;
	float _x, _y;
	int _hp;
	animation* _ani;





	bool _isDebug;
public:
	object();
	~object();

	virtual HRESULT add();
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();
	
	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();


};

