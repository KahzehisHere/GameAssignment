#include "GameStateManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "MainMenu.h"
#include "Frametime.h"

InputManager* inputManager = nullptr;
WindowManager* windowManager = nullptr;
GraphicDevice* graphicDevice = nullptr;
GameStateManager* gameStateManager = nullptr;
Frametime* gameTimer = new Frametime();

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Initialize WindowManager and GraphicDevice
    WindowManager windowManager(1280, 720, false, 1920, 1080);
    windowManager.createWindow(hInstance);

    GraphicDevice graphicDevice(1280, 720);
    graphicDevice.createDevice(windowManager.getHWND());

    // Initialize InputManager
    InputManager inputManager;
    if (!inputManager.initialize(hInstance, windowManager.getHWND())) {
        std::cout << "Failed to initialize input manager." << std::endl;
        return -1;
    }

    // Initialize MainMenu
    MainMenu mainMenu(&graphicDevice);

    // Main game loop
    while (windowManager.windowIsRunning()) {
        inputManager.getInput();  // Update input

        mainMenu.update(&inputManager);  // Update main menu with input

        // Render Main Menu
        graphicDevice.clear(D3DCOLOR_XRGB(0, 0, 0));  // Clear screen
        mainMenu.display();  // Render the main menu
        graphicDevice.present();  // Present the rendered scene
    }

    inputManager.cleanUp();
    graphicDevice.cleanup();

    return 0;
}

