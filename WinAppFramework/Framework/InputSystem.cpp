#include "WinApp.h"
#include "InputSystem.h"

Input::Input()
{
    //키보드 입력 초기화
    for (int i = 0; i < 256; i++)
    {
        isKeyDown[i] = false;
        isKeyUp[i] = false;
        isKey[i] = false;
    }

    //마우스 입력 초기화
    curMouse.x = WinApp::GetWinApp().GetClientWidth() / 2;
    curMouse.y = WinApp::GetWinApp().GetClientHeight() / 2;
    curMouse.wheel = 0;

    curMouse.left = false;
    curMouse.right = false;
    curMouse.middle = false;

    prevMouse = curMouse;

    SetCursorPos(curMouse.x, curMouse.y);
}

void Input::ResetInput()
{
    for (int i = 0; i < 256; i++)
    {
        isKeyDown[i] = false;
        isKeyUp[i] = false;
    }
}

void Input::KeyDown(KeyCode _key)
{
    int key = (int)_key;

    isKeyDown[key] = true;
    isKey[key] = true;
}

void Input::KeyUp(KeyCode _key)
{
    int key = (int)_key;

    isKeyUp[key] = true;
    isKey[key] = false;
}

bool Input::IsKeyDown(KeyCode _key) const
{
    int key = (int)_key;

    return isKeyDown[key];
}

bool Input::IsKeyUp(KeyCode _key) const
{
    int key = (int)_key;

    return isKeyUp[key];
}

bool Input::IsKey(KeyCode _key) const
{
    int key = (int)_key;

    return isKey[key];
}

void Input::UpdateMouse()
{
    prevMouse = curMouse;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(WinApp::GetWinApp().GetWindow(), &pt);

    curMouse.x = pt.x;
    curMouse.y = pt.y;
    curMouse.wheel = 0;

    curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
    curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
    curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

const Input::MouseState& Input::GetMouseState(bool isWorldPos)
{
    if (isWorldPos) curMouse.y = WinApp::GetWinApp().GetClientHeight() - curMouse.y;
    return curMouse;
}

const Input::MouseState& Input::GetPrevMouseState()
{
    return prevMouse;
}

bool Input::IsSame(const MouseState& a, const MouseState& b)
{
    return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;
}