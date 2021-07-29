#include "framework.h"
#include "animationManager.h"

animationManager::animationManager()
{
}

animationManager::~animationManager()
{
}

HRESULT animationManager::init()
{
     return S_OK;
}

void animationManager::release()
{
    deleteAll();
}

void animationManager::update()
{
    iterArrAnimation iter = _animation.begin();
    for ( iter; iter != _animation.end(); ++iter)
    {
        if (!iter->second->isPlay()) continue;
        iter->second->frameUpdate(TIME->getElapsedTime() * 1.0f);
    }
}

void animationManager::render()
{
}

void animationManager::addDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse, bool loop)
{
    //이미지 및 애니메이션 초기화
    image* img = IMAGE->findImage(imageKeyName);
    animation* ani = new animation;
    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
    ani->setDefPlayFrame(reverse, loop);
    ani->setFPS(fps);

    //이미지와 애니메이션을 초기화 한 후 map에 추가.
    _animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int* playarr, int arrLen, int fps, bool loop)
{
    //이미지 및 애니메이션 초기화
    image* img = IMAGE->findImage(imageKeyName);
    animation* ani = new animation;
    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
    ani->setPlayFrame(playarr, arrLen, loop);
    ani->setFPS(fps);

    //이미지와 애니메이션을 초기화 한 후 map에 추가.
    _animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
    //이미지 및 애니메이션 초기화
    image* img = IMAGE->findImage(imageKeyName);
    animation* ani = new animation;
    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
    ani->setPlayFrame(start, end, reverse, loop);
    ani->setFPS(fps);

    //이미지와 애니메이션을 초기화 한 후 map에 추가.
    _animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::start(string animationKeyName)
{
    iterArrAnimation iter = _animation.find(animationKeyName);
    iter->second->start();
}

void animationManager::stop(string animationKeyName)
{
    iterArrAnimation iter = _animation.find(animationKeyName);
    iter->second->stop();
}

void animationManager::pause(string animationKeyName)
{
    iterArrAnimation iter = _animation.find(animationKeyName);
    iter->second->pause();
}

void animationManager::resume(string animationKeyName)
{
    iterArrAnimation iter = _animation.find(animationKeyName);
    iter->second->resume();
}

animation* animationManager::findAnimation(string animationKeyName)
{
    iterArrAnimation iter = _animation.find(animationKeyName);

    if (iter != _animation.end()) 
    {
        return iter->second;
    }
    return nullptr;
}

void animationManager::deleteAll()
{
    iterArrAnimation iter = _animation.begin();
    for ( ; iter != _animation.end(); )
    {
        if (iter->second != NULL)
        {
            SAFE_DELETE(iter->second);
            iter = _animation.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}
