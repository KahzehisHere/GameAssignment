#include "GameStateManager.h"
#include <iostream>

GameStateManager::GameStateManager(InputManager* inputManager, WindowManager* windowManager, GraphicDevice* graphicDevice)
    : inputManager(inputManager), windowManager(windowManager), graphicDevice(graphicDevice) {
    currentState = GameState::MAIN_MENU;
}

GameStateManager::~GameStateManager() {}

void GameStateManager::update(float deltaTime) {
    switch (currentState) {
    case GameState::MAIN_MENU:
        updateMainMenu(deltaTime);
        break;
    case GameState::LOADING_SCREEN:
        updateLoadingScreen(deltaTime);
        break;
    case GameState::IN_GAME:
        updateInGame(deltaTime);
        break;
    case GameState::GAME_OVER:
        updateGameOver(deltaTime);
        break;
    }
}

void GameStateManager::render() {
    switch (currentState) {
    case GameState::MAIN_MENU:
        renderMainMenu();
        break;
    case GameState::LOADING_SCREEN:
        renderLoadingScreen();
        break;
    case GameState::IN_GAME:
        renderInGame();
        break;
    case GameState::GAME_OVER:
        renderGameOver();
        break;
    }
}

void GameStateManager::changeState(GameState newState) {
    currentState = newState;
}

void GameStateManager::updateMainMenu(float deltaTime) {
    if (inputManager->isKeyPressed(DIK_RETURN)) {
        changeState(GameState::LOADING_SCREEN);
    }
}

void GameStateManager::renderMainMenu(MainMenu* mainMenu) {
    graphicDevice->createDevice(windowManager->getHWND());
    mainMenu->display();
}

void GameStateManager::updateLoadingScreen(float deltaTime) {
    static float loadingTime = 0.0f;
    loadingTime += deltaTime;
    if (loadingTime >= 2.0f) {
        loadingTime = 0.0f;
        changeState(GameState::IN_GAME);
    }
}

void GameStateManager::renderLoadingScreen() {
    graphicDevice->createDevice(windowManager->getHWND());
}

void GameStateManager::updateInGame(float deltaTime) {
    if (inputManager->isKeyPressed(DIK_ESCAPE)) {
        changeState(GameState::GAME_OVER);
    }
}

void GameStateManager::renderInGame() {
    graphicDevice->createDevice(windowManager->getHWND());
}

void GameStateManager::updateGameOver(float deltaTime) {
    if (inputManager->isKeyPressed(DIK_RETURN)) {
        changeState(GameState::MAIN_MENU);
    }
}

void GameStateManager::renderGameOver() {
    graphicDevice->createDevice(windowManager->getHWND());
}
