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

	image* mouseoverImg;

	Button* but1;
	Button* but2;

	BYTE boxAlpha;


	bool isConversation1;	//수리하겠나
	bool isConversation2;	//자, 수리가 완료되었네.
	bool isConversation3;	//그런날도있는게지
	bool isConversation4;	//자네는 돈이
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
	void playerCollision();
	void playerInterCollision();
	void checkRepair();

	RECT getInterRc() { return _interRc; }
	bool getCanInteraction() { return isConversation1; }
	void setCanInteraction(bool canInter) {	isConversation1 = canInter;	}
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
