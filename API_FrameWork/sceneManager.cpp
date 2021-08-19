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
        //������ �Ǵ� ��常 ����
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

    //��ã���� E_FAIL
    if(find==_sceneList.end())   return E_FAIL;
    //�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
    if (find->second.gn == _currentScene) return E_FAIL;

    //������� �Դٸ� ������ ����. �� ���� �ʱ�ȭ �ϰ� ��������.
    if (SUCCEEDED(find->second.gn->init()))
    {
        //Ȥ�� ������ ���� �ִٸ� ������
        //if (_currentScene) _currentScene->release();          //���̵��Ҵ� �����������ʴ´�.
        
        _currentScene = find->second.gn;
        return S_OK;
    }

    return E_FAIL;
}
