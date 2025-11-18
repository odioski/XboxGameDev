//--------------------------------------------------------------------------------------
// Main.cpp
//
// Entry point for Xbox One X Scorpio game
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "XboxGame.h"

using namespace DirectX;

namespace
{
    std::unique_ptr<Sample> g_sample;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
#if defined(_XBOX_ONE) && defined(_TITLE)
    // Initialize Xbox Game Runtime
    HRESULT hr = XGameRuntimeInitialize();
    if (FAILED(hr))
    {
        return 1;
    }

    // Xbox One X Scorpio detection
    XSystemDeviceType deviceType = XSystemGetDeviceType();
    if (deviceType == XSystemDeviceType::XboxScorpio)
    {
        OutputDebugStringA("Running on Xbox One X Scorpio - Enhanced features enabled\n");
    }
#endif

    // Register class and create window
    RECT rc;
    {
        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = hInstance;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszClassName = L"XboxOneXGameWindowClass";
        if (!RegisterClassExW(&wcex))
            return 1;

        // Create window optimized for Xbox One X 4K
        HWND hwnd = CreateWindowExW(0, L"XboxOneXGameWindowClass", L"Xbox One X Scorpio Game",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 3840, 2160, nullptr, nullptr, hInstance, nullptr);

        if (!hwnd)
            return 1;

        ShowWindow(hwnd, nCmdShow);

        GetClientRect(hwnd, &rc);

        g_sample = std::make_unique<Sample>();
        g_sample->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
    }

    // Main message loop
    MSG msg = {};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_sample->Tick();
        }
    }

    g_sample.reset();

#if defined(_XBOX_ONE) && defined(_TITLE)
    XGameRuntimeUninitialize();
#endif

    return static_cast<int>(msg.wParam);
}

// Windows procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SYSKEYDOWN:
        if (sample)
        {
            sample->OnSuspending();
        }
        break;

    case WM_SYSKEYUP:
        if (sample)
        {
            sample->OnResuming();
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
