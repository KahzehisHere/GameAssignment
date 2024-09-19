#include "InputManager.h"
#include "WindowManager.h"
#include <iostream>

InputManager::InputManager() {}

InputManager::~InputManager() {
    cleanUp();
}
WindowManager windowManager;
HWND hwnd = windowManager.getHWND();

bool InputManager::initialize(HINSTANCE hInstance, HWND hwnd) {
    WindowManager windowManager;
    hwnd = windowManager.getHWND();  // Store the window handle for use in input processing

    HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create DirectInput object." << std::endl;
        return false;
    }

    // Initialize the keyboard device
    hr = directInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create keyboard device." << std::endl;
        return false;
    }
    hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    hr = dInputKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputKeyboardDevice->Acquire();

    // Initialize the mouse device
    hr = directInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create mouse device." << std::endl;
        return false;
    }
    hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    hr = dInputMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputMouseDevice->Acquire();

    return true;
}

void InputManager::getInput() {
    WindowManager windowmanager;
    int fullscreenWidth = windowmanager.getFullcreenWidth();
    int fullscreenHeight = windowmanager.getFullscreenHeight();
    //	Get immediate Keyboard Data.
    dInputKeyboardDevice->GetDeviceState(256, diKeys);
    dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state);

    // Update the cursor position based on relative movement (deltas)
    cursorPos.x += mouse_state.lX;  // Increment based on horizontal delta
    cursorPos.y += mouse_state.lY;  // Increment based on vertical delta

    // Keep the cursor within the screen boundaries
    cursorPos.x = clamp(cursorPos.x, 0.0f, (float)fullscreenWidth - 32);  // Assuming 32x32 cursor size
    cursorPos.y = clamp(cursorPos.y, 0.0f, (float)fullscreenHeight - 32); // Assuming 32x32 cursor size

}

bool InputManager::isMouseOverButton(RECT buttonRect) {
    return cursorPos.x >= buttonRect.left && cursorPos.x <= buttonRect.right &&
        cursorPos.y >= buttonRect.top && cursorPos.y <= buttonRect.bottom;
}

bool InputManager::isMouseButtonPressed(int button) {
    return mouse_state.rgbButtons[button] & 0x80;
}

void InputManager::cleanUp() {
    //	Create the Direct Input object.
    HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&directInput, NULL);
    //	Create the keyboard device.
    hr = directInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    hr = directInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    //	Set the input data format.
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

    //	Set the cooperative level.
    //	To Do:
    //	Try with different combination.
    dInputKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

    dInputKeyboardDevice->Acquire();
    dInputMouseDevice->Acquire(); 
}
