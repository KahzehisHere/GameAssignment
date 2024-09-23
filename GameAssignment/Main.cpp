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

//Initialize global pointers for key managers and objects
//AudioManager* audioManager = nullptr;
WindowManager* window = nullptr;
GraphicDevice* device = nullptr;
InputManager* inputManager = nullptr;
MainMenu* mainMenu = nullptr;
GameStateManager* gameStateManager = nullptr;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Initialize key components
    window = new WindowManager(1280, 720, false, 1920, 1080);  // Create the window
    window->createWindow(hInstance);

    device = new GraphicDevice();
    if (!device->createDevice(window->getHWND())) {
        return -1;  // Failed to create Direct3D device
    }

    inputManager = new InputManager();
    if (!inputManager->initialize(hInstance, window->getHWND())) {
        return -1;  // Failed to initialize input manager
    }

    // Initialize the game state manager and the main menu
    gameStateManager = new GameStateManager();
    mainMenu = new MainMenu();
    gameStateManager->PushState(mainMenu);  // Push the main menu state

    // Main game loop (renders only the main menu)
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

        // Update and render the current state (Main Menu)
        gameStateManager->Update();
        gameStateManager->Render();

        // Check if we should exit (the game state manager should handle transitions)
        if (gameStateManager->IsEmpty()) {
            running = false;
        }
    }

    // Cleanup resources before exiting
    device->cleanup();
    window->cleanup();  // No arguments needed
    inputManager->cleanUp();

    // Clean up allocated memory
   /* delete audioManager;*/
    delete window;
    delete device;
    delete inputManager;
    delete gameStateManager;

    return 0;
}
