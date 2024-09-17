#pragma once
#include "GameObject.h"

class Ladder : public GameObject {
public:
    Ladder(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos);

    // Override the virtual functions from GameObject
    void Update(float deltaTime) override;
    void Render(LPD3DXSPRITE sprite) override;

    bool canClimb() const;
};
