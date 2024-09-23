#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {}

InputManager::~InputManager() {
    cleanUp();
}

float InputManager::clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

bool InputManager::initialize(HINSTANCE hInstance, HWND hwnd) {
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
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputKeyboardDevice->Acquire();

    // Initialize the mouse device
    hr = directInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create mouse device." << std::endl;
        return false;
    }
    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputMouseDevice->Acquire();

    return true;
}

void InputManager::getInput() {
    // Get immediate Keyboard and Mouse Data
    dInputKeyboardDevice->GetDeviceState(256, diKeys);
    dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state);

    // Update the cursor position based on mouse movement
    cursorPos.x += mouse_state.lX;
    cursorPos.y += mouse_state.lY;

    // Clamp the cursor position within screen boundaries
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    cursorPos.x = static_cast<LONG>(clamp(static_cast<float>(cursorPos.x), 0.0f, static_cast<float>(screenWidth - 32)));
    cursorPos.y = static_cast<LONG>(clamp(static_cast<float>(cursorPos.y), 0.0f, static_cast<float>(screenHeight - 32)));
}

bool InputManager::isMouseOverButton(RECT buttonRect) {
    return cursorPos.x >= buttonRect.left && cursorPos.x <= buttonRect.right &&
        cursorPos.y >= buttonRect.top && cursorPos.y <= buttonRect.bottom;
}

bool InputManager::isMouseButtonPressed(int button) {
    return (mouse_state.rgbButtons[button] & 0x80) != 0;
}

void InputManager::cleanUp() {
    // Clean up the DirectInput devices
    if (dInputKeyboardDevice) {
        dInputKeyboardDevice->Unacquire();
        dInputKeyboardDevice->Release();
        dInputKeyboardDevice = nullptr;
    }
    if (dInputMouseDevice) {
        dInputMouseDevice->Unacquire();
        dInputMouseDevice->Release();
        dInputMouseDevice = nullptr;
    }
    if (directInput) {
        directInput->Release();
        directInput = nullptr;
    }
}
