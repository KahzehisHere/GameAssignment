//#include "Game.h"
//#include "InputManager.h"
//
//
//Game::Game() : object(nullptr), gamecharacter(nullptr), window(nullptr), sprite(nullptr), line(nullptr), font(nullptr) {
//    windowScreenHeight = 720;
//    windowScreenWidth = 1280;
//}
//
//Game::~Game() {
//    cleanup();  // Ensure resources are cleaned up
//}
//
//
//GameObject* object;
//GameCharacter* gamecharacter;
//WindowManager* window;
//InputManager* inputManager;
//
//HWND g_hWnd = window->getHWND();
//int windowScreenHeight = window->getHeight();
//int windowScreenWidth = window->getWidth();
//float gorkWidth = static_cast<float>(gamecharacter->getgorkWidth());
//float gorkHeight = static_cast<float>(gamecharacter->getgorkHeight());
//float militiaWidth = static_cast<float>(gamecharacter->getmilitiaWidth());
//float militiaHeight = static_cast<float>(gamecharacter->getmilitiaHeight());
//int militiaFrames = gamecharacter->getmilitiaFrames();
//int gorkFrames = gamecharacter->getgorkFrames();
//int gorkcCol = gamecharacter->getgorkcurrentcol();
//int gorkcRow = gamecharacter->getgorkcurrentrow();
//int militiacCol = gamecharacter->getmilitiacurrentcol();
//int militiacRow = gamecharacter->getmilitiacurrentrow();
//
//void Game::render(HRESULT hr, LPD3DXSPRITE sprite) {
//    hr = D3DXCreateSprite(d3dDevice, &sprite);
//    if (FAILED(hr)) {
//        cout << "Failed to create sprite" << endl;
//        return;
//    }
//
//    hr = D3DXCreateTextureFromFile(d3dDevice, "backgroundimage.png", &backgroundTexture);
//    if (FAILED(hr)) {
//        cout << "Failed to load background image" << endl;
//    }
//
//    gamecharacter->render(hr, sprite);
//    object->render(hr, sprite, line);
//}
//
//void Game::update() {
//
//    updateBoundingBox(platformPositions, platformBoundingBoxes, ladderBoundingBox, ladderBoundingBoxRight);
//    randomizeApplePositions(min, max, applePositions);
//    checkCollision(obj1, obj2, range);
//    checkCollisionWithPlatform(applePos, platformBoundingBoxes);
//    if (d3dDevice) {
//        // Clear the screen
//        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//        d3dDevice->BeginScene();
//    // Render control instructions at the top-left corner (one row per control)
//    
//        if (font) {
//            RECT instructionRect;
//            instructionRect.left = 10;
//            instructionRect.top = 10;  // Top-left position
//            instructionRect.right = 400;  // Set enough width for the text
//
//            // Display each instruction on a new line
//            std::string instructions[] = {
//                "-----P1-----",
//                "A = move left",
//                "D = move right",
//                "W = climb / Jump",
//
//            };
//
//            // Render each instruction with a small vertical offset
//            for (int i = 0; i < 4; i++) {
//                instructionRect.top = 10 + (i * 20);  // Set each instruction 20 pixels apart
//                instructionRect.bottom = instructionRect.top + 20;
//                font->DrawText(NULL, instructions[i].c_str(), -1, &instructionRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
//            }
//
//            instructionRect.top += 40;
//
//            std::string instructionsP2[] = {
//                "-----P2-----",
//                "Left Arrow = move left",
//                "Right Arrow = move right",
//                "Up Arrow = jump"
//            };
//
//            for (int i = 0; i < 4; i++) {
//                instructionRect.top += 20;  // Set each instruction 20 pixels apart
//                instructionRect.bottom = instructionRect.top + 20;
//                font->DrawText(NULL, instructionsP2[i].c_str(), -1, &instructionRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
//            }
//        }
//
//        d3dDevice->EndScene();
//        d3dDevice->Present(NULL, NULL, NULL, NULL);
//    }
//}
//
//void Game::Logic(float deltaTime) {
//    inputManager->getInput();
//    if (inputManager->diKeys[DIK_ESCAPE] & 0x80) {
//        PostQuitMessage(0);  // Exit the program
//    }
//
//    float gorkMoveX = 0.0f;
//    float gorkMoveY = 0.0f;
//
//    // Handle movement (left/right)
//    if (inputManager->diKeys[DIK_LEFT] & 0x80) {
//        gorkMoveX -= gorkMoveSpeed * deltaTime;
//        currentState = WALK_LEFT;
//    }
//    else if (inputManager->diKeys[DIK_RIGHT] & 0x80) {
//        gorkMoveX += gorkMoveSpeed * deltaTime;
//        currentState = WALK_RIGHT;
//    }
//    else {
//        currentState = IDLE;
//    }
//
//
//    // Jump logic: allow jumping only when on the ground or platform
//    if ((inputManager->diKeys[DIK_UP] & 0x80) && !gorkIsJumping) {
//        gorkIsJumping = true;
//        gorkJumpVelocity = -gorkjumpForce;  // Apply an initial upward velocity
//        audioManager->PlaySound4();
//
//    }
//
//    // Gravity applies if in the air (falling or jumping)
//    gorkJumpVelocity += gravity * deltaTime;
//    gorkMoveY += gorkJumpVelocity * deltaTime;  // Apply vertical velocity to movement
//
//    // Update Gork's position
//    gorkPosX += gorkMoveX;
//    gorkPosY += gorkMoveY;
//
//    // Clamp Gork's position to the screen
//    gorkPosX = clamp(gorkPosX, 0, windowScreenWidth - gorkWidth);
//
//    if (gorkPosX <= 0 || gorkPosX >= windowScreenWidth - gorkWidth) {
//        if (!HitSide) {
//            audioManager->PlaySound1();  // Play the sound when hitting the sides
//            HitSide = true;  // Set flag to true so it doesn't play again
//        }
//    }
//    else {
//        HitSide = false;  // Reset flag when the militia moves away from the sides
//    }
//
//    gorkPosY = clamp(gorkPosY, 0, windowScreenHeight - gorkHeight);
//    if (gorkPosY <= 0 || gorkPosY >= windowScreenWidth - gorkWidth) {
//        if (!HitSide) {
//            audioManager->PlaySound1();  // Play the sound when hitting the sides
//            HitSide = true;  // Set flag to true so it doesn't play again
//        }
//    }
//    else {
//        HitSide = false;  // Reset flag when the militia moves away from the sides
//    }
//
//    // Check if Gork has landed on the ground
//    bool gorkOnGround = gorkPosY >= windowScreenHeight - gorkHeight;  // On the ground
//
//    // Reset jump state if Gork is on the ground
//    if (gorkOnGround) {
//        gorkPosY = windowScreenHeight - gorkHeight;  // Clamp to the ground level
//        gorkIsJumping = false;  // Gork has landed, allow jumping again
//        gorkJumpVelocity = 0.0f;  // Reset vertical velocity
//    }
//
//    // Check if Gork has landed on a platform (you may need a platform collision detection function here)
//    bool gorkOnPlatform = false;
//    for (int i = 0; i < 4; i++) {
//        RECT platformRect = platformBoundingBoxes[i];
//
//        // Check if Gork is landing on the top of a platform
//        if (gorkPosY + gorkHeight >= platformRect.top &&  // Gork's feet are below platform top
//            gorkPosY <= platformRect.top &&  // Small threshold for collision accuracy
//            gorkPosX + gorkWidth > platformRect.left &&  // Gork's right side is past platform's left edge
//            gorkPosX < platformRect.right &&              // Gork's left side is before platform's right edge
//            gorkJumpVelocity >= 0) {                      // Only apply when falling (not jumping)
//
//            gorkPosY = platformRect.top - gorkHeight;  // Snap Gork to the top of the platform
//            gorkIsJumping = false;  // Gork has landed on a platform
//            gorkJumpVelocity = 0.0f;  // Reset vertical velocity
//            gorkOnPlatform = true;    // Mark Gork as on the platform
//        }
//
//        // Check if Gork hits the bottom of a platform when jumping
//        if (gorkPosY <= platformRect.bottom && gorkPosY + gorkHeight > platformRect.bottom &&
//            gorkPosX + gorkWidth > platformRect.left && gorkPosX < platformRect.right && gorkJumpVelocity < 0) {
//            gorkPosY = platformRect.bottom;
//            gorkJumpVelocity = 0.0f;  // Stop upward movement
//        }
//    }
//
//    // If Gork is falling and not on the ground or platform, apply gravity
//    if (!gorkOnGround && !gorkOnPlatform) {
//        gorkIsJumping = true;  // Set jumping state
//    }
//
//    // Clamp Gork's position to the screen
//    gorkPosX = clamp(gorkPosX, 0, windowScreenWidth - gorkWidth);
//    gorkPosY = clamp(gorkPosY, 0, windowScreenHeight - gorkHeight);
//
//    // Default movement is zero (stops the character when no key is pressed)
//    float moveX = 0.0f;
//    float moveY = 0.0f;
//
//    // Handle directional input and move the sprite accordingly
//    if (inputManager->diKeys[DIK_A] & 0x80) {
//        moveX -= militiamoveSpeed * deltaTime;
//        currentState = WALK_LEFT;  // Move left
//    }
//    else if (inputManager->diKeys[DIK_D] & 0x80) {
//        moveX += militiamoveSpeed * deltaTime;
//        currentState = WALK_RIGHT; // Move right
//    }
//    else {
//        currentState = IDLE;
//    }
//
//    // Handle ladder climbing logic
//    if (isOnLadder()) {
//        if (inputManager->diKeys[DIK_W] & 0x80) {
//            moveY -= militiamoveSpeed * deltaTime;  // Climb upwards when W is pressed
//            isJumping = false;  // Disable jumping while on the ladder
//            jumpVelocity = 0.0f;  // Disable gravity while on the ladder
//
//        }
//        else if (inputManager->diKeys[DIK_S] & 0x80) {
//            moveY += militiamoveSpeed * deltaTime;  // Descend the ladder when S is pressed
//            isJumping = false;  // Disable jumping while on the ladder
//            jumpVelocity = 0.0f;  // Disable gravity while on the ladder
//        }
//    }
//    else {
//        // Handle jump logic if not on the ladder
//        if ((inputManager->diKeys[DIK_W] & 0x80) && !isJumping) {
//            isJumping = true;            // Start the jump
//            jumpVelocity = -jumpForce;   // Apply an initial upward velocity
//            audioManager->PlaySound4();
//        }
//
//        // Apply gravity if jumping or falling
//        jumpVelocity += gravity * deltaTime;  // Gravity pulls the character down
//        moveY += jumpVelocity * deltaTime;    // Add the velocity to the Y movement
//    }
//
//    // Update the character's position based on movement
//    militiaPosX += moveX;
//    militiaPosY += moveY;
//
//    militiaPosX = clamp(militiaPosX, 0, windowScreenWidth - militiaWidth);
//    if (militiaPosX <= 0 || militiaPosX >= windowScreenWidth - militiaWidth) {
//        if (!HitSide) {
//            audioManager->PlaySound1();  // Play the sound when hitting the sides
//            HitSide = true;  // Set flag to true so it doesn't play again
//        }
//    }
//    else {
//        HitSide = false;  // Reset flag when the militia moves away from the sides
//    }
//
//
//    // Check for vertical collisions with platforms
//    bool isOnPlatform = false;
//    for (int i = 0; i < 4; i++) {
//        RECT platformRect = platformBoundingBoxes[i];
//
//        // Check if the character is landing on the top of the platform
//        if (militiaPosY + militiaHeight >= platformRect.top &&  // Character's feet are below platform top
//            militiaPosY <= platformRect.top &&  // Character was above platform in the previous frame
//            militiaPosX + militiaWidth > platformRect.left &&  // Character's right side is past platform's left edge
//            militiaPosX < platformRect.right &&  // Character's left side is before platform's right edge
//            jumpVelocity >= 0) {  // Only apply when falling (not jumping)
//
//            // Allow the player to pass through the platform if they are pressing the down key
//            if (!(inputManager->diKeys[DIK_S] & 0x80) && !isOnLadder()) {
//                // Snap the character to the top of the platform
//                militiaPosY = platformRect.top - militiaHeight;
//                isJumping = false;  // Reset jump state
//                jumpVelocity = 0.0f;  // Stop downward movement
//                isOnPlatform = true;  // Mark the character as standing on a platform
//            }
//        }
//
//
//        // Prevent moving through the left side of the platform
//        if (militiaPosX + militiaWidth >= platformRect.left && militiaPosX + militiaWidth <= platformRect.left + 5 &&
//            militiaPosY + militiaHeight > platformRect.top && militiaPosY < platformRect.bottom) {
//            militiaPosX = platformRect.left - militiaWidth;  // Stop character at the left edge of the platform
//        }
//
//        // Prevent moving through the right side of the platform
//        if (militiaPosX <= platformRect.right && militiaPosX >= platformRect.right - 5 &&
//            militiaPosY + militiaHeight > platformRect.top && militiaPosY < platformRect.bottom) {
//            militiaPosX = platformRect.right;  // Stop character at the right edge of the platform
//        }
//
//        // Check if character hits the bottom of a platform when jumping
//        if (militiaPosY <= platformRect.bottom && militiaPosY + militiaHeight > platformRect.bottom &&
//            militiaPosX + militiaWidth > platformRect.left && militiaPosX < platformRect.right && jumpVelocity < 0) {
//            militiaPosY = platformRect.bottom;
//            jumpVelocity = 0.0f;  // Stop upward movement
//        }
//
//
//        if (militiaPosY <= 0 && jumpVelocity < 0) {
//            militiaPosY = 0;  // Clamp character's Y position to the top of the window
//            jumpVelocity = 0.0f;  // Stop upward movement
//        }
//
//        // If the character is not on any platform and not jumping, apply gravity
//        if (!isOnPlatform && militiaPosY >= windowScreenHeight - militiaHeight) {
//            militiaPosY = windowScreenHeight - militiaHeight;  // Clamp to the ground level
//            isJumping = false;
//            jumpVelocity = 0.0f;
//        }
//
//
//
//        // Ensure the character doesn't go above the window
//        militiaPosY = clamp(militiaPosY, 0, windowScreenHeight - militiaHeight);
//        if (militiaPosY <= 0) {
//            if (!HitTop) {
//                audioManager->PlaySound1();  // Play the sound when hitting the top
//                HitTop = true;  // Set flag to true so it doesn't play again
//            }
//        }
//        else {
//            HitTop = false;  // Reset flag when the militia moves away from the top
//        }
//
//    }
//
//
//
//    // Check for collisions with apples and mark them as collected
//    bool allApplesCollected = true;
//    for (int i = 0; i < 3; i++) {
//        if (!applesCollected[i]) {
//            allApplesCollected = false;  // Not all apples collected yet
//
//            if (checkCollision(D3DXVECTOR3(militiaPosX, militiaPosY, 0), applePositions[i], 50.0f)) {
//                applesCollected[i] = true;  // Mark apple as collected
//                collectedApples++;
//
//                audioManager->PlaySound2();
//
//                cout << "Collected Apple: " << i + 1 << endl;
//            }
//        }
//    }
//
//    if (gorkPosX < militiaPosX + militiaWidth && gorkPosX + gorkWidth > militiaPosX &&
//        gorkPosY < militiaPosY + militiaHeight && gorkPosY + gorkHeight > militiaPosY) {
//
//
//        MessageBox(g_hWnd, "Player 2 (Gork) caught Player 1 (Militia)! Game Over!", "Game Over", MB_OK);
//
//        // End the game
//        PostQuitMessage(0);
//    }
//
//
//    updateAnimation(deltaTime);
//
//    // Once all apples are collected, then display the win message
//    if (allApplesCollected && countdownTime > 0) {
//        MessageBox(g_hWnd, "PLAYER 1 Win!", "hehe", MB_OK);
//        PostQuitMessage(0);  // Exit the game loop
//    }
//
//    // Update the countdown timer
//    countdownTime -= deltaTime;
//    if (countdownTime <= 0) {
//        countdownTime = 0;
//        MessageBox(g_hWnd, "Time's up!", "Player 2 Win the Game", MB_OK);
//        PostQuitMessage(0);
//    }
//}
//
//void Game::updateAnimation(float deltaTime) {
//    frameTimer += deltaTime;
//
//    // Check if the state has changed, and if so, reset to the start frame
//    if (currentState != previousState) {
//        switch (currentState) {
//        case WALK_LEFT:
//            militiaFrames = militiawalkLeft.startFrame;
//            gorkFrames = gorkwalkLeft.startFrame;
//            break;
//        case WALK_RIGHT:
//            militiaFrames = militiawalkRight.startFrame;
//            gorkFrames = gorkwalkRight.startFrame;
//            break;
//
//        default:
//            militiaFrames = militiaidle.startFrame;
//            gorkFrames = gorkidle.startFrame;
//            break;
//        }
//        previousState = currentState;  // Update previous state
//    }
//
//    // Proceed with frame update based on the timer
//    if (frameTimer >= frameTime) {
//        frameTimer = 0.0f;  // Reset the timer
//
//        // Update the militiaFrames based on the current state
//        Animation currentAnim;
//        switch (currentState) {
//        case WALK_LEFT:
//            currentAnim = militiawalkLeft;
//            currentAnim = gorkwalkLeft;
//            break;
//        case WALK_RIGHT:
//            currentAnim = militiawalkRight;
//            currentAnim = gorkwalkRight;
//            break;
//        default:
//            currentAnim = militiaidle;
//            currentAnim = gorkidle;
//            break;
//        }
//
//        // Move to the next frame within the animation range
//        militiaFrames++;
//        if (militiaFrames > currentAnim.endFrame) {
//            militiaFrames = currentAnim.startFrame;  // Loop back to the start frame
//        }
//    }
//}
//
//bool Game::isOnLadder() {
//    RECT militiaRect;
//    militiaRect.left = (LONG)militiaPosX;
//    militiaRect.top = (LONG)militiaPosY;
//    militiaRect.right = militiaRect.left + militiaWidth;
//    militiaRect.bottom = militiaRect.top + militiaHeight;
//
//
//    // Check collision with left or right ladder
//    if ((militiaRect.left < ladderBoundingBox.right && militiaRect.right > ladderBoundingBox.left &&
//        militiaRect.top < ladderBoundingBox.bottom && militiaRect.bottom > ladderBoundingBox.top) ||
//        (militiaRect.left < ladderBoundingBoxRight.right && militiaRect.right > ladderBoundingBoxRight.left &&
//            militiaRect.top < ladderBoundingBoxRight.bottom && militiaRect.bottom > ladderBoundingBoxRight.top)) {
//        return true;  // Militia is on the ladder
//    }
//
//    return false;  // Militia is not on the ladder
//}
//
//void Game::updateBoundingBox(D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight) {
//
//    int platformWidth = 315;  // Actual width of the platform
//    int platformHeight = 50; // Actual height of the platform
//    int buffer = 1;  // The size of the apple (buffer space around the platform)
//
//    for (int i = 0; i < 4; i++) {
//        platformBoundingBoxes[i].left = static_cast<LONG>(platformPositions[i].x + buffer);
//        platformBoundingBoxes[i].top = static_cast<LONG>(platformPositions[i].y + buffer);
//        platformBoundingBoxes[i].right = platformBoundingBoxes[i].left + platformWidth + buffer;
//        platformBoundingBoxes[i].bottom = platformBoundingBoxes[i].top + platformHeight + buffer;
//    }
//
//    // Ladder bounding box (adjust according to your ladder positions)
//    ladderBoundingBox.left = 50;  // X-position of the left ladder
//    ladderBoundingBox.top = (windowScreenHeight / 2) - (644 / 10);  // Y-position of the ladder
//    ladderBoundingBox.right = ladderBoundingBox.left + 50;  // Adjust ladder width
//    ladderBoundingBox.bottom = ladderBoundingBox.top + 644;  // Adjust ladder height
//
//    // Right ladder
//    ladderBoundingBoxRight.left = windowScreenWidth - 257 - 50;
//    ladderBoundingBoxRight.top = (windowScreenHeight / 2) - (644 / 3);
//    ladderBoundingBoxRight.right = ladderBoundingBoxRight.left + 50;
//    ladderBoundingBoxRight.bottom = ladderBoundingBoxRight.top + 644;
//}
//
//bool Game::checkCollision(D3DXVECTOR3 obj1, D3DXVECTOR3 obj2, float range) {
//    float distance = sqrt(pow(obj1.x - obj2.x, 2) + pow(obj1.y - obj2.y, 2));
//    return distance < range;
//}
//
//bool Game::checkCollisionWithPlatform(D3DXVECTOR3 applePos, RECT platformBoundingBoxes[4]) {
//    RECT appleRect;
//    int appleSize = 50;  // Assuming the apple sprite is 50x50 pixels
//
//    // Convert the 3D position of the apple into a 2D RECT for collision checking
//    appleRect.left = (LONG)applePos.x;
//    appleRect.top = (LONG)applePos.y;
//    appleRect.right = appleRect.left + appleSize;
//    appleRect.bottom = appleRect.top + appleSize;
//
//    // Check if the apple's bounding box intersects with any platform's bounding box
//    for (int i = 0; i < 4; i++) {
//        RECT platformRect = platformBoundingBoxes[i];
//
//        if (appleRect.left < platformRect.right &&
//            appleRect.right > platformRect.left &&
//            appleRect.top < platformRect.bottom &&
//            appleRect.bottom > platformRect.top) {
//            return true;  // Collision detected
//        }
//    }
//
//    return false;  // No collision
//}
//
//void Game::randomizeApplePositions(int min, int max, D3DXVECTOR3 applePositions[3]) {
//    int screenWidth = windowScreenWidth;  // Use the actual game screen width
//    int screenHeight = windowScreenHeight;  // Use the actual game screen height
//    int randomRangeX = max - min;
//
//    for (int i = 0; i < 3; i++) {
//        bool validPosition = false;
//        while (!validPosition) {
//            // Randomize apple positions within the screen bounds
//            int min = 100;
//            int max = 100;
//            int randomX = min + rand() % randomRangeX;
//            int randomY = min + rand() % (screenHeight - min);
//
//            D3DXVECTOR3 potentialPos((float)randomX, (float)randomY, 0.0f);
//
//            // Ensure that the apple's position doesn't collide with any platform
//            if (!checkCollisionWithPlatform(potentialPos, platformBoundingBoxes)) {
//                applePositions[i] = potentialPos;
//                validPosition = true;
//            }
//        }
//    }
//}
//
//void Game::cleanup() {
//    if (backgroundTexture) backgroundTexture->Release();
//    if (sprite) sprite->Release();
//    if (line) line->Release();
//    if (font) font->Release();
//
//    backgroundTexture = nullptr;
//    sprite = nullptr;
//    line = nullptr;
//    font = nullptr;
//}