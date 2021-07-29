#include"framework.h"
#include "Input.h"

Input::Input(){}

Input::~Input(){}

HRESULT Input::init()
{
    //Ű�� ���� �������� ���� ���·� �ʱ�ȭ
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
    //GetAsyncKeyState ���� Ű�� ���� �˾ƿ�
    //Ű�� ������ ���� �������� �� ȣ��
    //0x8000 �������� ������ ����, ȣ��������� ���� ����
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
    //GetKeyState ����Ű�� ��ۻ��¸� �˾ƿ�.
    //0x0001 �������������հ� ȣ������� �ȴ�����.
    if (GetKeyState(key) & 0x0001) return true;
    return false;
}
