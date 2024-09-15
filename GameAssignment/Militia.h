#pragma once
#include "GameCharacter.h"

class Militia : public GameCharacter {
public:
    Militia(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr);

    void Update(float deltaTime) override;
    void Render(LPD3DXSPRITE sprite) override;
};
