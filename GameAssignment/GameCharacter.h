//#pragma once
//#include <d3dx9.h>
//#include <iostream>
//#include "GraphicDevice.h"
//#include "GameObject.h"
//
//class GameCharacter {
//public:
//    GameCharacter(LPDIRECT3DTEXTURE9 tex, int texWidth, int texHeight, int cols, int rows);
//    ~GameCharacter();
//    void render(HRESULT hr, LPD3DXSPRITE sprite);
//
//    LPD3DXSPRITE sprite;  
//    LPD3DXLINE line;
//    LPD3DXFONT font;
//    LPDIRECT3DTEXTURE9 militiaTexture;
//    LPDIRECT3DTEXTURE9 gorkTexture;
//    LPD3DXFONT militiafont;
//    LPD3DXFONT gorkfont;
//    GraphicDevice* device;
//    IDirect3DDevice9* d3dDevice = device->getDirectDevice();
//    GraphicDevice* graphicDevice;
//    int windowScreenWidth = graphicDevice->getScreenWidth();
//    int windowScreenHeight = graphicDevice->getScreenHeight();
//    float gorkPosX = static_cast<float>(windowScreenWidth / 2 - gorkWidth / 2);
//    float gorkPosY = static_cast<float>(windowScreenHeight / 2 - gorkHeight / 2);
//    float militiaPosX = static_cast<float>(windowScreenWidth / 2 - militiaWidth / 2);
//    float militiaPosY = static_cast<float>(windowScreenHeight / 2 - militiaHeight / 2);
//    int getgorkWidth() {
//        return gorkWidth;
//    }
//    int getgorkHeight() {
//        return gorkHeight;
//    }
//    int getmilitiaWidth() {
//        return militiaWidth;
//    }
//    int getmilitiaHeight() {
//        return militiaHeight;
//    }
//    int getmilitiaFrames() {
//        return militiaFrames;
//    }
//    int getgorkFrames() {
//        return gorkFrames;
//    }
//    int getgorkcurrentcol() {
//        return gorkcCol;
//    }
//    int getgorkcurrentrow() {
//        return gorkcRow;
//    }
//    int getmilitiacurrentcol() {
//        return militiacCol;
//    }
//    int getmilitiacurrentrow() {
//        return militiacRow;
//    }
//private:
//
//    int gorksheetWidth = 128;
//    int gorksheetHeight = 128;
//    int gorkColumn = 4;         
//    int gorkRow = 4;             
//    const int gorkWidth = gorksheetWidth / gorkColumn;    
//    const int gorkHeight = gorksheetHeight / gorkRow;
//    int gorkFrames = 0;
//    int maxgorkFrame = 16;
//    int gorkcRow = gorkFrames / gorkColumn;
//    int gorkcCol = gorkFrames % gorkColumn;
//    
//      
//    int militiasheetWidth = 128;
//    int militiasheetHeight = 255;
//    int militiaColumn = 4;         
//    int militiaRow = 4;             
//    const int militiaWidth = militiasheetWidth / militiaColumn;   
//    const int militiaHeight = militiasheetHeight / militiaRow;   
//    int militiaFrames = 0;     
//    int maxmilitiaFrame = 16;
//    int militiacRow = militiaFrames / militiaColumn;
//    int militiacCol = militiaFrames % militiaColumn;
//    
//};
