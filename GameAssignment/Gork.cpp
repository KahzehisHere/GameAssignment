#include "Gork.h"

Gork::Gork(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr)
    : GameCharacter(tex, texWidth, texHeight, cols, rows, audioMgr) {
}

void Gork::Update(float deltaTime) {
    // Custom update logic for Gork if needed
    GameCharacter::Update(deltaTime);
}

void Gork::Render(LPD3DXSPRITE sprite) {
    // Custom rendering logic for Gork if needed
    GameCharacter::Render(sprite);
}
