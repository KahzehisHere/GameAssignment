#include "Militia.h"

Militia::Militia(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr)
    : GameCharacter(tex, texWidth, texHeight, cols, rows, audioMgr) {
}

void Militia::Update(float deltaTime) {
    // Custom update logic for militia if needed
    GameCharacter::Update(deltaTime);
}

void Militia::Render(LPD3DXSPRITE sprite) {
    // Custom rendering logic for militia if needed
    GameCharacter::Render(sprite);
}
