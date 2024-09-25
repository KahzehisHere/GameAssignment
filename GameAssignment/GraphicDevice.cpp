#include "GraphicDevice.h"
#include "WindowManager.h"
#include <iostream>

// Private constructor to enforce singleton
GraphicDevice::GraphicDevice() : d3dDevice(nullptr), direct3D9(nullptr) {}

// Destructor
GraphicDevice::~GraphicDevice() {
    cleanup();
}


// Cleanup the device
void GraphicDevice::cleanup() {
    if (d3dDevice) {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }
    if (direct3D9) {
        direct3D9->Release();
        direct3D9 = nullptr;
    }
}

// Singleton instance getter
GraphicDevice& GraphicDevice::getInstance() {
    static GraphicDevice instance;
    return instance;
}

// Function to create the Direct3D device
IDirect3DDevice9* GraphicDevice::createDevice(HWND hWnd) {
    WindowManager& windowManager = WindowManager::getWindowManager();

    if (d3dDevice || direct3D9) {
        cleanup();  // Ensure we release any existing resources before reallocation
    }

    direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (!direct3D9) {
        cout << "Failed to create Direct3D9 interface." << endl;
        return nullptr;
    }

    D3DPRESENT_PARAMETERS d3dPP;
    ZeroMemory(&d3dPP, sizeof(d3dPP));
    d3dPP.Windowed = true;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;

    // Retrieve the window width and height from WindowManager
    int screenWidth = windowManager.getWidth();
    int screenHeight = windowManager.getHeight();

    // Check if screenWidth and screenHeight are valid
    if (screenWidth <= 0 || screenHeight <= 0) {
        cout << "Invalid screen dimensions." << endl;
        cleanup();
        return nullptr;
    }

    d3dPP.BackBufferWidth = screenWidth;
    d3dPP.BackBufferHeight = screenHeight;
    d3dPP.hDeviceWindow = hWnd;

    HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

    if (FAILED(hr)) {
        cout << "Failed to create Direct3D device. Error code: " << hr << endl;
        cleanup();  // Clean up in case of failure
        return nullptr;
    }

    return d3dDevice;
}
