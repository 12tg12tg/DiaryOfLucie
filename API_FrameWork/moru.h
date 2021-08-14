#pragma once
#include "object.h"
class bulletManager;
class moru : public object
{
private:
	enum class MORUSTATE
	{
		NONE,
		SPEAK,
		BROKEN,
		NOMONEY
	};

	int _speakCount;
	MORUSTATE _state;
	int _price;

	bool canInteraction;
	bool _isDebug;
public:
	moru();
	~moru();

	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	virtual void afterHit();
	virtual void giveFrame();
	
	void bulletCollision(bulletManager* bm);
	void checkRepair();

	RECT getInterRc() { return _interRc; }
	bool getCanInteraction() { return canInteraction; }
	void setCanInteraction(bool canInter) {	canInteraction = canInter;	}
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
