#include "Game.h"
#include "InputManager.h"
#include "MainMenu.h"
#include <string>

using namespace std;

Game::Game() {

}

Game::~Game() {
    cleanup();  // Ensure resources are cleaned up
}

WindowManager& windowManager = WindowManager::getWindowManager();
HWND g_hWnd = windowManager.getHWND();


void Game::Enter() {
    std::cout << "Game Screen Entered" << std::endl;

    // Use singleton to get WindowManager
    WindowManager& windowManager = WindowManager::getWindowManager();
    HWND hWnd = windowManager.getHWND();  // Retrieve the HWND from WindowManager
    int windowScreenHeight = windowManager.getHeight();
    int windowScreenWidth = windowManager.getWidth();
    // Initialize GraphicDevice using the singleton and get the Direct3D device
    GraphicDevice& device = GraphicDevice::getInstance();  // Use singleton
    if (!d3dDevice) {
        device.createDevice(hWnd);  // Initialize the Direct3D device
        d3dDevice = device.getDirectDevice();  // Get the Direct3D device
    }

    InputManager& inputManager = InputManager::getInstance();

    HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        cout << "Failed to create sprite" << endl;
    }
    
    hr = D3DXCreateLine(d3dDevice, &line);
    if (FAILED(hr)) {
        cout << "Failed to create line" << endl;
    }

    hr = D3DXCreateTextureFromFile(d3dDevice, "backgroundimage.png", &backgroundTexture);
    if (FAILED(hr)) {
        cout << "Failed to load background image" << endl;
    }

    hr = D3DXCreateTextureFromFile(d3dDevice, "militia.png", &militiaTexture);  // Load the militia texture
    if (FAILED(hr)) {
        cout << "Failed to load militia texture" << endl;
    }

    hr = D3DXCreateTextureFromFile(d3dDevice, "gorksprite.png", &gorkTexture);  // Load the second player texture
    if (FAILED(hr)) {
        cout << "Failed to load gorktexture.png" << endl;
    }

    hr = D3DXCreateFont(d3dDevice, 8, 0, FW_NORMAL, 1, false,
        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "Arial", &gorkfont);


    hr = D3DXCreateFont(d3dDevice, 8, 0, FW_NORMAL, 1, false,
        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "Arial", &militiafont);

    hr = D3DXCreateTextureFromFile(d3dDevice, "platform.png", &platformTexture);  // Adjust the path
    if (FAILED(hr)) {
        cout << "Failed to load platform texture" << endl;
    }

    hr = D3DXCreateTextureFromFile(d3dDevice, "ladder.png", &ladderTexture);  // Adjust the path
    if (FAILED(hr)) {
        cout << "Failed to load ladder texture" << endl;
    }

    hr = D3DXCreateTextureFromFile(d3dDevice, "apple.png", &appleTexture);  // Adjust the path to your apple image
    if (FAILED(hr)) {
        cout << "Failed to load apple texture" << endl;
    }

    hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
    
}

void Game::Exit() {
    GameStateManager& gameStateManager = GameStateManager::getInstance();
    MainMenu* mainMenu = new MainMenu();
    GameStateManager::getInstance().PushState(mainMenu);
}

void Game::Update() {
    updateBoundingBox();
    randomizeApplePositions();
    checkCollision(obj1, obj2, range);
    checkCollisionWithPlatform(applePos);
    Logic();
}

void Game::Render() {
    if (d3dDevice) {
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        d3dDevice->BeginScene();


        if (sprite) {
            sprite->Begin(D3DXSPRITE_ALPHABLEND);  // Start sprite rendering with alpha blending

            // Render the background
            if (backgroundTexture) {
                D3DXVECTOR3 bgPos(0, 0, 0);  // Position at the top-left corner
                sprite->Draw(backgroundTexture, NULL, NULL, &bgPos, D3DCOLOR_XRGB(255, 255, 255));
            }

            if (gorkTexture) {
                RECT gorkRect;
                gorkRect.left = gorkcCol * gorkWidth;  // Use same frame logic as militia for simplicity
                gorkRect.right = gorkRect.left + gorkWidth;
                gorkRect.top = gorkcRow * gorkHeight;
                gorkRect.bottom = gorkRect.top + gorkHeight;

                D3DXVECTOR3 gorkPos(gorkPosX, gorkPosY, 0);
                sprite->Draw(gorkTexture, &gorkRect, NULL, &gorkPos, D3DCOLOR_XRGB(255, 255, 255));



            }


            // Render the animated militia sprite
            if (militiaTexture) {
                RECT militiaRect;
                militiaRect.left = militiacCol * militiaWidth;
                militiaRect.right = militiaRect.left + militiaWidth;
                militiaRect.top = militiacRow * militiaHeight;
                militiaRect.bottom = militiaRect.top + militiaHeight;

                D3DXVECTOR3 militiaPos(militiaPosX, militiaPosY, 0);  // Use updated positions
                sprite->Draw(militiaTexture, &militiaRect, NULL, &militiaPos, D3DCOLOR_XRGB(255, 255, 255));


            }


            if (platformTexture) {
                D3DSURFACE_DESC platformDesc;
                platformTexture->GetLevelDesc(0, &platformDesc);  // Get platform texture width and height

                int platformWidth = platformDesc.Width;
                int platformHeight = platformDesc.Height;

                int numberOfPlatforms = sizeof(platformPositions) / sizeof(platformPositions[0]);  // Calculate number of platforms

                // Loop through each platform bounding box and center the platform texture
                for (int i = 0; i < numberOfPlatforms; i++) {
                    RECT platformRect = platformBoundingBoxes[i];

                    // Calculate the center of the bounding box
                    float centerX = (platformRect.left + platformRect.right) / 2.0f;
                    float centerY = (platformRect.top + platformRect.bottom) / 2.0f;

                    // Calculate the position to draw the platform so it's centered
                    D3DXVECTOR3 platformPos(centerX - platformWidth / 2.0f, centerY - platformHeight / 2.0f, 0.0f);

                    // Draw the platform texture
                    sprite->Draw(platformTexture, NULL, NULL, &platformPos, D3DCOLOR_XRGB(255, 255, 255));
                }
            }

            // Render the ladders
            if (ladderTexture) {
                D3DSURFACE_DESC ladderDesc;
                ladderTexture->GetLevelDesc(0, &ladderDesc); // Get the width and height of the ladder sprite

                float ladderWidth = ladderDesc.Width;
                float ladderHeight = ladderDesc.Height;

                // Calculate how many ladders can fit within the height of the bounding box
                float ladderBoundingBoxHeight = ladderBoundingBox.bottom - ladderBoundingBox.top;
                int ladderCount = static_cast<int>(ladderBoundingBoxHeight / ladderHeight);

                // Draw multiple ladders for the left bounding box
                for (int i = 0; i < ladderCount; ++i) {
                    float ladderPosX = (ladderBoundingBox.left + ladderBoundingBox.right) / 2 - ladderWidth / 2;
                    float ladderPosY = ladderBoundingBox.top + i * ladderHeight;  // Stack ladders vertically

                    D3DXVECTOR3 ladderPos(ladderPosX, ladderPosY, 0.0f);
                    sprite->Draw(ladderTexture, NULL, NULL, &ladderPos, D3DCOLOR_XRGB(255, 255, 255));
                }

                // Draw multiple ladders for the right bounding box
                float ladderBoundingBoxHeightRight = ladderBoundingBoxRight.bottom - ladderBoundingBoxRight.top;
                int ladderCountRight = static_cast<int>(ladderBoundingBoxHeightRight / ladderHeight);

                for (int i = 0; i < ladderCountRight; ++i) {
                    float ladderPosXRight = (ladderBoundingBoxRight.left + ladderBoundingBoxRight.right) / 2 - ladderWidth / 2;
                    float ladderPosYRight = ladderBoundingBoxRight.top + i * ladderHeight;  // Stack ladders vertically

                    D3DXVECTOR3 ladderPosRight(ladderPosXRight, ladderPosYRight, 0.0f);
                    sprite->Draw(ladderTexture, NULL, NULL, &ladderPosRight, D3DCOLOR_XRGB(255, 255, 255));
                }
            }


            if (appleTexture) {
                for (int i = 0; i < 3; i++) {
                    if (!applesCollected[i]) {  // Only render if apple has not been collected
                        sprite->Draw(appleTexture, NULL, NULL, &applePositions[i], D3DCOLOR_XRGB(255, 255, 255));
                    }
                }
            }

            sprite->End();  // End sprite rendering
        }


        if (line) {
            D3DXVECTOR2 lines[5]; // 4 lines, but need 5 points to close the rectangle

            line->SetWidth(2.0f);  // Line thickness
            line->Begin();

            D3DCOLOR lineColor = D3DCOLOR_XRGB(255, 0, 0);  // Red color

            for (int i = 0; i < 4; i++) {
                RECT platformRect = platformBoundingBoxes[i];

                // Set the points for the bounding box (rectangle)
                lines[0] = D3DXVECTOR2(platformRect.left, platformRect.top);     // Top-left
                lines[1] = D3DXVECTOR2(platformRect.right, platformRect.top);    // Top-right
                lines[2] = D3DXVECTOR2(platformRect.right, platformRect.bottom); // Bottom-right
                lines[3] = D3DXVECTOR2(platformRect.left, platformRect.bottom);  // Bottom-left
                lines[4] = lines[0];  // Close the rectangle

                // Draw the lines around the platform
                line->Draw(lines, 5, lineColor);
            }

            // Draw ladder bounding boxes
            D3DCOLOR ladderLineColor = D3DCOLOR_XRGB(0, 255, 0);  // Green color for ladders

            // Draw left ladder bounding box
            lines[0] = D3DXVECTOR2(ladderBoundingBox.left, ladderBoundingBox.top);     // Top-left
            lines[1] = D3DXVECTOR2(ladderBoundingBox.right, ladderBoundingBox.top);    // Top-right
            lines[2] = D3DXVECTOR2(ladderBoundingBox.right, ladderBoundingBox.bottom); // Bottom-right
            lines[3] = D3DXVECTOR2(ladderBoundingBox.left, ladderBoundingBox.bottom);  // Bottom-left
            lines[4] = lines[0];  // Close the rectangle

            // Draw the ladder lines
            line->Draw(lines, 5, ladderLineColor);

            // Draw right ladder bounding box
            lines[0] = D3DXVECTOR2(ladderBoundingBoxRight.left, ladderBoundingBoxRight.top);     // Top-left
            lines[1] = D3DXVECTOR2(ladderBoundingBoxRight.right, ladderBoundingBoxRight.top);    // Top-right
            lines[2] = D3DXVECTOR2(ladderBoundingBoxRight.right, ladderBoundingBoxRight.bottom); // Bottom-right
            lines[3] = D3DXVECTOR2(ladderBoundingBoxRight.left, ladderBoundingBoxRight.bottom);  // Bottom-left
            lines[4] = lines[0];  // Close the rectangle

            // Draw the ladder lines
            line->Draw(lines, 5, ladderLineColor);

            line->End();
        }

        // Draw blue line around Gork
        if (line) {
            line->SetWidth(2.0f);  // Set line thickness
            line->Begin();
            D3DCOLOR lineColor = D3DCOLOR_XRGB(0, 0, 255);  // Blue color

            D3DXVECTOR2 gorkLines[5] = {
                D3DXVECTOR2(gorkPosX, gorkPosY),  // Top-left
                D3DXVECTOR2(gorkPosX + gorkWidth, gorkPosY),  // Top-right
                D3DXVECTOR2(gorkPosX + gorkWidth, gorkPosY + gorkHeight),  // Bottom-right
                D3DXVECTOR2(gorkPosX, gorkPosY + gorkHeight),  // Bottom-left
                D3DXVECTOR2(gorkPosX, gorkPosY)  // Back to top-left to close the rectangle
            };

            line->Draw(gorkLines, 5, lineColor);
            line->End();
        }

        // Draw red line around Militia
        if (line) {
            line->SetWidth(2.0f);  // Set line thickness
            line->Begin();
            D3DCOLOR lineColor = D3DCOLOR_XRGB(255, 0, 0);  // Red color

            D3DXVECTOR2 militiaLines[5] = {
                D3DXVECTOR2(militiaPosX, militiaPosY),  // Top-left
                D3DXVECTOR2(militiaPosX + militiaWidth, militiaPosY),  // Top-right
                D3DXVECTOR2(militiaPosX + militiaWidth, militiaPosY + militiaHeight),  // Bottom-right
                D3DXVECTOR2(militiaPosX, militiaPosY + militiaHeight),  // Bottom-left
                D3DXVECTOR2(militiaPosX, militiaPosY)  // Back to top-left to close the rectangle
            };

            line->Draw(militiaLines, 5, lineColor);
            line->End();
        }


        if (militiafont) {
            string militiaName = "P1";  // The name to display
            RECT nameRect;
            nameRect.left = militiaPosX;
            nameRect.top = (militiaPosY - 30);  // Position 30 pixels above the militia
            nameRect.right = (militiaPosX + militiaWidth);
            nameRect.bottom = (militiaPosY);  // Bottom part of the text rectangle

            // Draw the text in the center of the militia sprite
            font->DrawText(NULL, militiaName.c_str(), -1, &nameRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
        }

        if (gorkfont) {
            string militiaName = "P2";  // The name to display
            RECT nameRect;
            nameRect.left = gorkPosX;
            nameRect.top = (gorkPosY - 30);  // Position 30 pixels above the militia
            nameRect.right = (gorkPosX + gorkWidth);
            nameRect.bottom = (gorkPosY);  // Bottom part of the text rectangle


            font->DrawText(NULL, militiaName.c_str(), -1, &nameRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
        }

        // Render the countdown timer text
        if (font) {


            RECT timerRect;
            int textWidth = 200;  // Rough estimate of text width
            int textHeight = 50;  // Rough estimate of text height

            timerRect.left = (windowScreenWidth / 2) - (textWidth / 2);
            timerRect.top = 50;  // Adjust for top positioning
            timerRect.right = (windowScreenWidth / 2) + (textWidth / 2);
            timerRect.bottom = timerRect.top + textHeight;

            std::string countdownText = "Time left: " + std::to_string((int)countdownTime) + "s";
            cout << countdownText << endl;  // Debugging: Print countdown value

            // Draw the countdown timer text on top of the background
            font->DrawText(NULL, countdownText.c_str(), -1, &timerRect, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0));
        }

        // Render the apple collection status
        if (font) {
            RECT appleCountRect;
            int appleTextWidth = 450;  // Rough estimate of text width
            int appleTextHeight = 50;  // Rough estimate of text height

            appleCountRect.left = windowScreenWidth - appleTextWidth - 20;  // Position on the left side
            appleCountRect.top = 20;  // Adjust for top positioning (you can change this if needed)
            appleCountRect.right = windowScreenWidth - 20;
            appleCountRect.bottom = appleCountRect.top + appleTextHeight;

            // Calculate how many apples are left to collect
            int applesLeftToCollect = 3 - collectedApples;
            std::string appleCountText = "P1 Left: [" + std::to_string(applesLeftToCollect) + "] apples to collect to Win the game";

            // Draw the apple count text at the top left
            font->DrawText(NULL, appleCountText.c_str(), -1, &appleCountRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));

            RECT p2CatchRect;
            p2CatchRect.left = windowScreenWidth - appleTextWidth - 20;  // Same horizontal alignment
            p2CatchRect.top = appleCountRect.bottom + 10;  // Position directly below the P1 text, with some spacing
            p2CatchRect.right = windowScreenWidth - 20;
            p2CatchRect.bottom = p2CatchRect.top + appleTextHeight;

            // Message for Player 2
            std::string p2CatchText = "P2 has to catch P1 to win the game!";


            font->DrawText(NULL, p2CatchText.c_str(), -1, &p2CatchRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));

        }

        // Render control instructions at the top-left corner (one row per control)
        if (font) {
            RECT instructionRect;
            instructionRect.left = 10;
            instructionRect.top = 10;  // Top-left position
            instructionRect.right = 400;  // Set enough width for the text

            // Display each instruction on a new line
            std::string instructions[] = {
                "-----P1-----",
                "A = move left",
                "D = move right",
                "W = climb / Jump",

            };

            // Render each instruction with a small vertical offset
            for (int i = 0; i < 4; i++) {
                instructionRect.top = 10 + (i * 20);  // Set each instruction 20 pixels apart
                instructionRect.bottom = instructionRect.top + 20;
                font->DrawText(NULL, instructions[i].c_str(), -1, &instructionRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
            }

            instructionRect.top += 40;

            std::string instructionsP2[] = {
                "-----P2-----",
                "Left Arrow = move left",
                "Right Arrow = move right",
                "Up Arrow = jump"
            };

            for (int i = 0; i < 4; i++) {
                instructionRect.top += 20;  // Set each instruction 20 pixels apart
                instructionRect.bottom = instructionRect.top + 20;
                font->DrawText(NULL, instructionsP2[i].c_str(), -1, &instructionRect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
            }
        }

        d3dDevice->EndScene();
        d3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

void Game::Logic() {
    float gorkMoveX = 0.0f;
    float gorkMoveY = 0.0f;

    // Handle movement (left/right)
    if (inputManager.isKeyPressed(DIK_LEFT)) {
        gorkMoveX -= gorkMoveSpeed * deltaTime;
        gorkCurrentState = GORK_WALK_LEFT;
    }
    else if (inputManager.isKeyPressed(DIK_RIGHT)) {
        gorkMoveX += gorkMoveSpeed * deltaTime;
        gorkCurrentState = GORK_WALK_RIGHT;
    }
    else {
        gorkCurrentState = GORK_IDLE;
    }


    // Jump logic: allow jumping only when on the ground or platform
    if ((inputManager.isKeyPressed(DIK_UP)) && !gorkIsJumping) {
        gorkIsJumping = true;
        gorkJumpVelocity = -gorkjumpForce;  // Apply an initial upward velocity
        gorkCurrentState = GORK_JUMP;
        audioManager->PlaySound4();

    }

    // Gravity applies if in the air (falling or jumping)
    gorkJumpVelocity += gravity * deltaTime;
    gorkMoveY += gorkJumpVelocity * deltaTime;  // Apply vertical velocity to movement

    // Update Gork's position
    gorkPosX += gorkMoveX;
    gorkPosY += gorkMoveY;

    // Clamp Gork's position to the screen
    gorkPosX = clamp(gorkPosX, 0, windowScreenWidth - gorkWidth);
    if (gorkPosX <= 0 || gorkPosX >= windowScreenWidth - gorkWidth) {
        if (!HitSide) {
            HitSide = true;  // Set flag to true so it doesn't play again
            audioManager->PlaySound1();  // Play the sound when hitting the sides
        }
    }
    else {
        HitSide = false;  // Reset flag when the militia moves away from the sides
    }

    gorkPosY = clamp(gorkPosY, 0, windowScreenHeight - gorkHeight);
    if (gorkPosY <= 0 || gorkPosY >= windowScreenWidth - gorkWidth) {
        if (!HitSide) {
            audioManager->PlaySound1();  // Play the sound when hitting the sides
            HitSide = true;  // Set flag to true so it doesn't play again
        }
    }
    else {
        HitSide = false;  // Reset flag when the militia moves away from the sides
    }

    // Check if Gork has landed on the ground
    bool gorkOnGround = gorkPosY >= windowScreenHeight - gorkHeight;  // On the ground

    // Reset jump state if Gork is on the ground
    if (gorkOnGround) {
        gorkPosY = windowScreenHeight - gorkHeight;  // Clamp to the ground level
        gorkIsJumping = false;  // Gork has landed, allow jumping again
        gorkJumpVelocity = 0.0f;  // Reset vertical velocity
    }

    // Check if Gork has landed on a platform (you may need a platform collision detection function here)
    bool gorkOnPlatform = false;
    for (int i = 0; i < 4; i++) {
        RECT platformRect = platformBoundingBoxes[i];

        // Check if Gork is landing on the top of a platform
        if (gorkPosY + gorkHeight >= platformRect.top &&  // Gork's feet are below platform top
            gorkPosY <= platformRect.top &&  // Small threshold for collision accuracy
            gorkPosX + gorkWidth > platformRect.left &&  // Gork's right side is past platform's left edge
            gorkPosX < platformRect.right &&              // Gork's left side is before platform's right edge
            gorkJumpVelocity >= 0) {                      // Only apply when falling (not jumping)

            gorkPosY = platformRect.top - gorkHeight;  // Snap Gork to the top of the platform
            gorkIsJumping = false;  // Gork has landed on a platform
            gorkJumpVelocity = 0.0f;  // Reset vertical velocity
            gorkOnPlatform = true;    // Mark Gork as on the platform
        }

        // Check if Gork hits the bottom of a platform when jumping
        if (gorkPosY <= platformRect.bottom && gorkPosY + gorkHeight > platformRect.bottom &&
            gorkPosX + gorkWidth > platformRect.left && gorkPosX < platformRect.right && gorkJumpVelocity < 0) {
            gorkPosY = platformRect.bottom;
            gorkJumpVelocity = 0.0f;  // Stop upward movement
        }

        // Prevent moving through the left side of the platform
        if (gorkPosX + gorkWidth >= platformRect.left && gorkPosX + gorkWidth <= platformRect.left + 5 &&
            gorkPosY + gorkHeight > platformRect.top && gorkPosY < platformRect.bottom) {
            gorkPosX = platformRect.left - gorkWidth;  // Stop character at the left edge of the platform
        }

        // Prevent moving through the right side of the platform
        if (gorkPosX <= platformRect.right && gorkPosX >= platformRect.right - 5 &&
            gorkPosY + gorkHeight > platformRect.top && gorkPosY < platformRect.bottom) {
            gorkPosX = platformRect.right;  // Stop character at the right edge of the platform
        }
    }

    // If Gork is falling and not on the ground or platform, apply gravity
    if (!gorkOnGround && !gorkOnPlatform) {
        gorkIsJumping = true;  // Set jumping state
    }

    // Clamp Gork's position to the screen
    gorkPosX = clamp(gorkPosX, 0, windowScreenWidth - gorkWidth);
    gorkPosY = clamp(gorkPosY, 0, windowScreenHeight - gorkHeight);

    // Default movement is zero (stops the character when no key is pressed)
    float moveX = 0.0f;
    float moveY = 0.0f;

    // Handle directional input and move the sprite accordingly
    if (inputManager.isKeyPressed(DIK_A)) {
        moveX -= militiamoveSpeed * deltaTime;
        currentState = MILITIA_WALK_LEFT;  // Move left
    }
    else if (inputManager.isKeyPressed(DIK_D)) {
        moveX += militiamoveSpeed * deltaTime;
        currentState = MILITIA_WALK_RIGHT; // Move right
    }
    else {
        currentState = MILITIA_IDLE;
    }

    // Handle ladder climbing logic
    if (isOnLadder()) {
        if (inputManager.isKeyPressed(DIK_W)) {
            moveY -= militiamoveSpeed * deltaTime;  // Climb upwards when W is pressed
            isJumping = false;  // Disable jumping while on the ladder
            jumpVelocity = 0.0f;  // Disable gravity while on the ladder

        }
        else if (inputManager.isKeyPressed(DIK_S)) {
            moveY += militiamoveSpeed * deltaTime;  // Descend the ladder when S is pressed
            isJumping = false;  // Disable jumping while on the ladder
            jumpVelocity = 0.0f;  // Disable gravity while on the ladder
        }
    }
    else {
        // Handle jump logic if not on the ladder
        if ((inputManager.isKeyPressed(DIK_W)) && !isJumping) {
            isJumping = true;            // Start the jump
            jumpVelocity = -jumpForce;   // Apply an initial upward velocity
            audioManager->PlaySound4();
        }

        // Apply gravity if jumping or falling
        jumpVelocity += gravity * deltaTime;  // Gravity pulls the character down
        moveY += jumpVelocity * deltaTime;    // Add the velocity to the Y movement
    }

    // Update the character's position based on movement
    militiaPosX += moveX;
    militiaPosY += moveY;

    militiaPosX = clamp(militiaPosX, 0, windowScreenWidth - militiaWidth);
    if (militiaPosX <= 0 || militiaPosX >= windowScreenWidth - militiaWidth) {
        if (!HitSide) {
            audioManager->PlaySound1();  // Play the sound when hitting the sides
            HitSide = true;  // Set flag to true so it doesn't play again
        }
    }
    else {
        HitSide = false;  // Reset flag when the militia moves away from the sides
    }


    // Check for vertical collisions with platforms
    bool isOnPlatform = false;
    for (int i = 0; i < 4; i++) {
        RECT platformRect = platformBoundingBoxes[i];

        // Check if the character is landing on the top of the platform
        if (militiaPosY + militiaHeight >= platformRect.top &&  // Character's feet are below platform top
            militiaPosY <= platformRect.top &&  // Character was above platform in the previous frame
            militiaPosX + militiaWidth > platformRect.left &&  // Character's right side is past platform's left edge
            militiaPosX < platformRect.right &&  // Character's left side is before platform's right edge
            jumpVelocity >= 0) {  // Only apply when falling (not jumping)

            // Allow the player to pass through the platform if they are pressing the down key
            if (!(inputManager.isKeyPressed(DIK_S)) && !isOnLadder()) {
                // Snap the character to the top of the platform
                militiaPosY = platformRect.top - militiaHeight;
                isJumping = false;  // Reset jump state
                jumpVelocity = 0.0f;  // Stop downward movement
                isOnPlatform = true;  // Mark the character as standing on a platform
            }
        }


        // Prevent moving through the left side of the platform
        if (militiaPosX + militiaWidth >= platformRect.left && militiaPosX + militiaWidth <= platformRect.left + 5 &&
            militiaPosY + militiaHeight > platformRect.top && militiaPosY < platformRect.bottom) {
            militiaPosX = platformRect.left - militiaWidth;  // Stop character at the left edge of the platform
        }

        // Prevent moving through the right side of the platform
        if (militiaPosX <= platformRect.right && militiaPosX >= platformRect.right - 5 &&
            militiaPosY + militiaHeight > platformRect.top && militiaPosY < platformRect.bottom) {
            militiaPosX = platformRect.right;  // Stop character at the right edge of the platform
        }

        // Check if character hits the bottom of a platform when jumping
        if (militiaPosY <= platformRect.bottom && militiaPosY + militiaHeight > platformRect.bottom &&
            militiaPosX + militiaWidth > platformRect.left && militiaPosX < platformRect.right && jumpVelocity < 0) {
            militiaPosY = platformRect.bottom;
            jumpVelocity = 0.0f;  // Stop upward movement
        }


        if (militiaPosY <= 0 && jumpVelocity < 0) {
            militiaPosY = 0;  // Clamp character's Y position to the top of the window
            jumpVelocity = 0.0f;  // Stop upward movement
        }

        // If the character is not on any platform and not jumping, apply gravity
        if (!isOnPlatform && militiaPosY >= windowScreenHeight - militiaHeight) {
            militiaPosY = windowScreenHeight - militiaHeight;  // Clamp to the ground level
            isJumping = false;
            jumpVelocity = 0.0f;
        }



        // Ensure the character doesn't go above the window
        militiaPosY = clamp(militiaPosY, 0, windowScreenHeight - militiaHeight);
        if (militiaPosY <= 0) {
            if (!HitTop) {
                audioManager->PlaySound1();  // Play the sound when hitting the top
                HitTop = true;  // Set flag to true so it doesn't play again
            }
        }
        else {
            HitTop = false;  // Reset flag when the militia moves away from the top
        }

    }



    // Check for collisions with apples and mark them as collected
    bool allApplesCollected = true;
    for (int i = 0; i < 3; i++) {
        if (!applesCollected[i]) {
            allApplesCollected = false;  // Not all apples collected yet

            if (checkCollision(D3DXVECTOR3(militiaPosX, militiaPosY, 0), applePositions[i], 50.0f)) {
                applesCollected[i] = true;  // Mark apple as collected
                collectedApples++;

                audioManager->PlaySound2();

                cout << "Collected Apple: " << i + 1 << endl;
            }
        }
    }

    if (gorkPosX < militiaPosX + militiaWidth && gorkPosX + gorkWidth > militiaPosX &&
        gorkPosY < militiaPosY + militiaHeight && gorkPosY + gorkHeight > militiaPosY) {


        MessageBox(g_hWnd, "Player 2 (Gork) caught Player 1 (Militia)! Game Over!", "Game Over", MB_OK);

        // End the game
        PostQuitMessage(0);
    }


    updateMilitiaAnimation(deltaTime);
    updateGorkAnimation(deltaTime);

    // Once all apples are collected, then display the win message
    if (allApplesCollected && countdownTime > 0) {
        MessageBox(g_hWnd, "PLAYER 1 Win!", "hehe", MB_OK);
        Exit();
    }

    // Update the countdown timer
    countdownTime -= deltaTime;
    if (countdownTime <= 0) {
        countdownTime = 0;
        MessageBox(g_hWnd, "Time's up!", "Player 2 Win the Game", MB_OK);
        Exit();
    }
}

bool Game::isOnLadder() {
    RECT militiaRect;
    militiaRect.left = (LONG)militiaPosX;
    militiaRect.top = (LONG)militiaPosY;
    militiaRect.right = militiaRect.left + militiaWidth;
    militiaRect.bottom = militiaRect.top + militiaHeight;


    // Check collision with left or right ladder
    if ((militiaRect.left < ladderBoundingBox.right && militiaRect.right > ladderBoundingBox.left &&
        militiaRect.top < ladderBoundingBox.bottom && militiaRect.bottom > ladderBoundingBox.top) ||
        (militiaRect.left < ladderBoundingBoxRight.right && militiaRect.right > ladderBoundingBoxRight.left &&
            militiaRect.top < ladderBoundingBoxRight.bottom && militiaRect.bottom > ladderBoundingBoxRight.top)) {
        return true;  // Militia is on the ladder
    }

    return false;  // Militia is not on the ladder
}

void Game::updateBoundingBox() {

    int platformWidth = 315;  // Actual width of the platform
    int platformHeight = 50; // Actual height of the platform
    int buffer = 1;  // The size of the apple (buffer space around the platform)

    for (int i = 0; i < 4; i++) {
        platformBoundingBoxes[i].left = static_cast<LONG>(platformPositions[i].x + buffer);
        platformBoundingBoxes[i].top = static_cast<LONG>(platformPositions[i].y + buffer);
        platformBoundingBoxes[i].right = platformBoundingBoxes[i].left + platformWidth + buffer;
        platformBoundingBoxes[i].bottom = platformBoundingBoxes[i].top + platformHeight + buffer;
    }

    // Ladder bounding box (adjust according to your ladder positions)
    ladderBoundingBox.left = 50;  // X-position of the left ladder
    ladderBoundingBox.top = (windowScreenHeight / 2) - (644 / 10);  // Y-position of the ladder
    ladderBoundingBox.right = ladderBoundingBox.left + 50;  // Adjust ladder width
    ladderBoundingBox.bottom = ladderBoundingBox.top + 644;  // Adjust ladder height

    // Right ladder
    ladderBoundingBoxRight.left = windowScreenWidth - 257 - 50;
    ladderBoundingBoxRight.top = (windowScreenHeight / 2) - (644 / 3);
    ladderBoundingBoxRight.right = ladderBoundingBoxRight.left + 50;
    ladderBoundingBoxRight.bottom = ladderBoundingBoxRight.top + 644;
}

bool Game::checkCollision(D3DXVECTOR3 obj1, D3DXVECTOR3 obj2, float range) {
    float distance = sqrt(pow(obj1.x - obj2.x, 2) + pow(obj1.y - obj2.y, 2));
    return distance < range;
}

bool Game::checkCollisionWithPlatform(D3DXVECTOR3 applePos) {
    RECT appleRect;
    int appleSize = 50;  // Assuming the apple sprite is 50x50 pixels

    // Convert the 3D position of the apple into a 2D RECT for collision checking
    appleRect.left = (LONG)applePos.x;
    appleRect.top = (LONG)applePos.y;
    appleRect.right = appleRect.left + appleSize;
    appleRect.bottom = appleRect.top + appleSize;

    // Check if the apple's bounding box intersects with any platform's bounding box
    for (int i = 0; i < 4; i++) {
        RECT platformRect = platformBoundingBoxes[i];

        if (appleRect.left < platformRect.right &&
            appleRect.right > platformRect.left &&
            appleRect.top < platformRect.bottom &&
            appleRect.bottom > platformRect.top) {
            return true;  // Collision detected
        }
    }

    return false;  // No collision
}

void Game::randomizeApplePositions() {
    int screenWidth = windowScreenWidth;  // Use the actual game screen width
    int screenHeight = windowScreenHeight;  // Use the actual game screen height
    int min = 100;
    int max = 100;
    int randomRangeX = max - min;

    if (randomRangeX <= 0) {
        randomRangeX = 1;  // Set a minimum valid range
    }
    for (int i = 0; i < 3; i++) {
        bool validPosition = false;
        while (!validPosition) {
            // Randomize apple positions within the screen bounds
            
            int randomX = min + rand() % randomRangeX;
            int randomY = min + rand() % (screenHeight - min);

            D3DXVECTOR3 potentialPos((float)randomX, (float)randomY, 0.0f);

            // Ensure that the apple's position doesn't collide with any platform
            if (!checkCollisionWithPlatform(potentialPos)) {
                applePositions[i] = potentialPos;
                validPosition = true;
            }
        }
    }
}

// Function to update gork's animation
void Game::updateGorkAnimation(float deltaTime1) {
    static float gorkFrameTimer = 0.0f;  // Separate frame timer for Gork
    gorkFrameTimer += deltaTime1;

    // Check if the state has changed, and if so, reset to the start frame
    if (gorkCurrentState != gorkPreviousState) {
        switch (gorkCurrentState) {
        case GORK_WALK_LEFT:
            gorkFrames = gork_walkLeft.gork_startFrame;
            break;
        case GORK_WALK_RIGHT:
            gorkFrames = gork_walkRight.gork_startFrame;
            break;
        case GORK_JUMP:
            gorkFrames = gork_jump.gork_startFrame;
            break;
        default:
            gorkFrames = gork_idle.gork_startFrame;
            break;
        }
        gorkPreviousState = gorkCurrentState;  // Update previous state
    }

    // Proceed with frame update based on the timer
    if (gorkFrameTimer >= frameTime2) {
        gorkFrameTimer = 0.0f;  // Reset the timer

        // Update the Gork frames based on the current state
        gorkanimmation gorkcurrentAnim;
        switch (gorkCurrentState) {
        case GORK_WALK_LEFT:
            gorkcurrentAnim = gork_walkLeft;
            break;
        case GORK_WALK_RIGHT:
            gorkcurrentAnim = gork_walkRight;
            break;
        case GORK_JUMP:
            gorkcurrentAnim = gork_jump;
            break;
        default:
            gorkcurrentAnim = gork_idle;
            break;
        }

        // Move to the next frame within the animation range
        gorkFrames++;
        if (gorkFrames > gorkcurrentAnim.gork_endFrame) {
            gorkFrames = gorkcurrentAnim.gork_startFrame;  // Loop back to the start frame
        }

        // Calculate the current row and column in the sprite sheet
        gorkcRow = gorkFrames / gorkColumn;
        gorkcCol = gorkFrames % gorkColumn;
    }
}

// Function to update militia's animation
void Game::updateMilitiaAnimation(float deltaTime) {
    static float militiaFrameTimer = 0.0f;  // Separate frame timer for militia
    militiaFrameTimer += deltaTime;

    // Check if the state has changed, and if so, reset to the start frame
    if (currentState != previousState) {
        switch (currentState) {
        case MILITIA_WALK_LEFT:
            militiaFrames = militia_walkLeft.militia_startFrame;
            break;
        case MILITIA_WALK_RIGHT:
            militiaFrames = militia_walkRight.militia_startFrame;
            break;
        default:
            militiaFrames = militia_idle.militia_startFrame;
            break;
        }
        previousState = currentState;  // Update previous state
    }

    // Proceed with frame update based on the timer
    if (militiaFrameTimer >= frameTime1) {
        militiaFrameTimer = 0.0f;  // Reset the timer

        // Update the militiaFrames based on the current state
        Animation currentAnim1;
        switch (currentState) {
        case MILITIA_WALK_LEFT:
            currentAnim1 = militia_walkLeft;
            break;
        case MILITIA_WALK_RIGHT:
            currentAnim1 = militia_walkRight;
            break;
        default:
            currentAnim1 = militia_idle;
            break;
        }

        // Move to the next frame within the animation range
        militiaFrames++;
        if (militiaFrames > currentAnim1.militia_endFrame) {
            militiaFrames = currentAnim1.militia_startFrame;  // Loop back to the start frame
        }

        // Calculate the current row and column in the sprite sheet
        militiacRow = militiaFrames / militiaColumn;
        militiacCol = militiaFrames % militiaColumn;
    }
}

void Game::cleanup() {
    if (backgroundTexture) backgroundTexture->Release();
    if (sprite) sprite->Release();
    if (line) line->Release();
    if (font) font->Release();

    backgroundTexture = nullptr;
    sprite = nullptr;
    line = nullptr;
    font = nullptr;
}