#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

using namespace std;

class WindowManager {
private:
    HWND g_hWnd;
    WNDCLASS wndClass;
    MSG msg;
    int windowWidth;
    int windowHeight;
    int fullscreenWidth;
    int fullscreenHeight;
    bool isFullscreen;

    void applyWindowMode();

public:
    WindowManager(int ScreenWidth = 1280, int ScreenHeight = 720, bool fullscreen = false, int fullscreenWidth = 1920, int fullscreenHeight = 1080);
    ~WindowManager();

    HWND createWindow(HINSTANCE hInstance);
    bool windowIsRunning();
    void cleanup(HINSTANCE hInstance);
    void toggleFullcreen();
    void setFullscreenResolution();
    int getFullcreenWidth() const { return fullscreenWidth; }
    int getFullscreenHeight() const { return fullscreenHeight; }
    int getWidth() const { return windowWidth; }
    int getHeight() const { return windowHeight; }
    HWND getHWND() const { return g_hWnd; }
};
