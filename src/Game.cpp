//--------------------------------------------------------------------------------------
// Game.cpp
//
// Main game class implementation for Xbox One game
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "Game.h"

#include <algorithm>
#include <cstdio>

using namespace DirectX;

using Microsoft::WRL::ComPtr;

namespace
{
    constexpr uint64_t c_targetFrameRate = 60;
    constexpr uint64_t c_ticksPerSecond = 10000000;
}

// Constructor
Game::Game() noexcept :
    m_window(nullptr),
    m_outputWidth(1920),
    m_outputHeight(1080),
    m_featureLevel(D3D_FEATURE_LEVEL_11_1),
    m_frame(0),
    m_qpcFrequency(0),
    m_qpcLastTime(0),
    m_qpcMaxDelta(0),
    m_running(true)
{
}

// Destructor
Game::~Game()
{
    if (m_d3dContext)
    {
        m_d3dContext->ClearState();
    }
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window)
{
    if (!window)
    {
        throw std::invalid_argument("Window handle cannot be null");
    }
    
    m_window = window;

    CreateDevice();
    CreateResources();

    // Initialize timing
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_qpcFrequency));
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_qpcLastTime));

    // Setup maximum delta (defaults to 1/10 of a second)
    m_qpcMaxDelta = m_qpcFrequency / 10;
}

// Executes the basic game loop.
void Game::Tick()
{
    // Wait for the previous frame to complete (vsync)
    // This is a simple implementation for demonstration
    
    Update();
    Render();

    m_frame++;
}

// Updates the world.
void Game::Update()
{
    uint64_t currentTime;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

    uint64_t delta = currentTime - m_qpcLastTime;
    m_qpcLastTime = currentTime;

    // Clamp excessively large time deltas
    if (delta > m_qpcMaxDelta)
    {
        delta = m_qpcMaxDelta;
    }

    // Convert to canonical tick format
    delta *= c_ticksPerSecond;
    delta /= m_qpcFrequency;

    // Cap the delta time to prevent spiral of death
    // TODO: Add your game logic here
    //       - Process input (gamepad, keyboard, mouse)
    //       - Update game state (physics, AI, animations)
    //       - Handle collisions
    //       - Update camera position
    //       - Play audio/music
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_frame == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.

    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), 
                                        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
                                        1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), 
                                     m_depthStencilView.Get());

    // Set the viewport
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, 
                            static_cast<float>(m_outputWidth), 
                            static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnSuspending()
{
    m_running = false;
}

void Game::OnResuming()
{
    m_running = true;
    m_qpcLastTime = 0;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    // Create the Direct3D 11 API device object and a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    HRESULT hr = D3D11CreateDevice(
        nullptr,                            // Specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        device.GetAddressOf(),
        &m_featureLevel,
        context.GetAddressOf()
    );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 
        // so we need to retry without it
        hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            device.GetAddressOf(),
            &m_featureLevel,
            context.GetAddressOf()
        );
    }

    ThrowIfFailed(hr);

    ThrowIfFailed(device.As(&m_d3dDevice));
    ThrowIfFailed(context.As(&m_d3dContext));
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews[] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    const UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    const UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(
            2,
            backBufferWidth,
            backBufferHeight,
            backBufferFormat,
            0
        );

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            OnDeviceLost();
            return;
        }
        else
        {
            ThrowIfFailed(hr);
        }
    }
    else
    {
        // Create a descriptor for the swap chain.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = backBufferFormat;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
        fsSwapChainDesc.Windowed = TRUE;

        // Create a SwapChain from a Direct3D device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        ComPtr<IDXGIAdapter> dxgiAdapter;
        ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        ComPtr<IDXGIFactory2> dxgiFactory;
        ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
            m_d3dDevice.Get(),
            m_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr,
            m_swapChain.ReleaseAndGetAddressOf()
        ));
    }

    // Obtain the back buffer for this window which will be the final 3D render target.
    ComPtr<ID3D11Texture2D> backBuffer;
    ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the render target to use on bind.
    ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(
        backBuffer.Get(),
        nullptr,
        m_renderTargetView.ReleaseAndGetAddressOf()
    ));

    // Allocate a 2-D surface as the depth/stencil buffer and create a depth/stencil 
    // view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(
        depthBufferFormat,
        backBufferWidth,
        backBufferHeight,
        1,
        1,
        D3D11_BIND_DEPTH_STENCIL
    );

    ComPtr<ID3D11Texture2D> depthStencil;
    ThrowIfFailed(m_d3dDevice->CreateTexture2D(
        &depthStencilDesc,
        nullptr,
        depthStencil.GetAddressOf()
    ));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(
        depthStencil.Get(),
        &depthStencilViewDesc,
        m_depthStencilView.ReleaseAndGetAddressOf()
    ));
}

void Game::OnDeviceLost()
{
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();

    CreateDevice();
    CreateResources();
}
