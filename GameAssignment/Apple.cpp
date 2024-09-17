#include "Apple.h"


using namespace std;

// Constructor
Apple::Apple(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos)
    : GameObject(tex, w, h, pos) {}

// Update method for Apple
bool checkCollisionWithPlatform(D3DXVECTOR3 applePos) {
    RECT appleRect;
    int appleSize = 50;  // Apple sprite is 50x50 pixels

    appleRect.left = (LONG)applePos.x;
    appleRect.top = (LONG)applePos.y;
    appleRect.right = appleRect.left + appleSize;
    appleRect.bottom = appleRect.top + appleSize;

    for (int i = 0; i < 4; i++) {
        RECT platformRect = platformBoundingBoxes[i];

        if (appleRect.left < platformRect.right &&
            appleRect.right > platformRect.left &&
            appleRect.top < platformRect.bottom &&
            appleRect.bottom > platformRect.top) {
            return true;  // Collision detected
        }
    }
    return false;
}

// Render method for Apple
void Apple::Render(LPD3DXSPRITE sprite) {
    HRESULT hr;
    hr = D3DXCreateTextureFromFile(d3dDevice, "apple.png", &appleTexture);  // Adjust the path to your apple image
    if (FAILED(hr)) {
        cout << "Failed to load apple texture" << endl;
    }
    sprite->Draw(texture, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}

void Apple::cleanup() {
    if (appleTexture) {
        appleTexture->Release();
        appleTexture = NULL;
}
