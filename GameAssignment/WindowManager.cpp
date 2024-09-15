#include "WindowManager.h"

using namespace std;

WindowManager::WindowManager(int ScreenWidth, int ScreenHeight, bool fullscreen, int fullWidth, int fullHeight) {}

WindowManager::~WindowManager() {
   
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    case WM_MOUSEMOVE:
        /*mousePos.x = (short)LOWORD(lParam);
        mousePos.y = (short)HIWORD(lParam);*/
        cout << "X: " << " Y: "  << endl;
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND WindowManager::createWindow(HINSTANCE hInstance) {
    ZeroMemory(&wndClass, sizeof(wndClass));
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = DefWindowProc;
    wndClass.lpszClassName = "MainWindowClass";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wndClass);
    if (!RegisterClass(&wndClass)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_OK);
        return NULL;
    }
    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "ADAM's Apple", WS_POPUP, 0, 0, fullscreenWidth, fullscreenHeight, NULL, NULL, hInstance, NULL);
    ShowWindow(g_hWnd, SW_SHOWDEFAULT);
    return g_hWnd;
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
