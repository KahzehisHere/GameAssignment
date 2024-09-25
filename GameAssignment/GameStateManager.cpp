#include "GameStateManager.h"

GameStateManager::GameStateManager() {}

GameStateManager::~GameStateManager() {
    // Cleanup all remaining states
    while (!stateStack.empty()) {
        CleanupCurrentState();
    }
}

GameStateManager& GameStateManager::getInstance() {
    static GameStateManager instance;
    return instance;
}

void GameStateManager::PushState(GameState* state) {
    stateStack.push(state);
    state->Enter();  
}

void GameStateManager::PopState() {
    if (!stateStack.empty()) {
        CleanupCurrentState();
    }
}

void GameStateManager::ChangeState(GameState* state) {
    if (!stateStack.empty()) {
        CleanupCurrentState();
    }
    PushState(state);           // Push the new state
}

void GameStateManager::Update() {
    if (!stateStack.empty()) {
        stateStack.top()->Update();  // Update the current state
    }
}

void GameStateManager::Render() {
    if (!stateStack.empty()) {
        stateStack.top()->Render();  // Render the current state
    }
}

bool GameStateManager::IsEmpty() const {
    return stateStack.empty();  // Check if the state stack is empty
}

void GameStateManager::CleanupCurrentState() {
    // Cleanup the current state safely
    if (!stateStack.empty()) {
        stateStack.top()->Exit();    // Call the state's Exit method
        delete stateStack.top();     // Delete the state
        stateStack.pop();            // Pop the state from the stack
    }
}
