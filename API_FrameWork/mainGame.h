#pragma once
#include "gameNode.h"
class mainGame : public gameNode
{
private:





	bool isDebug;
	bool showFPS;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);





	void setFPSprint() { if (InputManager->isOnceKeyDown(VK_F2)) showFPS = !showFPS; }
	void setIsDebug() {
		if (InputManager->isOnceKeyDown(VK_F1)) {
			isDebug = !isDebug;
		}
	}
};  

