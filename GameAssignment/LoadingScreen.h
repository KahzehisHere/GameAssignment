#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "GameState.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "InputManager.h"
#include "GraphicDevice.h"
#include "WindowManager.h"
#include "GameState.h"

class LoadingScreen : public GameState {
public:
    LoadingScreen();    // Constructor
    ~LoadingScreen();   // Destructor

    void Enter() override;  // Called when the loading screen is entered
    void Exit() override;   // Called when the loading screen is exited
    void Update() override; // Update the loading state logic
    void Render() override; // Render the loading screen

    // Loading screen specific methods
    void setNextState(GameState* nextState); // Define which state to transition to after loading

private:
    GameState* nextState = nullptr;  // The next state to transition to
    LPDIRECT3DDEVICE9 d3dDevice = nullptr; // Direct3D device (added this as it is used in the cpp file)
    LPD3DXFONT font = nullptr;       // Font for rendering text
    LPDIRECT3DTEXTURE9 loadingTexture = nullptr;  // Texture for the loading screen
    LPD3DXSPRITE sprite = nullptr;   // Sprite for rendering the texture
};

#endif // LOADINGSCREEN_H
