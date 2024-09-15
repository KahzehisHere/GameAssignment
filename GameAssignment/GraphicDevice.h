#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class GraphicDevice {
public:
    GraphicDevice(int width, int height);  // Constructor with screen dimensions
    IDirect3DDevice9* createDevice(HWND hWnd);  // Creates the device with the provided HWND
    void cleanup();  // Cleans up the device

private:
    IDirect3DDevice9* d3dDevice;  // Direct3D device object
    int screenWidth;  // Screen width
    int screenHeight; // Screen height
};
