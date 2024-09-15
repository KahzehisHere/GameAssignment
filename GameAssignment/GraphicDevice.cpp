#include "GraphicDevice.h"
#include "WindowManager.h"

// Constructor
GraphicDevice::GraphicDevice(int width, int height)
    : d3dDevice(nullptr), screenWidth(width), screenHeight(height) {}

// Function to create the Direct3D device
IDirect3DDevice9* GraphicDevice::createDevice(HWND hWnd) {
    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3d) {
        MessageBox(NULL, "Failed to create Direct3D", "Error", MB_OK);
        return nullptr;
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = screenWidth;
    d3dpp.BackBufferHeight = screenHeight;

    if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice))) {
        d3d->Release();
        return nullptr;
    }

    d3d->Release();
    return d3dDevice;
}

// Clean up the device
void GraphicDevice::cleanup() {
    if (d3dDevice) {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }
}
