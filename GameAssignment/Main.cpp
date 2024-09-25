#define DIRECTINPUT_VERSION 0x0800
#include <iostream>
#include "MainMenu.h"
#include "LoadingScreen.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "AudioManager.h"
#include "Frametime.h"

using namespace std;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Get the singleton instance of WindowManager
    WindowManager& windowManager = WindowManager::getWindowManager(1280, 720, false, 1920, 1080);

    // Create the window using the instance of WindowManager
    if (!windowManager.createWindow(hInstance)) {
        MessageBox(NULL, "Failed to create window!", "Error", MB_OK);
        return -1;  // Exit if window creation fails
    }
    int windowWidth = windowManager.getWidth();
    int windowHeight = windowManager.getHeight();

    // Get instances of the singletons
    GraphicDevice& device = GraphicDevice::getInstance();
    InputManager& inputManager = InputManager::getInstance();
    GameStateManager& gameStateManager = GameStateManager::getInstance();
    AudioManager& audioManager = AudioManager::getInstance();

    // Initialize the graphics device
    if (!device.createDevice(windowManager.getHWND())) {
        cout << "Failed to create Direct3D device." << endl;
        return -1;  // Exit if graphics device creation fails
    }

    // Initialize the input manager
    if (!inputManager.initialize(hInstance, windowManager.getHWND())) {
        cout << "Failed to initialize input manager." << endl;
        return -1;
    }

    audioManager.InitializeAudio();

    // Initialize the game state manager and the main menu
    MainMenu* mainMenu = new MainMenu();
    gameStateManager.PushState(mainMenu);  // Push the main menu state

    Frametime frametime;
    frametime.init(60);

    // Main game loop
    MSG msg = { 0 };
    bool running = true;
    try {
        while (running) {
            // Handle Windows messages
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    running = false;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            // Check how many frames need to be updated
            int framesToUpdate = frametime.FramesToUpdate();
            inputManager.getInput();
            if (framesToUpdate > 0) {
                // Update and render the current state                
                gameStateManager.Update();
                gameStateManager.Render();
            }

            // Exit if the game state manager is empty
            if (gameStateManager.IsEmpty()) {
                running = false;
            }
        }
    }
    catch (const std::exception& e) {
        // Handle any unexpected exceptions
        cerr << "An error occurred: " << e.what() << endl;
    }
    device.cleanup();
    inputManager.cleanUp();
    windowManager.cleanup();

    return 0;
}
