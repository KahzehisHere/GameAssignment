#include "WindowManager.h"

WindowManager::WindowManager(int ScreenWidth, int ScreenHeight, bool fullscreen, int fullWidth, int fullHeight)
    : g_hWnd(NULL), windowWidth(ScreenWidth), windowHeight(ScreenHeight), fullscreenWidth(fullWidth), fullscreenHeight(fullHeight), isFullscreen(fullscreen) {}

WindowManager::~WindowManager() {}

HWND WindowManager::createWindow(HINSTANCE hInstance) {
    ZeroMemory(&wndClass, sizeof(wndClass));
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = DefWindowProc;
    wndClass.lpszClassName = "MainWindowClass";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wndClass)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_OK);
        return NULL;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;
    if (isFullscreen) {
        style = WS_POPUP;
    }

    g_hWnd = CreateWindow("MainWindowClass", "Game Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInstance, NULL);

    if (!g_hWnd) {
        MessageBox(NULL, "Failed to create window", "Error", MB_OK);
        return NULL;
    }

    applyWindowMode();
    ShowWindow(g_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(g_hWnd);

    return g_hWnd;
}

void WindowManager::applyWindowMode() {
    if (isFullscreen) {
        SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP);
        SetWindowPos(g_hWnd, HWND_TOP, 0, 0, fullscreenWidth, fullscreenHeight, SWP_FRAMECHANGED);
    }
    else {
        SetWindowLong(g_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPos(g_hWnd, HWND_TOP, 100, 100, windowWidth, windowHeight, SWP_FRAMECHANGED);
    }
    ShowWindow(g_hWnd, SW_SHOWDEFAULT);
}

bool WindowManager::windowIsRunning() {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void WindowManager::cleanup(HINSTANCE hInstance) {
    UnregisterClass(wndClass.lpszClassName, hInstance);
}
