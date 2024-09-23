#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    virtual ~GameState() {}

    // Called when the state is entered
    virtual void Enter() = 0;

    // Called when the state is exited
    virtual void Exit() = 0;

    // Update logic for the state (called every frame)
    virtual void Update() = 0;

    // Render logic for the state (called every frame)
    virtual void Render() = 0;
};

#endif // GAMESTATE_H
