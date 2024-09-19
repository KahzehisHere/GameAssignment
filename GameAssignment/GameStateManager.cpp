#include "GameStateManager.h"
#include "AudioManager.h"

GameStateManager::GameStateManager() {
    currentState = MAIN_MENU;  // Start with the main menu
    mainMenu = new MainMenu();
    loadingScreen = new LoadingScreen();
    game = new Game();
}

GameStateManager::~GameStateManager() {
    delete mainMenu;
    delete loadingScreen;
    delete game;
}

void GameStateManager::changeState(GameState newState) {
    currentState = newState;
}

void GameStateManager::update() {
    switch (currentState) {
    case MAIN_MENU:
        mainMenu->update(inputManager);
        break;
    case PLAYING:
        game->Logic(deltaTime, AudioManager & audioManager);
        game->update();
        game->updateAnimation(deltaTime);
        break;
    case LOADING_SCREEN:
        loadingScreen->render();
        break;
    case GAME_OVER:
        // Handle game over update logic here
        break;
    }
}

void GameStateManager::render() {
    switch (currentState) {
    case MAIN_MENU:
        mainMenu->loadTextures();
        mainMenu->display();
        break;
    case PLAYING:
        game->render(hr, sprite);
        break;
    case LOADING_SCREEN:
        loadingScreen->loadResources();

        break;
    case GAME_OVER:
        // Handle game over rendering here
        break;
    }
}
