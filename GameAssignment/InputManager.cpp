#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "InputManager.h"
#include <iostream>

// Private constructor to enforce singleton
InputManager::InputManager() : dInput(nullptr), dInputKeyboardDevice(nullptr), dInputMouseDevice(nullptr){}

// Destructor
InputManager::~InputManager() {
    cleanUp();
}

float InputManager::clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

bool InputManager::initialize(HINSTANCE hInstance, HWND hWnd) {
    HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create DirectInput object. Error: " << hr << std::endl;
        return false;
    }

    // Initialize keyboard device
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create keyboard device. Error: " << hr << std::endl;
        return false;
    }
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputKeyboardDevice->Acquire();

    // Initialize mouse device
    hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    if (FAILED(hr)) {
        std::cout << "Failed to create mouse device. Error: " << hr << std::endl;
        return false;
    }
    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    dInputMouseDevice->Acquire();

    return true;
}

InputManager& InputManager::getInstance() {
    static InputManager instance;  // Static instance for singleton
    return instance;
}


void InputManager::getInput() {
    // Get immediate Keyboard and Mouse Data
    dInputKeyboardDevice->GetDeviceState(256, diKeys);
    dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state);

    // Update the cursor position based on mouse movement
    cursorPos.x += mouse_state.lX;
    cursorPos.y += mouse_state.lY;

    // Get window bounds from the WindowManager
    WindowManager& windowManager = WindowManager::getWindowManager();
    int windowWidth = windowManager.getWidth();
    int windowHeight = windowManager.getHeight();

    // Keep the cursor within the screen boundaries
    cursorPos.x = clamp(cursorPos.x, 0.0f, (float)windowWidth - 32);  // Assuming 32x32 cursor size
    cursorPos.y = clamp(cursorPos.y, 0.0f, (float)windowHeight - 32); // Assuming 32x32 cursor size
}

bool InputManager::isMouseOverButton(RECT buttonRect) {
    return cursorPos.x >= buttonRect.left && cursorPos.x <= buttonRect.right &&
        cursorPos.y >= buttonRect.top && cursorPos.y <= buttonRect.bottom;
}

bool InputManager::isMouseButtonPressed(int button) {
    return (mouse_state.rgbButtons[button] & 0x80) != 0;
}

bool InputManager::isKeyPressed(int key) {
    return (diKeys[key] & 0x80) != 0;
}

HRESULT InputManager::getMouseState(DIMOUSESTATE* mouseState) {
    if (dInputMouseDevice) {
        // Get the current state of the mouse
        HRESULT hr = dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);
        if (FAILED(hr)) {
            // If the device is lost, try to re-acquire it
            if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
                dInputMouseDevice->Acquire();
            }
        }
        return hr;
    }
    return E_FAIL;
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
    if (dInput) {
        dInput->Release();
        dInput = nullptr;
    }
}
