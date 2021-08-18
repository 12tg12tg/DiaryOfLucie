#pragma once
#include "singleton.h"
class gameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	struct weightgameNode
	{
		gameNode* gn;
		bool islight;
	};

	typedef map<string, weightgameNode> sceneList;
	typedef map<string, weightgameNode>::iterator isceneList;

private:
	static gameNode* _currentScene;
	sceneList _sceneList;

public:
	SceneManager();
	~SceneManager();

	HRESULT init();
	void release();
	void releaseLight();
	void update(); //계산하는곳
	void render(/*HDC hdc*/);
	gameNode* curScene();
	gameNode* addScene(string sceneName, gameNode* scene, bool islight = true);
	HRESULT changeScene(string sceneName);
};

