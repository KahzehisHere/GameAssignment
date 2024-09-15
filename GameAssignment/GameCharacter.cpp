#include "GameCharacter.h"

GameCharacter::GameCharacter(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows, AudioManager* audioMgr)
    : texture(tex), textureWidth(texWidth), textureHeight(texHeight), columns(cols), rows(rows),
    currentFrame(0), frameTime(0.1f), frameTimer(0.0f), moveSpeed(300.0f), isJumping(false),
    jumpVelocity(0.0f), gravity(1000.0f), jumpForce(600.0f), audioManager(audioMgr) {
    frameWidth = textureWidth / columns;
    frameHeight = textureHeight / rows;
    currentState = IDLE;
}

void GameCharacter::Update(float deltaTime) {
    // Handle animation and movement
    frameTimer += deltaTime;

    if (frameTimer >= frameTime) {
        frameTimer = 0.0f;
        currentFrame++;
        if (currentFrame >= columns * rows) {
            currentFrame = 0;  // Loop animation
        }
    }

    ApplyGravity(deltaTime);

    // Update bounding box based on position
    boundingBox.left = (LONG)position.x;
    boundingBox.top = (LONG)position.y;
    boundingBox.right = boundingBox.left + frameWidth;
    boundingBox.bottom = boundingBox.top + frameHeight;
}

void GameCharacter::Render(LPD3DXSPRITE sprite) {
    RECT sourceRect;
    sourceRect.left = (currentFrame % columns) * frameWidth;
    sourceRect.right = sourceRect.left + frameWidth;
    sourceRect.top = (currentFrame / columns) * frameHeight;
    sourceRect.bottom = sourceRect.top + frameHeight;

    sprite->Draw(texture, &sourceRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}

void GameCharacter::MoveLeft(float deltaTime) {
    position.x -= moveSpeed * deltaTime;
    currentState = WALK_LEFT;
}

void GameCharacter::MoveRight(float deltaTime) {
    position.x += moveSpeed * deltaTime;
    currentState = WALK_RIGHT;
}

void GameCharacter::Jump() {
    if (!isJumping) {
        isJumping = true;
        jumpVelocity = -jumpForce;  // Initial upward velocity
        audioManager->PlaySound4();  // Play jump sound
    }
}

void GameCharacter::ApplyGravity(float deltaTime) {
    if (isJumping) {
        jumpVelocity += gravity * deltaTime;
        position.y += jumpVelocity * deltaTime;

        // Clamp to the ground
        if (position.y >= 720 - frameHeight) {  // Assuming ground is at y = 720
            position.y = 720 - frameHeight;
            isJumping = false;
            jumpVelocity = 0.0f;
        }
    }
}

D3DXVECTOR3 GameCharacter::GetPosition() const {
    return position;
}

RECT GameCharacter::GetBoundingBox() const {
    return boundingBox;
}

void GameCharacter::SetPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void GameCharacter::SetGravity(float g) {
    gravity = g;
}
