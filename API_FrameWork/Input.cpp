#include"framework.h"
#include "Input.h"

Input::Input(){}

Input::~Input(){}

HRESULT Input::init()
{
    //키가 전부 눌려있지 않은 상태로 초기화
    for (int i = 0; i < KEYMAX; i++)
    {
        _keyUp.set(i, false);
        _keyDown.set(i, false);
    }
    return S_OK;
}

void Input::release()
{
}

bool Input::isOnceKeyDown(int key)
{
    //GetAsyncKeyState 현재 키의 상태 알아옴
    //키가 눌렸을 때나 떨어졌을 때 호출
    //0x8000 이전에는 누른적 없고, 호출시점에서 눌린 상태
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!_keyDown[key])
        {
            _keyDown.set(key, true);
            return true;
        }
    }
    else 
    {
        _keyDown.set(key, false);
    }
    return false;
}

bool Input::isOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        _keyUp.set(key, true);
    }
    else 
    {
        if (_keyUp[key])
        {
            _keyUp.set(key, false);
            return true;
        }
    }
    return false;
}

bool Input::isStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) return true;
    return false;
}

bool Input::isToggleKey(int key)
{
    //GetKeyState 현재키의 토글상태를 알아옴.
    //0x0001 이전에누른적잇고 호출시점에 안눌른것.
    if (GetKeyState(key) & 0x0001) return true;
    return false;
}
