#include "GameStateManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "AudioManager.h"

int main() {
    // Initialize managers
    WindowManager windowManager;
    InputManager inputManager;
    AudioManager audioManager;
    GameStateManager gameStateManager;
    HINSTANCE hInstance;

    // Initialize window and audio
    if (!windowManager.createWindow(hInstance)) {
        return -1;
    }
    audioManager.InitializeAudio();

    // Main game loop
    bool isRunning = true;
    while (isRunning) {
        inputManager.getInput(); // Capture keyboard/mouse input

        // Change game state if ESC is pressed
        if (inputManager.diKeys[DIK_ESCAPE] & 0x80) {
            isRunning = false;
        }

        // Update game state logic
        gameStateManager.update();

        // Clear the screen before rendering
        windowManager.cleanup(hInstance);

        // Render the current game state
        gameStateManager.render();

        // Present the rendered screen
        windowManager.windowIsRunning();
    }

    return 0;
}
