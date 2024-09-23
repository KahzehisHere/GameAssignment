#pragma once
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
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
    HINSTANCE hInstance;


public:
    WindowManager(int ScreenWidth = 1280, int ScreenHeight = 720, bool fullscreen = false, int fullscreenWidth = 1920, int fullscreenHeight = 1080);
    ~WindowManager();

    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    HWND createWindow(HINSTANCE hInstance);
    //bool windowIsRunning();
    void cleanup();

    int getFullscreenWidth() const { return fullscreenWidth; }  // Fixed typo
    int getFullscreenHeight() const { return fullscreenHeight; }
    int getWidth() const { return windowWidth; }
    int getHeight() const { return windowHeight; }
    HWND getHWND() const { return g_hWnd; }
    HINSTANCE getInstance() const { return hInstance; }
};

extern WindowManager* windowManager;

#endif