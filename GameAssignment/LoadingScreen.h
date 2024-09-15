#include <d3d9.h>
#include <d3dx9.h>
#include <chrono>

class LoadingScreen {
private:
    LPDIRECT3DDEVICE9 d3dDevice;
    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPDIRECT3DTEXTURE9 loadingTexture;

public:
    LoadingScreen(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE spr, LPD3DXFONT fnt);
    ~LoadingScreen();

    void loadResources();  // Load textures, fonts, etc.
    void render();         // Render the loading screen
    void releaseResources();  // Cleanup resources
};

