#pragma once
#include "gameNode.h"
#include "mainDOL.h"
class mainGame : public gameNode
{
private:
	mainDOL* _mDOL;




	bool _isDebug;
	bool _showFPS;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);




	RECT checkGameSize();
	void setFPSprint() { if (InputManager->isOnceKeyDown(VK_F2)) _showFPS = !_showFPS; }
	void setIsDebug() {
		if (InputManager->isOnceKeyDown(VK_F1)) {
			_isDebug = !_isDebug;
			_mDOL->setIsdebug(_isDebug);
		}
	}
};  

