#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <iostream>
#include "MainMenu.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "AudioManager.h"
#include "Frametime.h"

using namespace std;

WindowManager* windowManager = nullptr;
GraphicDevice* device = nullptr;
InputManager* inputManager = nullptr;
MainMenu* mainMenu = nullptr;
GameStateManager* gameStateManager = nullptr;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Initialize window manager
    windowManager = new WindowManager(1280, 720, false, 1920, 1080);
    if (!windowManager) {
        MessageBox(NULL, "Failed to initialize windowManager!", "Error", MB_OK);
        return -1;
    }
    if (!windowManager->createWindow(hInstance)) {
        MessageBox(NULL, "Failed to create window!", "Error", MB_OK);
        delete windowManager; // Clean up allocated memory
        return -1;  // Exit if window creation fails
    }
    HWND g_hwnd = windowManager->getHWND();
    if (g_hwnd == nullptr) {
        MessageBox(NULL, "Window handle is null!", "Error", MB_OK);
        return -1;  // Exit if no valid window handle
    }

    // Initialize the graphics device
    device = new GraphicDevice();
    if (!device->createDevice()) {
        cout << "Failed to create Direct3D device." << endl;
        return -1;  // Exit if graphics device creation fails
    }

    // Initialize the input manager
    inputManager = new InputManager();
    if (!inputManager->initialize(hInstance, windowManager->getHWND())) {
        cout << "Failed to initialize input manager." << endl;
        return -1;  // Exit if input manager initialization fails
    }

    // Initialize the game state manager and the main menu
    gameStateManager = new GameStateManager();
    mainMenu = new MainMenu();
    gameStateManager->PushState(mainMenu);  // Push the main menu state

    Frametime frametime;
    frametime.init(60);

    // Main game loop
    MSG msg = { 0 };
    bool running = true;
    while (running) {
        // Handle Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;  // Exit if quit message is received
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Check how many frames need to be updated
        int framesToUpdate = frametime.FramesToUpdate();
        if (framesToUpdate > 0) {
            // Update the current state
            for (int i = 0; i < framesToUpdate; ++i) {
                gameStateManager->Update();
            }

            // Render the current state
            gameStateManager->Render();
        }

        // Exit if there are no more states in the game state manager
        if (gameStateManager->IsEmpty()) {
            running = false;
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
