#pragma once
#include "object.h"
#include "Item.h"
class shop : public object
{
protected:
	int _speakCount;
	/*아이템4개 배열 가지고있기*/

	image* mouseoverImg;

	Button* but1;
	Button* but2;
	
	ITEMDATA itemdata[4] = {};

	BYTE boxAlpha;
	RECT interRc[4];
	RECT talkRc;

	bool isConversation1;	
	bool isConversation2;	
	bool isConversation3;	
	bool isConversation4;	

	int currentItemIndex;
	Button* usableBt;

	HFONT* hFont;
	HFONT* oFont;
public:
	shop();
	~shop();

	/*아이템 랜덤으로 선언하기*/
	virtual HRESULT add(float centerx, float centery);
	virtual void release();
	virtual void update(bulletManager* bm);
	virtual void render();
	void emptyitem(int array) {
		itemdata[array].item_image = IMAGE->addImage("공백", "images/item/empty.bmp", 32, 32, true, RGB(255, 0, 255));
		itemdata[array].item_name = "팔렸어";
		itemdata[array].item_shopInfo = "";
	}
	void playerInterCollision();
	void soldItem();
};

