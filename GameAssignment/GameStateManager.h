#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>
#include "GameState.h"

class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    // Manage states
    void PushState(GameState* state);       // Push a new state onto the stack
    void PopState();                        // Pop the current state from the stack
    void ChangeState(GameState* state);     // Change the current state

    // Game loop functions
    void Update();                          // Update the current state
    void Render();                          // Render the current state

    bool IsEmpty() const;                   // Check if the stack is empty

private:
    void CleanupCurrentState();             // Helper function to cleanup current state
    std::stack<GameState*> stateStack;      // Stack to hold the game states
};

#endif // GAMESTATEMANAGER_H
