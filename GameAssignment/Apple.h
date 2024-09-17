#pragma once
#include "GameObject.h"
#include "GraphicDevice.h"

class Apple : public GameObject {
public:
    GraphicDevice device;
    IDirect3DDevice9* d3dDevice = device.getDirectDevice();
    Apple(LPDIRECT3DTEXTURE9 tex, int w, int h, D3DXVECTOR3 pos);
    D3DXVECTOR3 applePositions[3];
    bool applesCollected[3] = { false, false, false };  // Tracks whether each apple has been collected
    int collectedApples = 0;  // Number of apples collected by the player
    LPDIRECT3DTEXTURE9 appleTexture = NULL;


    // Override the virtual functions from GameObject
    void Update(float deltaTime) override;
    void Render(LPD3DXSPRITE sprite) override;
    void cleanup();
};
