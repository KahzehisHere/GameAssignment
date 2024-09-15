#pragma once
#include <d3dx9.h>
#include <iostream>
#include "AudioManager.h"

class GameCharacter {
protected:
    LPDIRECT3DTEXTURE9 texture;  // Character texture
    int textureWidth;
    int textureHeight;
    int frameWidth;
    int frameHeight;
    int columns;  // Number of columns in the sprite sheet
    int rows;     // Number of rows in the sprite sheet
    int currentFrame;
    float frameTime;
    float frameTimer;

    D3DXVECTOR3 position;
    float moveSpeed;
    float jumpVelocity;
    bool isJumping;
    float gravity;
    float jumpForce;

    AudioManager* audioManager;

    RECT boundingBox;  // Character's bounding box

    enum MovementState { IDLE, WALK_LEFT, WALK_RIGHT } currentState;

public:
    GameCharacter(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr);

    // Virtual functions for custom logic
    virtual void Update(float deltaTime);
    virtual void Render(LPD3DXSPRITE sprite);

    // Movement functions
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void Jump();
    void ApplyGravity(float deltaTime);

    // Getters
    D3DXVECTOR3 GetPosition() const;
    RECT GetBoundingBox() const;

    // Setters
    void SetPosition(float x, float y);
    void SetGravity(float g);
};
