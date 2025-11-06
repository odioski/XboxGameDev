//--------------------------------------------------------------------------------------
// main.cpp
// 
// Entry point for Xbox One game
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "Game.h"

#include <windows.h>
#include <exception>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace
{
    std::unique_ptr<Game> g_game;
}

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return 1;

    try
    {
        g_game = std::make_unique<Game>();
        
        // Main game loop
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
                g_game->Tick();
            }
        }

        g_game.reset();
    }
    catch (const std::exception& e)
    {
        OutputDebugStringA("Exception: ");
        OutputDebugStringA(e.what());
        OutputDebugStringA("\n");
        return 1;
    }

    CoUninitialize();

    return 0;
}

// Exit helper
void ExitGame() noexcept
{
    PostQuitMessage(0);
}
