#pragma once  // Add this to prevent redefinition
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>
#include "WindowManager.h"


class InputManager {
public:
    InputManager();
    ~InputManager();

    bool initialize(HINSTANCE hInstance, HWND hwnd);
    void getInput();  // Polls input devices
    bool isMouseOverButton(RECT buttonRect);  // Checks if a specific key is pressed
    bool isMouseButtonPressed(int button);  // Checks if a specific mouse button is pressed
    BYTE  diKeys[256];
    void cleanUp();
    POINT getMousePosition() {
        return cursorPos;
    }

private:
    LPDIRECTINPUT8 dInput;
    LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8  dInputMouseDevice;
    DIMOUSESTATE mouse_state;
    POINT cursorPos;
    float clamp(float value, float min, float max);
};


extern InputManager* inputManager;

#endif
