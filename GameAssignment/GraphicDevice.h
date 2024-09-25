#pragma once
#ifndef GRAPHICDEVICE_H
#define GRAPHICDEVICE_H
#include <d3d9.h>
#include <d3dx9.h>
#include "WindowManager.h"

class GraphicDevice {
public:
    ~GraphicDevice();
    static GraphicDevice& getInstance(); // Singleton instance getter
    IDirect3DDevice9* createDevice(HWND hWnd);
    void cleanup();
    IDirect3DDevice9* getDirectDevice() const { return d3dDevice; }

private:

    IDirect3D9* direct3D9 = nullptr;
    IDirect3DDevice9* d3dDevice = nullptr;
    // Constructor is private to enforce singleton
    GraphicDevice();

    // Deleted copy constructor and assignment operator
    GraphicDevice(const GraphicDevice&) = delete;
    GraphicDevice& operator=(const GraphicDevice&) = delete;
};

#endif