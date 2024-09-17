#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "WindowManager.h"

class GraphicDevice {
public:
    WindowManager windowManager;
    HWND hwnd = windowManager.getHWND();
    GraphicDevice(int width, int height);  // Constructor with screen dimensions
    IDirect3DDevice9* createDevice(HWND hWnd);  // Creates the device with the provided HWND
    void cleanup();
    int getScreenWidth() {
        return screenWidth;
    }

    int getScreenHeight() {
        return screenHeight;
    }

    IDirect3D9* getDirect3D(){
        return direct3D9;
    }

    IDirect3DDevice9* getDirectDevice() {
        return d3dDevice;
    }

private:

    IDirect3D9* direct3D9 = NULL;
    IDirect3DDevice9* d3dDevice = NULL;
    int screenWidth = 1280;  // Screen width
    int screenHeight = 720; // Screen height

    
};
