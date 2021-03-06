#pragma once
#include "object.h"
#include "motherMap.h"
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
	motherMap* _motherm;
//	bool _isDebug;
public:
	fountain();
	~fountain();

	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	virtual void playerCollision();
	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();

	void setBox();
	void setmotherMapMemoryLink(motherMap* motherMap) { _motherm = motherMap; }
};

