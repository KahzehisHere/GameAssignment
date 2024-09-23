#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <iostream>
#include "MainMenu.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "AudioManager.h"

using namespace std;

WindowManager* windowManager = nullptr;
GraphicDevice* device = nullptr;
InputManager* inputManager = nullptr;
MainMenu* mainMenu = nullptr;
GameStateManager* gameStateManager = nullptr;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Initialize key components
    windowManager = new WindowManager(1280, 720, false, 1920, 1080);
    if (!windowManager->createWindow(hInstance)) {
        cout << "Failed to create window." << endl;
        return -1;
    }

    device = new GraphicDevice();
    if (!device->createDevice(windowManager->getHWND())) {
        cout << "Failed to create Direct3D device." << endl;
        return -1;
    }

    inputManager = new InputManager();
    if (!inputManager->initialize(hInstance, windowManager->getHWND())) {
        cout << "Failed to initialize input manager." << endl;
        return -1;
    }

    // Initialize the game state manager and the main menu
    gameStateManager = new GameStateManager();
    mainMenu = new MainMenu();
    gameStateManager->PushState(mainMenu);  // Push the main menu state

    // Main game loop
    MSG msg = { 0 };
    bool running = true;
    while (running) {
        // Handle Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Update and render the current state
        gameStateManager->Update();
        gameStateManager->Render();

        // Check if we should exit
        if (gameStateManager->IsEmpty()) {
            running = false;  // Exit if the state stack is empty
        }
    }

    // Cleanup resources before exiting
    if (device) {
        device->cleanup();
    }
    if (windowManager) {
        windowManager->cleanup();
    }
    if (inputManager) {
        inputManager->cleanUp();
    }

    // Clean up allocated memory
    delete windowManager;
    delete device;
    delete inputManager;
    delete gameStateManager;

    return 0;
}
