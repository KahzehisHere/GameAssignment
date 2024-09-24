#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "GraphicDevice.h"

using namespace std;

WindowManager::WindowManager(int ScreenWidth, int ScreenHeight, bool fullscreen, int fullWidth, int fullHeight)
    : g_hWnd(nullptr), hInstance(nullptr), windowWidth(ScreenWidth), windowHeight(ScreenHeight),
    isFullscreen(fullscreen), fullscreenWidth(fullWidth), fullscreenHeight(fullHeight), msg{}, wndClass{} {
    // Constructor body
}

WindowManager::~WindowManager() {
    // Destructor
}

LRESULT CALLBACK WindowManager::WindowProcedure(HWND g_hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(g_hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND WindowManager::createWindow(HINSTANCE hInstance) {
    this->hInstance = hInstance; 

    ZeroMemory(&wndClass, sizeof(wndClass));
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = WindowProcedure;
    wndClass.lpszClassName = "MainWindowClass";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wndClass)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_OK);
        return NULL;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;  // Test with basic window style

    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "ADAM's Apple", style, 0, 0, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
    

    ShowWindow(g_hWnd, SW_SHOWDEFAULT);
    return g_hWnd;
}

HWND WindowManager::getHWND() const {
    return g_hWnd; 
}

//Redudant because we are using game state manager 
/*bool WindowManager::windowIsRunning() {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}*/

void WindowManager::cleanup( ) {
    UnregisterClass(wndClass.lpszClassName, hInstance);
}
