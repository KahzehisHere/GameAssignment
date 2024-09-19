#pragma once
#include "GraphicDevice.h"
#include "Game.h"
#include "GameObject.h"
#include "GameCharacter.h"
#include "InputManager.h"\
#include "WindowManager.h"
#include "AudioManager.h"

class Game
{
public:
	void update();
    void updateAnimation(float deltaTime);
    bool isOnLadder();
    void Logic(float deltaTime, AudioManager& audioManager);
    void updateBoundingBox(D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight);
    bool checkCollision(D3DXVECTOR3 obj1, D3DXVECTOR3 obj2, float range);
    bool checkCollisionWithPlatform(D3DXVECTOR3 applePos, RECT platformBoundingBoxes[4]);
    void randomizeApplePositions(int min, int max, D3DXVECTOR3 applePositions[3]);
    void render(HRESULT hr, LPD3DXSPRITE sprite);
	void cleanup();

private:

    LPD3DXSPRITE sprite;
    LPD3DXFONT font;
    LPD3DXLINE line;
    LPDIRECT3DTEXTURE9 backgroundTexture;
    GraphicDevice* device;
    GameCharacter* gamecharacter;
    WindowManager* window;
    IDirect3DDevice9* d3dDevice = device->getDirectDevice();
    D3DXVECTOR3 obj1;
    D3DXVECTOR3 obj2;

    float clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    float range;
    struct Animation {
        int startFrame;
        int endFrame;
    };

    float countdownTime = 60.0f;

    bool HitSide = false;
    bool HitTop = false;

    Animation militiaidle = { 0,0 };
    Animation militiawalkLeft = { 4,7 };
    Animation militiawalkRight = { 8,11 };

    Animation gorkidle = { 0,0 };
    Animation gorkwalkLeft = { 4,7 };
    Animation gorkwalkRight = { 8,11 };

    enum MovementState { IDLE, WALK_LEFT, WALK_RIGHT };
    MovementState currentState = IDLE;
    MovementState previousState = IDLE;

    float frameTime = 0.1f;
    float frameTimer = 0.0f;
    const float gravity = 1000.0f;
    bool gorkOnPlatform = false;
    bool militiaOnPlatform = false;

    float gorkPosX;
    float gorkPosY;
    float gorkMoveSpeed = 300.0f;
    bool gorkIsJumping = false;
    float gorkJumpVelocity = 0.0f;
    const float gorkjumpForce = 800.0f;

    float militiaPosX;
    float militiaPosY;
    float militiamoveSpeed = 300.0f;
    bool isJumping = false;
    float jumpVelocity = 0.0f;
    const float jumpForce = 600.0f;

    LPDIRECT3DTEXTURE9 platformTexture;
    RECT platformBoundingBoxes[4];
    D3DXVECTOR3 platformPositions[4];

    LPDIRECT3DTEXTURE9 ladderTexture;
    RECT ladderBoundingBox;
    RECT ladderBoundingBoxRight;

    D3DXVECTOR3 applePositions[3];
    D3DXVECTOR3 applePos;
    bool applesCollected[3] = { false, false, false };  // Tracks whether each apple has been collected
    int collectedApples = 0;  // Number of apples collected by the player
    LPDIRECT3DTEXTURE9 appleTexture;
    int min = 100;
    int max = 100;
};

