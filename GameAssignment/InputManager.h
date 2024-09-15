#pragma once
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
    POINT getMousePosition();  // Gets mouse cursor position

    void cleanUp();

private:
    //Input
    //	Direct Input object.
    LPDIRECTINPUT8 directInput;
    //	Direct Input keyboard device.
    LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8  dInputMouseDevice;
    //	Key input buffer
    BYTE  diKeys[256];
    DIMOUSESTATE mouse_state;
    POINT cursorPos;
    float clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
};
