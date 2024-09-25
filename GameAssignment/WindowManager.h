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
    int windowWidth = 1280;
    int windowHeight = 720;
    int fullscreenWidth = 1920;
    int fullscreenHeight = 1080;
    bool isFullscreen;
    HINSTANCE hInstance;
    static LRESULT CALLBACK WindowProcedure(HWND g_hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    WindowManager(int ScreenWidth = 1280, int ScreenHeight = 720, bool fullscreen = false, int fullscreenWidth = 1920, int fullscreenHeight = 1080);
   
    WindowManager(const WindowManager&) = delete;
    void operator=(const WindowManager&) = delete;
public:
    
    ~WindowManager();
    
    HWND createWindow(HINSTANCE hInstance);
    //bool windowIsRunning();
    void cleanup();
    int getFullscreenWidth() const;  // Fixed typo
    int getFullscreenHeight() const;
    int getWidth() const;
    int getHeight() const;
    HWND getHWND() const;

    // Get singleton instance of WindowManager
    static WindowManager& getWindowManager(int ScreenWidth = 800, int ScreenHeight = 600, bool fullscreen = false, int fullWidth = 1920, int fullHeight = 1080) {
        static WindowManager instance(ScreenWidth, ScreenHeight, fullscreen, fullWidth, fullHeight);
        return instance;
    }

    // Getter for HINSTANCE
    HINSTANCE getInstanceHandle() const { return hInstance; }
};

#endif