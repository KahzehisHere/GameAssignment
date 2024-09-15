#include "LoadingScreen.h"
#include "Frametime.h"
#include "GraphicDevice.h"

LoadingScreen::LoadingScreen(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE spr, LPD3DXFONT fnt)
    : d3dDevice(device), sprite(spr), font(fnt), loadingTexture(nullptr) {
}

LoadingScreen::~LoadingScreen() {
    releaseResources();
}

void LoadingScreen::loadResources() {
    HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "ChasingUI.png", &loadingTexture);
    if (FAILED(hr)) {
        // Handle texture load failure
    }
}

void LoadingScreen::render() {
    loadResources();
    // Initialize high-resolution performance counter
    LARGE_INTEGER frequency, startTime, currentTime;
    QueryPerformanceFrequency(&frequency); // Get the frequency of the counter
    QueryPerformanceCounter(&startTime);   // Start timing

    while (true) {
        // Clear the screen and start drawing
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        d3dDevice->BeginScene();  // Begin rendering
        GraphicDevice* graphicDevice;
        int windowScreenWidth = graphicDevice->getScreenWidth();
        int windowScreenHeight = graphicDevice->getScreenHeight();

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

        // Query the current time to check how much time has passed
        QueryPerformanceCounter(&currentTime);
        double elapsedTime = static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        // Exit the loop after 2 seconds
        if (elapsedTime >= 2.0) {
            break;  // Exit the loading screen after 2 seconds
        }
    }

    // Clear the scene after the loading screen
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->Present(NULL, NULL, NULL, NULL);  // Clear the screen before the game starts
}

void LoadingScreen::releaseResources() {
    if (loadingTexture) {
        loadingTexture->Release();
        loadingTexture = nullptr;
    }
}
