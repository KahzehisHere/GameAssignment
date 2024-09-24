#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "MainMenu.h"
#include "WindowManager.h"
#include <string>
#include <iostream>


D3DXVECTOR3 cursorPos (640.0f, 360.0f, 0.0f);
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
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "main_menu_background.png", &mainMenuBackground);
    // Load textures for the menu background, start, and exit buttons
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "main_menu_background.png", &mainMenuBackground))) {
        cout << "Failed to load main menu background texture" << endl;
    }
    hr = D3DXCreateTextureFromFile(d3dDevice, "startbutton.png", &startButtonTexture);
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "startbutton.png", &startButtonTexture))) {
        cout << "Failed to load start button texture" << endl;
    }
    hr = D3DXCreateTextureFromFile(d3dDevice, "exitbutton.png", &exitButtonTexture);
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "exitbutton.png", &exitButtonTexture))) {
        cout << "Failed to load exit button texture" << endl;
    }
    hr = D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &pointer);
    if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &pointer))){
        cout << "Failed to load cursor texture" << endl;
    }

    hr = D3DXCreateLine(d3dDevice, &line);
    if (FAILED(hr)) {
        cout << "Failed to create line" << endl;
    }

    hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

    // Define the positions for the buttons dynamically based on the screen size

    startButtonRect.left = windowManager->getWidth() / 2 - buttonWidth / 2;
    startButtonRect.top = windowManager->getHeight() / 2 - 100;
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
        // Calculate the center position of the button rectangle
        float centerX = static_cast<float>(startButtonRect.left + buttonWidth / 2);
        float centerY = static_cast<float>(startButtonRect.top + buttonHeight / 2);

        // Adjust the position to draw the sprite centered on the button
        D3DXVECTOR3 startButtonPos(centerX - (buttonWidth / 2), centerY - (buttonHeight / 2), 0.0f);
        sprite->Draw(startButtonTexture, NULL, NULL, &startButtonPos, D3DCOLOR_XRGB(255, 255, 255));
    }

    // Draw exit button
    if (exitButtonTexture) {
        // Calculate the center position of the button rectangle
        float centerX = static_cast<float>(exitButtonRect.left + buttonWidth / 2);
        float centerY = static_cast<float>(exitButtonRect.top + buttonHeight / 2);

        // Adjust the position to draw the sprite centered on the button
        D3DXVECTOR3 exitButtonPos(centerX - (buttonWidth / 2), centerY - (buttonHeight / 2), 0.0f);
        sprite->Draw(exitButtonTexture, NULL, NULL, &exitButtonPos, D3DCOLOR_XRGB(255, 255, 255));
    }

    sprite->End();
     //Draw the boxes around the buttons
        if (line) {
            line->SetWidth(2.0f);  // Set line thickness
            line->Begin();
            D3DCOLOR lineColor = D3DCOLOR_XRGB(255, 255, 0);  // Yellow color

            // Draw a box around the "Start Game" button
            D3DXVECTOR2 startButtonBox[5] = {
                D3DXVECTOR2(startButtonRect.left, startButtonRect.top),
                D3DXVECTOR2(startButtonRect.right, startButtonRect.top),
                D3DXVECTOR2(startButtonRect.right, startButtonRect.bottom),
                D3DXVECTOR2(startButtonRect.left, startButtonRect.bottom),
                D3DXVECTOR2(startButtonRect.left, startButtonRect.top)  // Close the rectangle
            };
            line->Draw(startButtonBox, 5, lineColor);

            // Draw a box around the "Exit" button
            D3DXVECTOR2 exitButtonBox[5] = {
                D3DXVECTOR2(exitButtonRect.left, exitButtonRect.top),
                D3DXVECTOR2(exitButtonRect.right, exitButtonRect.top),
                D3DXVECTOR2(exitButtonRect.right, exitButtonRect.bottom),
                D3DXVECTOR2(exitButtonRect.left, exitButtonRect.bottom),
                D3DXVECTOR2(exitButtonRect.left, exitButtonRect.top)  // Close the rectangle
            };
            line->Draw(exitButtonBox, 5, lineColor);

            line->End();
        }
        if (font) {
            // Draw text over the "Start Game" button, centered
            RECT startTextRect = startButtonRect;
            startTextRect.top += 10; // Adjust vertically if needed
            font->DrawText(NULL, "Start Game", -1, &startTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, D3DCOLOR_XRGB(255, 255, 255));
        }

        // Draw the text over the "Exit" button, centered
        if (font) {
            RECT exitTextRect = exitButtonRect;
            exitTextRect.top += 10; // Adjust vertically if needed
            font->DrawText(NULL, "Exit", -1, &exitTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, D3DCOLOR_XRGB(255, 255, 255));
        }
    inputManager->getInput();
    // Draw the custom cursor
    if (pointer) {
        D3DXVECTOR3 cursorDrawPos = cursorPos;  // Use tracked cursor position

        cursorDrawPos.x -= 16;  // Assuming 32x32 cursor size, adjust by half the size
        cursorDrawPos.y -= 16;

        sprite->Begin(D3DXSPRITE_ALPHABLEND);
        sprite->Draw(pointer, NULL, NULL, &cursorDrawPos, D3DCOLOR_XRGB(255, 255, 255));
        sprite->End();

    }
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
    
    sprite->Release();

}

void MainMenu::Update() {
    // Get mouse position and check for button clicks
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ScreenToClient(GetForegroundWindow(), &cursorPos);

    // Start Button Clicked
    if (inputManager->isMouseButtonPressed(0)) {  // Left mouse button is index 0
        if (cursorPos.x >= startButtonRect.left && cursorPos.x <= startButtonRect.right &&
            cursorPos.y >= startButtonRect.top && cursorPos.y <= startButtonRect.bottom) {
            std::cout << "Start button clicked" << std::endl;

            // Transition to the next game state (e.g., GamePlayState)
            // Assuming you have a GamePlayState class defined
            /*GameState* gamePlayState = new GamePlayState();
            gameStateManager->PushState(gamePlayState); */ // Push new game state
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
