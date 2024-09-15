#ifndef MAINMENU_H
#define MAINMENU_H

#include <d3d9.h>
#include <d3dx9.h>
#include "InputManager.h"
#include "GraphicDevice.h"
#include "WindowManager.h"

class MainMenu {
public:
    MainMenu(IDirect3DDevice9* device);
    ~MainMenu();

    void loadTextures();
    void display();
    void cleanup();
    void update(InputManager* inputManager);

private:
    IDirect3DDevice9* d3dDevice;
    LPDIRECT3DTEXTURE9 startButtonTexture;
    LPDIRECT3DTEXTURE9 exitButtonTexture;
    LPDIRECT3DTEXTURE9 mainMenuBackground;
    RECT startButtonRect;
    RECT exitButtonRect;

    RECT getSbutton() {
        return startButtonRect;
    }
    RECT getEbutton() {
        return exitButtonRect;
    }
};

#endif
