//--------------------------------------------------------------------------------------
// pch.h
//
// Header for standard system includes for Xbox One X development.
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

// Use the C++ standard templated min/max
#define NOMINMAX

#include <windows.h>
#include <winerror.h>
#include <windef.h>
#include <wrl/client.h>
#include <wrl/event.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include "include/d3dx12.h"

// DirectX Tool Kit includes
// #include "include/BufferHelpers.h"  // Commented out - requires Xbox-specific headers
// #include "include/CommonStates.h"  // Commented out - requires Xbox-specific headers
// #include "include/DirectXHelpers.h"  // Commented out - requires Xbox-specific headers
// #include "include/Effects.h"  // Commented out - requires Xbox-specific headers
// #include "include/GraphicsMemory.h"  // Commented out - requires Xbox-specific headers
// #include "include/ResourceUploadBatch.h"  // Commented out - requires Xbox-specific headers

#include <XGame.h>

// Version check commented out for compatibility
// #if _GAMERUNTIMESDK_VER < 0x42000300 /* GDK Edition 180800 */
// #error This sample requires the August 2018 GDK or later
// #endif

#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <system_error>

#include <stdio.h>

// Forward declarations for Xbox development
namespace DX
{
    interface IDeviceNotify
    {
        virtual void OnDeviceLost() = 0;
        virtual void OnDeviceRestored() = 0;
    };
}

// Xbox Game Runtime (local headers)
#include "include/XGame.h"
#include "include/XSystem.h"
#include "include/XTaskQueue.h"

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        virtual const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}
