#pragma once
#include "GraphicDevice.h"
#include <d3dx9.h>
using namespace std;

class GameObject {
public:
    GameObject(HRESULT hr, LPD3DXLINE line, D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight);
    
    void render(HRESULT hr, LPD3DXSPRITE sprite, LPD3DXLINE line);
    void drawPlatformBoundingBoxes(HRESULT hr, LPD3DXLINE line, D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight);
    void Update(D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight);
   
private:

    GraphicDevice* device;
    IDirect3DDevice9* d3dDevice = device->getDirectDevice();
    LPD3DXLINE line;
    HRESULT hr;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;

    LPDIRECT3DTEXTURE9 platformTexture;
    RECT platformBoundingBoxes[4];
    D3DXVECTOR3 platformPositions[4];

    LPDIRECT3DTEXTURE9 ladderTexture;
    RECT ladderBoundingBox;
    RECT ladderBoundingBoxRight;

    D3DXVECTOR3 applePositions[3];
    bool applesCollected[3] = { false, false, false };  // Tracks whether each apple has been collected
    int collectedApples = 0;  // Number of apples collected by the player
    LPDIRECT3DTEXTURE9 appleTexture;
};
