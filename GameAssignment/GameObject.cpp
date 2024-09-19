#include "GameObject.h"
#include "WindowManager.h"
#include <string>

// Constructor
GameObject::GameObject(HRESULT hr, LPD3DXLINE line, D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight)
    : platformTexture(nullptr), ladderTexture(nullptr), appleTexture(nullptr), font(nullptr) {
    // Initialize the positions and bounding boxes
}

// Destructor
GameObject::~GameObject() {
    if (platformTexture) platformTexture->Release();
    if (ladderTexture) ladderTexture->Release();
    if (appleTexture) appleTexture->Release();
    if (font) font->Release();
}

D3DXVECTOR3 platformPositions[4] = {
    D3DXVECTOR3(600.0f, 425.0f, 0.0f),
    D3DXVECTOR3(0.0f, 300.0f, 0.0f),
    D3DXVECTOR3(800.0f, 150.0f, 0.0f),
    D3DXVECTOR3(230.0f, 100.0f, 0.0f),
};

D3DXVECTOR2 lines[5]; // 4 lines, but need 5 points to close the rectangle
HRESULT hr;
GraphicDevice* device;
IDirect3DDevice9* d3dDevice = device->getDirectDevice();

WindowManager* window;
int windowScreenHeight = window->getHeight();
int windowScreenWidth = window->getWidth();


void GameObject::render(HRESULT hr, LPD3DXSPRITE sprite, LPD3DXLINE line ) {
    hr = D3DXCreateSprite(d3dDevice, &sprite);
    if (FAILED(hr)) {
        cout << "Failed to create sprite" << endl;
    }
    
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

void GameObject::Update(D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight) { 
    if (d3dDevice) {
        

        if (sprite) {
            sprite->Begin(D3DXSPRITE_ALPHABLEND);  // Start sprite rendering with alpha blending

            if (appleTexture) {
                for (int i = 0; i < 3; i++) {
                    if (!applesCollected[i]) {  // Only render if apple has not been collected
                        sprite->Draw(appleTexture, NULL, NULL, &applePositions[i], D3DCOLOR_XRGB(255, 255, 255));
                    }
                }
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

        sprite->End();  // End sprite rendering
    }

    drawPlatformBoundingBoxes(hr, line, platformPositions, platformBoundingBoxes, ladderBoundingBox, ladderBoundingBoxRight);

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
}


void GameObject::drawPlatformBoundingBoxes(HRESULT hr, LPD3DXLINE line, D3DXVECTOR3 platformPositions[4], RECT platformBoundingBoxes[4], RECT ladderBoundingBox, RECT ladderBoundingBoxRight) {

    if (line) {
        

        hr = D3DXCreateLine(d3dDevice, &line);
        if (FAILED(hr)) {
            cout << "Failed to create line" << endl;
        }

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
}






