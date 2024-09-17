#include "GraphicDevice.h"


WindowManager windowManager;
HWND hwnd = windowManager.getHWND();

// Constructor
GraphicDevice::GraphicDevice(int width, int height)
    : d3dDevice(nullptr), screenWidth(width), screenHeight(height) {}

// Clean up the device
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

// Function to create the Direct3D device
IDirect3DDevice9* GraphicDevice::createDevice(HWND hWnd) {
    if (d3dDevice != NULL) {
        d3dDevice->Release();
        d3dDevice = NULL;
    }

    // Create the Direct3D interface
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
    d3dPP.BackBufferCount = 1;
    d3dPP.BackBufferWidth = screenWidth;
    d3dPP.BackBufferHeight = screenHeight;
    d3dPP.hDeviceWindow = hWnd;



    HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

    if (FAILED(hr)) {
        cout << "Failed to create Direct3D device." << endl;
        PostQuitMessage(0);

    return d3dDevice;
}


