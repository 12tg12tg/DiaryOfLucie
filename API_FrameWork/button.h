#pragma once
#include "singleton.h"
typedef struct tagButton
{
	RECT rc;
	image* img;
	bool isMouseOver;
	bool isClick;
	bool isDrag; 
	COLORREF butColor;
	bool buttonOn;
	bool fixMode;
	bool ismoving;
	RECT smallRect;
	RECT bigRect;

} Button;

class Cbutton : public Singleton<Cbutton>
{
private:
	map<string, Button*> _mButton;
	map<string, Button*>::iterator _miButton;

	int _tempX, _tempY;

	int differ = 5;
	bool _isDebug;
public:
	HRESULT init();
	void update();		//오버상태인지 클릭상태인지 확인.
	void release();		
	void render(HDC hdc);		//현재존재하는 모든 버튼 출력

	Button* addButton(string buttonkey, const int x, const int y, const int width, const int height, COLORREF color = RGB(255, 234, 38));
	Button* addButtonCenter(string buttonkey, const int centerx, const int centery, const int width, const int height, COLORREF color = RGB(255, 234, 38));
	Button* addFixableRect(string buttonkey, COLORREF color = RGB(255, 234, 38));

	Button* findButton(string buttonkey);

	void buttonOn(string buttonkey);
	void buttonOff(string buttonkey);

	void removeButton(string buttonkey);
	void removeAll();

	bool isMouseOver(string buttonkey);
	bool isClick(string buttonkey);
	bool isDrag(string buttonkey);

	int getClickSpotX() { return _tempX; }
	int getClickSpotY() { return _tempY; }
	
	//void RectFixModeON(bool fixMode) { _fixMode = fixMode; }

	void setIsDebug(bool isDebug);
};

