#include "InputManager.h"
#include <iostream>

InputManager::InputManager() : directInput(nullptr), keyboardDevice(nullptr), mouseDevice(nullptr) {}

InputManager::~InputManager() {
    cleanUp();
}

bool InputManager::initialize(HINSTANCE hInstance, HWND hwnd) {
    this->hwnd = hwnd;  // Store the window handle for use in input processing

    HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create DirectInput object." << std::endl;
        return false;
    }

    // Initialize the keyboard device
    hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create keyboard device." << std::endl;
        return false;
    }
    hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    hr = keyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    keyboardDevice->Acquire();

    // Initialize the mouse device
    hr = directInput->CreateDevice(GUID_SysMouse, &mouseDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create mouse device." << std::endl;
        return false;
    }
    hr = mouseDevice->SetDataFormat(&c_dfDIMouse);
    hr = mouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    mouseDevice->Acquire();

    return true;
}

void InputManager::getInput() {
    // Poll the keyboard state
    HRESULT hr = keyboardDevice->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
    if (FAILED(hr)) {
        if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) {
            keyboardDevice->Acquire();
        }
    }

    // Poll the mouse state
    hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
    if (FAILED(hr)) {
        if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) {
            mouseDevice->Acquire();
        }
    }
}

bool InputManager::isKeyPressed(int key) {
    return keyboardState[key] & 0x80;
}

bool InputManager::isMouseButtonPressed(int button) {
    return mouseState.rgbButtons[button] & 0x80;
}

POINT InputManager::getMousePosition() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ScreenToClient(hwnd, &cursorPos);  // Convert to window coordinates
    return cursorPos;
}

void InputManager::cleanUp() {
    if (keyboardDevice) {
        keyboardDevice->Unacquire();
        keyboardDevice->Release();
        keyboardDevice = nullptr;
    }
    if (mouseDevice) {
        mouseDevice->Unacquire();
        mouseDevice->Release();
        mouseDevice = nullptr;
    }
    if (directInput) {
        directInput->Release();
        directInput = nullptr;
    }
}
