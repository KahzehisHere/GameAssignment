//#include "GameCharacter.h"
//
//GameCharacter::GameCharacter() {
//
//}
//
//GameCharacter::~GameCharacter() {
//    if (militiaTexture) militiaTexture->Release();
//    if (gorkTexture) gorkTexture->Release();
//    if (font) font->Release();
//}
//
//GameCharacter& GameCharacter::getInstance() {
//    static GameCharacter instance;  // Static instance for singleton
//    return instance;
//}
//
//void GameCharacter::render(HRESULT hr, LPD3DXSPRITE sprite) {
//    GraphicDevice& device = GraphicDevice::getInstance();
//    d3dDevice = device.getDirectDevice();
//    
//    hr = D3DXCreateSprite(d3dDevice, &sprite);
//    if (FAILED(hr)) {
//        cout << "Failed to create sprite" << endl;
//    }
//
//    hr = D3DXCreateLine(d3dDevice, &line);
//    if (FAILED(hr)) {
//        cout << "Failed to create line" << endl;
//    }
//
//    hr = D3DXCreateTextureFromFile(d3dDevice, "militia.png", &militiaTexture);  // Load the militia texture
//    if (FAILED(hr)) {
//        cout << "Failed to load militia texture" << endl;
//    }
//
//    hr = D3DXCreateTextureFromFile(d3dDevice, "gorksprite.png", &gorkTexture);  // Load the second player texture
//    if (FAILED(hr)) {
//        cout << "Failed to load gorktexture.png" << endl;
//    }
//
//    hr = D3DXCreateFont(d3dDevice, 8, 0, FW_NORMAL, 1, false,
//        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
//        DEFAULT_PITCH | FF_DONTCARE, "Arial", &gorkfont);
//
//
//    hr = D3DXCreateFont(d3dDevice, 8, 0, FW_NORMAL, 1, false,
//        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
//        DEFAULT_PITCH | FF_DONTCARE, "Arial", &militiafont);
//
//    if (d3dDevice) {
//        
//        if (sprite) {
//            sprite->Begin(D3DXSPRITE_ALPHABLEND);  // Start sprite rendering with alpha blending
//
//            if (gorkTexture) {
//                RECT gorkRect;
//                gorkRect.left = militiacCol * gorkWidth;  // Use same frame logic as militia for simplicity
//                gorkRect.right = gorkRect.left + gorkWidth;
//                gorkRect.top = militiacRow * gorkHeight;
//                gorkRect.bottom = gorkRect.top + gorkHeight;
//
//                D3DXVECTOR3 gorkPos(gorkPosX, gorkPosY, 0);
//                sprite->Draw(gorkTexture, &gorkRect, NULL, &gorkPos, D3DCOLOR_XRGB(255, 255, 255));
//            }
//
//
//            // Render the animated militia sprite
//            if (militiaTexture) {
//                RECT militiaRect;
//                militiaRect.left = militiacCol * militiaWidth;
//                militiaRect.right = militiaRect.left + militiaWidth;
//                militiaRect.top = militiacRow * militiaHeight;
//                militiaRect.bottom = militiaRect.top + militiaHeight;
//
//                D3DXVECTOR3 militiaPos(militiaPosX, militiaPosY, 0);  // Use updated positions
//                sprite->Draw(militiaTexture, &militiaRect, NULL, &militiaPos, D3DCOLOR_XRGB(255, 255, 255));
//            }
//        }
//        sprite->End();  // End sprite rendering
//
//        if (line) {
//            line->SetWidth(2.0f);  // Set line thickness
//            line->Begin();
//            D3DCOLOR lineColor = D3DCOLOR_XRGB(0, 0, 255);  // Blue color
//
//            D3DXVECTOR2 gorkLines[5] = {
//                D3DXVECTOR2(gorkPosX, gorkPosY),  // Top-left
//                D3DXVECTOR2(gorkPosX + gorkWidth, gorkPosY),  // Top-right
//                D3DXVECTOR2(gorkPosX + gorkWidth, gorkPosY + gorkHeight),  // Bottom-right
//                D3DXVECTOR2(gorkPosX, gorkPosY + gorkHeight),  // Bottom-left
//                D3DXVECTOR2(gorkPosX, gorkPosY)  // Back to top-left to close the rectangle
//            };
//
//            line->Draw(gorkLines, 5, lineColor);
//            line->End();
//        }
//
//        if (line) {
//            line->SetWidth(2.0f);  // Set line thickness
//            line->Begin();
//            D3DCOLOR lineColor = D3DCOLOR_XRGB(255, 0, 0);  // Red color
//
//            D3DXVECTOR2 militiaLines[5] = {
//                D3DXVECTOR2(militiaPosX, militiaPosY),  // Top-left
//                D3DXVECTOR2(militiaPosX + militiaWidth, militiaPosY),  // Top-right
//                D3DXVECTOR2(militiaPosX + militiaWidth, militiaPosY + militiaHeight),  // Bottom-right
//                D3DXVECTOR2(militiaPosX, militiaPosY + militiaHeight),  // Bottom-left
//                D3DXVECTOR2(militiaPosX, militiaPosY)  // Back to top-left to close the rectangle
//            };
//
//            line->Draw(militiaLines, 5, lineColor);
//            line->End();
//        }
//
//        if (militiafont) {
//            string militiaName = "P1";  // The name to display
//            RECT nameRect;
//            nameRect.left = (LONG)militiaPosX;
//            nameRect.top = (LONG)(militiaPosY - 30);  // Position 30 pixels above the militia
//            nameRect.right = (LONG)(militiaPosX + militiaWidth);
//            nameRect.bottom = (LONG)(militiaPosY);  // Bottom part of the text rectangle
//
//            militiafont->DrawText(NULL, militiaName.c_str(), -1, &nameRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
//        }
//
//        if (gorkfont) {
//            string gorkName = "P2";  // The name to display
//            RECT nameRect;
//            nameRect.left = (LONG)gorkPosX;
//            nameRect.top = (LONG)(gorkPosY - 30);  // Position 30 pixels above the militia
//            nameRect.right = (LONG)(gorkPosX + gorkWidth);
//            nameRect.bottom = (LONG)(gorkPosY);  // Bottom part of the text rectangle
//
//            gorkfont->DrawText(NULL, gorkName.c_str(), -1, &nameRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
//        }
//        
//    }
//}
