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
} Button;

class Cbutton : public Singleton<Cbutton>
{
private:
	map<string, Button*> _mButton;
	map<string, Button*>::iterator _miButton;

	int _tempX, _tempY;

	bool _isDebug;
public:
	HRESULT init();
	void update();		//������������ Ŭ���������� Ȯ��.
	void release();		
	void render(HDC hdc);		//���������ϴ� ��� ��ư ���

	Button* addButton(string buttonkey, const int x, const int y, const int width, const int height, COLORREF color = RGB(255, 234, 38));
	Button* addButtonCenter(string buttonkey, const int centerx, const int centery, const int width, const int height, COLORREF color = RGB(255, 234, 38));

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

	void setIsDebug(bool isDebug);
};

