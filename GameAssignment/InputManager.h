#pragma once  // Add this to prevent redefinition
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>
#include "WindowManager.h"


class InputManager {
public:
    ~InputManager();

    static InputManager& getInstance();  // Singleton instance getter
    bool initialize(HINSTANCE hInstance, HWND hWnd);
    void cleanUp();
    bool isMouseButtonPressed(int button);
    bool isKeyPressed(int key);
    HRESULT getMouseState(DIMOUSESTATE* mouseState);
    void getInput();  // Polls input devices
    bool isMouseOverButton(RECT buttonRect);  // Checks if a specific key is pressed
    POINT getMousePosition() {
        return cursorPos;
    }

private:
    BYTE  diKeys[256];
    LPDIRECTINPUT8 dInput = nullptr;
    LPDIRECTINPUTDEVICE8 dInputKeyboardDevice = nullptr;
    LPDIRECTINPUTDEVICE8 dInputMouseDevice = nullptr;
    DIMOUSESTATE mouse_state;
    POINT cursorPos;
    float clamp(float value, float min, float max);
    InputManager();
    // Deleted copy constructor and assignment operator
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
};

#endif
