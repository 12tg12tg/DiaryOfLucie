#pragma once
#include "object.h"
class shop : public object
{
protected:
	int _speakCount;
	/*������4�� �迭 �������ֱ�*/

	image* mouseoverImg;

	Button* but1;
	Button* but2;

	BYTE boxAlpha;

	RECT interRc[4];

	bool isConversation1;	
	bool isConversation2;	
	bool isConversation3;	
	bool isConversation4;	

public:
	shop();
	~shop();

	/*������ �������� �����ϱ�*/
	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();

	void playerInterCollision();
	void soldItem();
};

