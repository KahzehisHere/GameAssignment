#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "MainMenu.h"
#include "WindowManager.h"
#include <string>
#include <iostream>

using namespace std;

MainMenu::MainMenu( ) : startButtonTexture(nullptr), exitButtonTexture(nullptr), mainMenuBackground(nullptr), pointer(nullptr) {
    // Initialize the button positions
    startButtonRect = { 640 - 100, 360 - 50, 640 + 100, 360 };  // Example start button rectangle
    exitButtonRect = { 640 - 100, 420, 640 + 100, 470 };        // Example exit button rectangle
}

MainMenu::~MainMenu() {
    cleanup();
}

void MainMenu::Enter() {
    cout << "Entering Main Menu" << endl;
    loadTextures();
}

void MainMenu::Exit() {
    cout << "Exiting Main Menu" << endl;
}

void MainMenu::loadTextures() {
    // Load textures for the menu background, start, and exit buttons
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "main_menu_background.png", &mainMenuBackground))) {
        cout << "Failed to load main menu background texture" << endl;
    }
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "startbutton.png", &startButtonTexture))) {
        cout << "Failed to load start button texture" << endl;
    }
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "exitbutton.png", &exitButtonTexture))) {
        cout << "Failed to load exit button texture" << endl;
    }
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &pointer))){
        cout << "Failed to load cursor texture" << endl;
    }
    // Define the positions for the buttons dynamically based on the screen size

    startButtonRect.left = 1280 / 2 - buttonWidth / 2;
    startButtonRect.top = 720 / 2 - 100;
    startButtonRect.right = startButtonRect.left + buttonWidth;
    startButtonRect.bottom = startButtonRect.top + buttonHeight;

    exitButtonRect.left = 1280 / 2 - buttonWidth / 2;
    exitButtonRect.top = 720 / 2 + 60;
    exitButtonRect.right = exitButtonRect.left + buttonWidth;
    exitButtonRect.bottom = exitButtonRect.top + buttonHeight;
}

void MainMenu::Render() {
    // Render the menu screen
    LPD3DXSPRITE sprite = nullptr;

    // Ensure sprite creation is successful
    if (FAILED(D3DXCreateSprite(d3dDevice, &sprite))) {
        cout << "Failed to create sprite." << endl;
        return;
    }

    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();

    // Begin sprite rendering
    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    // Draw the main menu background with scaling
    if (mainMenuBackground) {
        D3DSURFACE_DESC bgDesc;
        mainMenuBackground->GetLevelDesc(0, &bgDesc);

        float scaleX = static_cast<float>(1280) / static_cast<float>(bgDesc.Width);
        float scaleY = static_cast<float>(720) / static_cast<float>(bgDesc.Height);

        D3DXMATRIX mat;
        D3DXMatrixScaling(&mat, scaleX, scaleY, 1.0f);
        sprite->SetTransform(&mat);

        D3DXVECTOR3 menuPos(0, 0, 0);
        sprite->Draw(mainMenuBackground, NULL, NULL, &menuPos, D3DCOLOR_XRGB(255, 255, 255));

        // Reset transformation for future draws
        D3DXMatrixIdentity(&mat);
        sprite->SetTransform(&mat);
    }

    // Draw start button
    if (startButtonTexture) {
        D3DXVECTOR3 startButtonPos(
            static_cast<float>(startButtonRect.left),
            static_cast<float>(startButtonRect.top),
            0.0f
        );
        sprite->Draw(startButtonTexture, NULL, NULL, &startButtonPos, D3DCOLOR_XRGB(255, 255, 255));
    }

    // Draw exit button
    if (exitButtonTexture) {
        D3DXVECTOR3 exitButtonPos(
            static_cast<float>(exitButtonRect.left),
            static_cast<float>(exitButtonRect.top),
            0.0f
        );
        sprite->Draw(exitButtonTexture, NULL, NULL, &exitButtonPos, D3DCOLOR_XRGB(255, 255, 255));
    }

    sprite->End();
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);

    sprite->Release();

}

void MainMenu::Update() {
    // Get mouse position and check for button clicks
    POINT cursorPos = inputManager->getMousePosition();
    GetCursorPos(&cursorPos);
    ScreenToClient(GetForegroundWindow(), &cursorPos);

    // Start Button Clicked
    if (inputManager->isMouseButtonPressed(0)) {  // Left mouse button is index 0
        if (cursorPos.x >= startButtonRect.left && cursorPos.x <= startButtonRect.right &&
            cursorPos.y >= startButtonRect.top && cursorPos.y <= startButtonRect.bottom) {
            // Handle Start Button
            std::cout << "Start button clicked" << std::endl;
            // Transition to game state
        }

        // Exit Button Clicked
        if (cursorPos.x >= exitButtonRect.left && cursorPos.x <= exitButtonRect.right &&
            cursorPos.y >= exitButtonRect.top && cursorPos.y <= exitButtonRect.bottom) {
            std::cout << "Exit button clicked" << std::endl;
            PostQuitMessage(0);  // Exit the game
        }
    }
}

void MainMenu::cleanup() {
    if (mainMenuBackground) mainMenuBackground->Release();
    if (startButtonTexture) startButtonTexture->Release();
    if (exitButtonTexture) exitButtonTexture->Release();
    if (pointer) pointer->Release();  // Also release pointer texture
}
