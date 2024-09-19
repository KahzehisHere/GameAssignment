#include "MainMenu.h"
#include "WindowManager.h"
#include <string>
#include <iostream>

using namespace std;

MainMenu::MainMenu(IDirect3DDevice9* device) : d3dDevice(device), startButtonTexture(nullptr), exitButtonTexture(nullptr), mainMenuBackground(nullptr) {
    if (!d3dDevice) {
        std::cout << "Error: Direct3D device is not initialized." << std::endl;
    }
}

MainMenu::~MainMenu() {
    cleanup();
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
    int buttonWidth = 200;
    int buttonHeight = 50;

    startButtonRect.left = 1280 / 2 - buttonWidth / 2;
    startButtonRect.top = 720 / 2 - 100;
    startButtonRect.right = startButtonRect.left + buttonWidth;
    startButtonRect.bottom = startButtonRect.top + buttonHeight;

    exitButtonRect.left = 1280 / 2 - buttonWidth / 2;
    exitButtonRect.top = 720 / 2 + 60;
    exitButtonRect.right = exitButtonRect.left + buttonWidth;
    exitButtonRect.bottom = exitButtonRect.top + buttonHeight;
}

void MainMenu::display() {
    loadTextures();
    // Menu rendering loop
    MSG msg;
    bool menuRunning = true;
    LPD3DXSPRITE sprite;
    D3DXCreateSprite(d3dDevice, &sprite);
    WindowManager windowmanager;
    int fullscreenWidth = windowmanager.getFullcreenWidth();
    int fullscreenHeight = windowmanager.getFullscreenHeight();

    while (menuRunning) {
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        d3dDevice->BeginScene();

        // Begin sprite rendering
        sprite->Begin(D3DXSPRITE_ALPHABLEND);

        // Draw the main menu background without scaling
        if (mainMenuBackground) {
            D3DSURFACE_DESC bgDesc;
            mainMenuBackground->GetLevelDesc(0, &bgDesc);

            // Calculate the scaling factors to scale the image to the screen size
            float scaleX = static_cast<float>(fullscreenWidth) / static_cast<float>(bgDesc.Width);
            float scaleY = static_cast<float>(fullscreenHeight) / static_cast<float>(bgDesc.Height);

            // Apply scaling to the sprite
            D3DXMATRIX mat;
            D3DXMatrixScaling(&mat, scaleX, scaleY, 1.0f);
            sprite->SetTransform(&mat);

            // Draw the background image scaled to fit the screen
            D3DXVECTOR3 menuPos(0, 0, 0); // Draw from top-left
            sprite->Draw(mainMenuBackground, NULL, NULL, &menuPos, D3DCOLOR_XRGB(255, 255, 255));

            // Reset transformation for future draws
            D3DXMatrixIdentity(&mat);
            sprite->SetTransform(&mat);
        }


        // Draw start button
        if (startButtonTexture) {
            // Calculate the center position of the button rect
            float startButtonCenterX = (startButtonRect.left + startButtonRect.right) / 2.0f;
            float startButtonCenterY = (startButtonRect.top + startButtonRect.bottom) / 2.0f;

            // Assume the sprite's width and height are half the rect size, adjust if needed
            D3DSURFACE_DESC buttonDesc;
            startButtonTexture->GetLevelDesc(0, &buttonDesc);

            float buttonWidth = buttonDesc.Width;
            float buttonHeight = buttonDesc.Height;

            // Adjust the position to center the sprite
            D3DXVECTOR3 startButtonPos(startButtonCenterX - buttonWidth / 2.0f, startButtonCenterY - buttonHeight / 2.0f, 0.0f);
            sprite->Draw(startButtonTexture, NULL, NULL, &startButtonPos, D3DCOLOR_XRGB(255, 255, 255));
        }

        // Draw exit button
        if (exitButtonTexture) {
            float exitButtonCenterX = (exitButtonRect.left + exitButtonRect.right) / 2.0f;
            float exitButtonCenterY = (exitButtonRect.top + exitButtonRect.bottom) / 2.0f;

            D3DSURFACE_DESC exitDesc;
            exitButtonTexture->GetLevelDesc(0, &exitDesc);

            float exitWidth = exitDesc.Width;
            float exitHeight = exitDesc.Height;

            D3DXVECTOR3 exitButtonPos(exitButtonCenterX - exitWidth / 2.0f, exitButtonCenterY - exitHeight / 2.0f, 0.0f);
            sprite->Draw(exitButtonTexture, NULL, NULL, &exitButtonPos, D3DCOLOR_XRGB(255, 255, 255));
        }

        sprite->End();
        d3dDevice->EndScene();
        d3dDevice->Present(NULL, NULL, NULL, NULL);

        // Logic for detecting button clicks (simplified example)
        if (GetAsyncKeyState(VK_LBUTTON)) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(GetForegroundWindow(), &cursorPos);

            // Start game button click
            if (cursorPos.x >= startButtonRect.left && cursorPos.x <= startButtonRect.right &&
                cursorPos.y >= startButtonRect.top && cursorPos.y <= startButtonRect.bottom) {
                menuRunning = false;  // Exit the menu
            }

            // Exit button click
            if (cursorPos.x >= exitButtonRect.left && cursorPos.x <= exitButtonRect.right &&
                cursorPos.y >= exitButtonRect.top && cursorPos.y <= exitButtonRect.bottom) {
                PostQuitMessage(0);  // Exit the game
                menuRunning = false;
            }
        }

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                menuRunning = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    sprite->Release();
}

void MainMenu::update(InputManager* inputManager) {
    // Get mouse position and check for button clicks
    POINT cursorPos = inputManager->getMousePosition();

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
}
