#include "Ladder.h"

// Constructor
Ladder::Ladder(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos)
    : GameObject(tex, w, h, pos) {}

// Update method for Ladder
void Ladder::Update(float deltaTime) {
    // Ladders are static, but interaction logic could go here
}

// Render method for Ladder
void Ladder::Render(LPD3DXSPRITE sprite) {
    sprite->Draw(texture, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}

// Check if player can climb
bool Ladder::canClimb() const {
    // Logic for determining if the player is within range to climb
    // Can be based on bounding box collision
    return true;
}
