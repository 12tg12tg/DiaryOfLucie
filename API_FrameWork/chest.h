#pragma once
#include "object.h"
#include "Item.h"
class chest : public object
{
private:
	//RECT _hitRc;
	//RECT _footRc;
	//RECT _interRc;
	//image* _img;
	//float _x, _y;
	//int _hp;
	//animation* _ani;

	int _openCount;
	bool _isOpen;
	bool _istake = false;
	int currentItemIndex;
	int _curBox;
	ITEMDATA itemdata[2];
	

	

	//bool _isDebug;
public:
	chest();
	~chest();

	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	void playerInterCollision();
	virtual void playerCollision();
	virtual void bulletCollision(bulletManager* bm);
	virtual void afterHit();
	virtual void giveFrame();
	virtual void takeItem();
	virtual ITEMDATA getItemData() { return itemdata[0]; }
};

