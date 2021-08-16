#include "framework.h"
#include "SceneManager.h"
#include "gameNode.h"

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

//������� �ΰ����� �ʱ�ȭ����
gameNode* SceneManager::_currentScene = nullptr;

HRESULT SceneManager::init()
{
    return S_OK;
}



void SceneManager::release()
{
    isceneList iter = _sceneList.begin();
    for (iter; iter != _sceneList.end(); )
    {
        //����
        if (iter->second != NULL)
        {
            if (iter->second == _currentScene)iter->second->release();
            SAFE_DELETE(iter->second);
            iter = _sceneList.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    _sceneList.clear();
}

void SceneManager::update()
{
    if (_currentScene)
    {
        _currentScene->update();
    }
}

void SceneManager::render()
{
    if (_currentScene)_currentScene->render();
}

gameNode* SceneManager::addScene(string sceneName, gameNode* scene)
{
    if (!scene) return nullptr;

    _sceneList.insert(make_pair(sceneName, scene));

    return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
    isceneList find = _sceneList.find(sceneName);

    //��ã���� E_FAIL
    if(find==_sceneList.end())   return E_FAIL;
    //�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
    if (find->second == _currentScene) return E_FAIL;

    //������� �Դٸ� ������ ����. �� ���� �ʱ�ȭ �ϰ� ��������.
    if (SUCCEEDED(find->second->init()))
    {
        //Ȥ�� ������ ���� �ִٸ� ������
       // if (_currentScene) _currentScene->release();
        
        _currentScene = find->second;
        return S_OK;
    }

    return E_FAIL;
}
