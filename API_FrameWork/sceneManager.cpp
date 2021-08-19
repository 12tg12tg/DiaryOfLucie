#include "framework.h"
#include "SceneManager.h"
#include "gameNode.h"

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

//현재씬을 널값으로 초기화하자
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
        //삭제
        if (iter->second.gn != NULL)
        {
            iter->second.gn->release();
            SAFE_DELETE(iter->second.gn);
            iter = _sceneList.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    _sceneList.clear();
}

void SceneManager::releaseLight()
{
    isceneList iter = _sceneList.begin();
    for (iter; iter != _sceneList.end(); )
    {
        //날려도 되는 노드만 삭제
        if (iter->second.islight && iter->second.gn != NULL)
        {
            iter->second.gn->release();
            SAFE_DELETE(iter->second.gn);
            iter = _sceneList.erase(iter);
        }
        else
        {
            iter++;
        }
    }
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
    //int i = 0;
    //isceneList iter = _sceneList.begin();
    //for (iter; iter != _sceneList.end(); ++iter){

    //    ZORDER->UITextOut(iter->first, ZMAXLAYER, 100, 50 + 20 * i, RGB(255, 255, 255));
    //    i++;
    //}
}

gameNode* SceneManager::curScene()
{
    return _currentScene;
}

gameNode* SceneManager::addScene(string sceneName, gameNode* scene, bool islight)
{
    if (!scene) return nullptr;

    weightgameNode newPair;
    newPair.gn = scene;
    newPair.islight = islight;
    _sceneList.insert(make_pair(sceneName, newPair));

    return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
    isceneList find = _sceneList.find(sceneName);

    //못찾으면 E_FAIL
    if(find==_sceneList.end())   return E_FAIL;
    //바꾸려는씬이 현재씬이랑 같아도 E_FAIL
    if (find->second.gn == _currentScene) return E_FAIL;

    //여기까지 왔다면 문제가 없다. 즉 씬을 초기화 하고 변경하자.
    if (SUCCEEDED(find->second.gn->init()))
    {
        //혹시 기존에 씬이 있다면 릴리즈
        //if (_currentScene) _currentScene->release();          //씬이동할대 릴리즈하지않는다.
        
        _currentScene = find->second.gn;
        return S_OK;
    }

    return E_FAIL;
}
