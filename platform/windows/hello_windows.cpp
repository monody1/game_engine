//
// Created by Chen.Zr on 2020/3/21.
//

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(
        HWND hWnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
);

int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow
) {
    HWND hWnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(
            0,
            _T("WindowClass1"),
            _T("hello"),
            WS_OVERLAPPEDWINDOW,
            300,
            300,
            500,
            400,
            NULL,
            NULL,
            hInstance,
            NULL
    );
    ShowWindow(hWnd, nCmdShow);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(
        HWND hWnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rec = {20, 20, 60, 80};
            HBRUSH  hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

            FillRect(hdc, &rec, hbrush);
            EndPaint(hWnd, &ps);
        }
            break;
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
            break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
