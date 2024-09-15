#pragma once
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicDevice.h"
#include "MainMenu.h"
#include "GameStates.h"

class GameStateManager {
public:
    GameStateManager(InputManager* inputManager, WindowManager* windowManager, GraphicDevice* graphicDevice);
    ~GameStateManager();

    void update(float deltaTime);
    void render();
    void changeState(GameState newState);

private:
    GameState currentState;
    InputManager* inputManager;
    WindowManager* windowManager;
    GraphicDevice* graphicDevice;

    void updateMainMenu(float deltaTime);
    void updateLoadingScreen(float deltaTime);
    void updateInGame(float deltaTime);
    void updateGameOver(float deltaTime);

    void renderMainMenu(MainMenu* mainMenu);
    void renderLoadingScreen();
    void renderInGame();
    void renderGameOver();
};
