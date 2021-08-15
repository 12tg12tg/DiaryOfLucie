#pragma once
#include"gameNode.h"
class progressBar : public gameNode
{
private:


	RECT _rcProgress;
	int _x, _y;
	int _width;

	image* _progressBarFront;
	image* _progressBarBack;


public:

	progressBar();
	~progressBar();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();


	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect()const { return _rcProgress; }

};

