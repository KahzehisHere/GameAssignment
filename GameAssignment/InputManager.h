#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>

class InputManager {
public:
    InputManager();
    ~InputManager();

    bool initialize(HINSTANCE hInstance, HWND hwnd);
    void getInput();  // Polls input devices
    bool isKeyPressed(int key);  // Checks if a specific key is pressed
    bool isMouseButtonPressed(int button);  // Checks if a specific mouse button is pressed
    POINT getMousePosition();  // Gets mouse cursor position

    void cleanUp();

private:
    LPDIRECTINPUT8 directInput;  // DirectInput interface
    LPDIRECTINPUTDEVICE8 keyboardDevice;  // Keyboard device
    LPDIRECTINPUTDEVICE8 mouseDevice;  // Mouse device

    BYTE keyboardState[256];  // Array to store keyboard state
    DIMOUSESTATE mouseState;  // Struct to store mouse state

    HWND hwnd;  // Handle to the window
};
