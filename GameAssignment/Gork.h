#pragma once
#include "GameCharacter.h"

class Gork : public GameCharacter {
public:
    Gork(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr);

    void Update(float deltaTime) override;
    void Render(LPD3DXSPRITE sprite) override;
};
