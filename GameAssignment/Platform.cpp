#include "Platform.h"

// Constructor
Platform::Platform(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos)
    : GameObject(tex, w, h, pos) {}

// Update method for Platform
void Platform::Update(float deltaTime) {
}

// Render method for Platform
void Platform::Render(LPD3DXSPRITE sprite) {
    sprite->Draw(texture, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}
