#pragma once
#include "MainMenu.h"
#include "LoadingScreen.h"
#include "InputManager.h"
#include "Game.h"
#include "AudioManager.h"

enum GameState {
    MAIN_MENU,
    PLAYING,
    LOADING_SCREEN,
    GAME_OVER
};

class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    void changeState(GameState newState);
    void update();
    void render();

private:
    GameState currentState;
    MainMenu* mainMenu;
    LoadingScreen* loadingScreen;
    Game* game;
    InputManager* inputManager;
    HRESULT hr;
    LPD3DXSPRITE sprite;
    float deltaTime;
};
