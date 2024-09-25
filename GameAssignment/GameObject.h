//#pragma once
//#include "GraphicDevice.h"
//#include <d3dx9.h>
//using namespace std;
//
//class GameObject {
//public:
//    GameObject();
//    ~GameObject();
//    void render();
//    void drawPlatformBoundingBoxes();
//    
//   
//private:
//    LPD3DXLINE line = nullptr;
//    HRESULT hr;
//    LPD3DXSPRITE sprite = nullptr;
//    LPD3DXFONT font = nullptr;
//    LPDIRECT3DDEVICE9 d3dDevice = nullptr;
//    LPDIRECT3DTEXTURE9 platformTexture = nullptr;
//    RECT platformBoundingBoxes[4];
//    D3DXVECTOR3 platformPositions[4];
//
//    LPDIRECT3DTEXTURE9 ladderTexture = nullptr;
//    RECT ladderBoundingBox;
//    RECT ladderBoundingBoxRight;
//
//    D3DXVECTOR3 applePositions[3];
//    bool applesCollected[3] = { false, false, false };  // Tracks whether each apple has been collected
//    int collectedApples = 0;  // Number of apples collected by the player
//    int windowScreenWidth;
//    int windowScreenHeight;
//    LPDIRECT3DTEXTURE9 appleTexture = nullptr;
//};
