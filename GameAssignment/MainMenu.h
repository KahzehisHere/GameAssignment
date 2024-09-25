#ifndef MAINMENU_H
#define MAINMENU_H
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "InputManager.h"
#include "GraphicDevice.h"
#include "WindowManager.h"
#include "GameState.h"

class MainMenu : public GameState{
public:
    MainMenu();
    ~MainMenu();

    // Override GameState methods
    void Enter() override;
    void Exit() override;
    void Update() override;
    void Render() override;
    

private:
    InputManager& IM = InputManager::getInstance();
    LPDIRECT3DTEXTURE9 startButtonTexture = nullptr;  // Start button texture
    LPDIRECT3DTEXTURE9 exitButtonTexture = nullptr;   // Exit button texture
    LPDIRECT3DTEXTURE9 mainMenuBackground = nullptr;  // Menu background texture
    LPDIRECT3DTEXTURE9 pointer = nullptr;             // Cursor pointer texture
    LPD3DXFONT font = nullptr;
    LPD3DXLINE line = nullptr;
    LPDIRECT3DDEVICE9 d3dDevice = nullptr;            // Direct3D device pointer
    RECT startButtonRect;                             // Start button rectangle
    RECT exitButtonRect;                              // Exit button rectangle
    D3DXVECTOR3 cursorPos;
    int buttonWidth = 200;
    int buttonHeight = 50;

    // Helper methods
    void loadTextures();                              // Load all textures
    void cleanup();                                   // Release all textures and resources

    // Optional: Encapsulated button access
    RECT getStartButtonRect() const { return startButtonRect; }
    RECT getExitButtonRect() const { return exitButtonRect; }
};

#endif
