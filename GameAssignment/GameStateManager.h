#pragma once
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "MainMenu.h"
#include "GameStates.h"
#include "Game.h"
#include "LoadingScreen.h"

class GameStateManager {
public:
    GameStateManager(InputManager* inputManager, WindowManager* windowManager, GraphicDevice* graphicDevice);
    ~GameStateManager();

    void update(float deltaTime);
    void render();
    void changeState(GameState newState);

    void updateMainMenu(float deltaTime);
    void updateLoadingScreen(float deltaTime);
    void updateInGame(float deltaTime);

    void renderMainMenu(MainMenu* mainMenu);
    void renderLoadingScreen(LoadingScreen* loading);
    void renderInGame(Game* game);

private:

    GameState currentState;
    InputManager* inputManager;
    WindowManager* windowManager;
    GraphicDevice* graphicDevice;
    MainMenu* mainMenu;
};
