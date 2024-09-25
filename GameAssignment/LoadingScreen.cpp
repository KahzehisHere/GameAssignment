#include "LoadingScreen.h"
#include "Frametime.h"
#include "GraphicDevice.h"
#include "WindowManager.h"
#include "GameStateManager.h"
#include <iostream>


LoadingScreen::LoadingScreen() {
    d3dDevice = nullptr;  // Initialize to nullptr
}

LoadingScreen::~LoadingScreen() {
    
}

void LoadingScreen::Enter() {
    std::cout << "Loading Screen Entered" << std::endl;

    // Use singleton to get WindowManager
    WindowManager& windowManager = WindowManager::getWindowManager();
    HWND hWnd = windowManager.getHWND();  // Retrieve the HWND from WindowManager

    // Initialize GraphicDevice using the singleton and get the Direct3D device
    GraphicDevice& device = GraphicDevice::getInstance();  // Use singleton
    if (!d3dDevice) {
        device.createDevice(hWnd);  // Initialize the Direct3D device
        d3dDevice = device.getDirectDevice();  // Get the Direct3D device
    }

    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        cout << "Failed to create sprite" << endl;
    }

    // Load the texture for the loading screen
     hr = D3DXCreateTextureFromFile(d3dDevice, "ChasingUI.png", &loadingTexture);
    if (FAILED(hr)) {
        std::cout << "Failed to load UI" << std::endl;
    }

    
}

void LoadingScreen::Exit() {
    std::cout << "Loading Screen Exited" << std::endl;
    // Clean up loading screen resources here
    if (loadingTexture) {
        loadingTexture->Release();
        loadingTexture = nullptr;
    }
}

void LoadingScreen::Update() {
    // Simulate loading for a brief moment, then transition to the next state
    static int loadCounter = 0;
    loadCounter++;

    // For demo purposes, after 100 frames, consider the loading complete
    if (loadCounter >= 100 && nextState != nullptr) {
        GameStateManager::getInstance().ChangeState(nextState);  // Transition to the next game state
    }
}

void LoadingScreen::Render() {
    // Use the singleton WindowManager to get the window dimensions
    WindowManager& windowManager = WindowManager::getWindowManager();
    int windowScreenWidth = windowManager.getWidth();
    int windowScreenHeight = windowManager.getHeight();

    // Clear the screen and start drawing
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();  // Begin rendering

    if (sprite) {
        sprite->Begin(D3DXSPRITE_ALPHABLEND);  // Begin sprite rendering

        // Render the loading texture
        if (loadingTexture) {
            D3DSURFACE_DESC textureDesc;
            loadingTexture->GetLevelDesc(0, &textureDesc);

            D3DXVECTOR3 texturePos(
                (windowScreenWidth - textureDesc.Width) / 2.0f,
                (windowScreenHeight - textureDesc.Height) / 2.0f,
                0.0f
            );

            sprite->Draw(loadingTexture, NULL, NULL, &texturePos, D3DCOLOR_XRGB(255, 255, 255));
        }

        // Render the "Loading" text
        if (font) {
            RECT textRect;
            textRect.left = windowScreenWidth / 2 - 50;
            textRect.top = windowScreenHeight / 2 + 250;
            textRect.right = windowScreenWidth / 2 + 50;
            textRect.bottom = textRect.top + 50;

            font->DrawText(NULL, "Loading....", -1, &textRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
        }

        sprite->End();  // End sprite rendering
    }

    d3dDevice->EndScene();  // End rendering
    d3dDevice->Present(NULL, NULL, NULL, NULL);  // Present to the screen

    std::cout << "Rendering Loading Screen..." << std::endl;
}

void LoadingScreen::setNextState(GameState* nextState) {
    this->nextState = nextState;  // Define the next state after loading
}

