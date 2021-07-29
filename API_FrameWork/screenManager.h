#pragma once
#include "gameNode.h"
class screenManager : public gameNode
{
private:
	struct tagThisImage
	{
		image*	img;
		int		alpha;
		int		frameX;
		int		count;

		void init() {
			alpha = 255;
			frameX = 0;
			count = 0;
		}
	};
private:
	tagThisImage		_bg1;
	tagThisImage		_bg2;
	tagThisImage		_bgSlow;
	tagThisImage		_bgFast;
	tagThisImage		_fireWork1;
	tagThisImage		_fireWork2;
	tagThisImage		_fireWork3;
	tagThisImage		_fireWork4;
	tagThisImage		_fireWork5;

	tagThisImage		_fadeOut1;
	tagThisImage		_fadeOut2;

public:
	screenManager();
	~screenManager();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void blackfadeOut();
	void blackfadein();
	void showFireWork1();
	void showFireWork2();
	void showFireWork3();
	void showFireWork4();
	void showFireWork5();

	void initBlackFadeOut() { _fadeOut2.alpha = 255; }
	void initBlackFadeIn() { _fadeOut2.alpha = 0; }
};

