# Project Architecture

This document describes the architecture and structure of the Xbox One Game Development template.

## Overview

This project provides a clean, minimal template for Xbox One game development on Windows 11. It uses DirectX 11 for rendering and follows Microsoft's recommended practices for Xbox game development.

## Project Structure

```
XboxGameDev/
├── src/                    # Source code implementation files
│   ├── main.cpp           # Application entry point
│   └── Game.cpp           # Main game class implementation
│
├── include/               # Header files
│   └── Game.h            # Game class definition
│
├── assets/               # Game assets (textures, models, audio)
│   └── .gitkeep         # Placeholder for directory
│
├── shaders/              # HLSL shader files
│   ├── Simple.hlsl      # Example shader
│   └── .gitkeep         # Placeholder for directory
│
├── docs/                 # Documentation
│   ├── QUICKSTART.md    # Quick setup guide
│   ├── ARCHITECTURE.md  # This file
│   ├── TROUBLESHOOTING.md  # Common issues and solutions
│   └── CONTRIBUTING.md  # Contribution guidelines
│
├── XboxGame.sln          # Visual Studio solution file
├── XboxGame.vcxproj      # Visual Studio project file
├── XboxGame.vcxproj.filters  # Project filters for organization
├── build.cmd             # Command-line build script
├── .gitignore            # Git ignore patterns
├── LICENSE               # MIT License
├── README.md             # Main readme
└── SETUP.md              # Detailed setup instructions
```

## Core Components

### 1. Entry Point (main.cpp)

**Responsibilities:**
- Application initialization
- Window creation and message pump
- Main game loop management
- Exception handling
- COM initialization/cleanup

**Key Functions:**
- `wWinMain()` - Windows application entry point
- `ExitGame()` - Clean shutdown helper

**Flow:**
```
Start → COM Init → Create Game → Message Loop → Cleanup → Exit
                      ↓
                  Game::Tick() (repeated)
```

### 2. Game Class (Game.h / Game.cpp)

**Responsibilities:**
- DirectX 11 device management
- Rendering pipeline setup
- Game loop implementation (Update/Render)
- Resource management
- Device loss handling

**Key Components:**

#### Device Resources
- `ID3D11Device1` - D3D11 device for resource creation
- `ID3D11DeviceContext1` - D3D11 context for rendering
- `IDXGISwapChain1` - Swap chain for presenting frames
- `ID3D11RenderTargetView` - Render target view
- `ID3D11DepthStencilView` - Depth/stencil buffer view

#### Core Methods

**Initialization:**
- `Initialize(HWND)` - Set up D3D and resources
- `CreateDevice()` - Create D3D11 device and context
- `CreateResources()` - Create render targets and buffers

**Game Loop:**
- `Tick()` - Main game loop entry point
- `Update()` - Update game state (called every frame)
- `Render()` - Render the current frame
- `Clear()` - Clear render targets
- `Present()` - Present frame to screen

**Lifecycle:**
- `OnSuspending()` - Handle application suspend
- `OnResuming()` - Handle application resume
- `OnDeviceLost()` - Handle device loss and recreation

### 3. Rendering Pipeline

**Render Pass Flow:**
```
Clear() → Game Logic → Render() → Present()
   ↓                      ↓
Clear RT/DS          Draw Calls      Display
Set Viewport        Bind Shaders      VSync
```

**Default Configuration:**
- Resolution: 1920x1080 (Full HD)
- Format: BGRA8 (8-bit per channel)
- Depth: 32-bit float
- Clear Color: Cornflower Blue
- VSync: Enabled (60 FPS target)

## Build Configurations

### Platforms

1. **Gaming.Xbox.XboxOne.x64**
   - Target: Xbox One, Xbox One S, Xbox One X
   - Feature Level: D3D_FEATURE_LEVEL_11_1
   - Architecture: x64

2. **Gaming.Xbox.Scarlett.x64**
   - Target: Xbox Series S, Xbox Series X
   - Feature Level: D3D_FEATURE_LEVEL_12_0+
   - Architecture: x64

3. **x64 (Desktop)**
   - Target: Windows 11 PC
   - For local development and testing
   - Architecture: x64

### Configurations

**Debug:**
- Optimization: Disabled
- Debug symbols: Full
- Runtime checks: Enabled
- Incremental linking: Yes
- SDL checks: Enabled

**Release:**
- Optimization: Maximum (/O2)
- Debug symbols: Program Database
- Whole program optimization: Yes
- Incremental linking: No
- Runtime checks: Disabled

## Key Technologies

### DirectX 11

**Why DirectX 11?**
- Full Xbox One support
- Mature, stable API
- Excellent documentation
- Wide hardware support

**Core Features Used:**
- Hardware-accelerated rendering
- Shader pipeline (vertex/pixel)
- Swap chain management
- Resource views
- Device context state management

### C++17

**Language Features:**
- Standard Library containers
- Smart pointers (unique_ptr, ComPtr)
- RAII for resource management
- Exception handling
- Move semantics

### Windows Runtime (WinRT)

**Used For:**
- COM object management
- Platform integration
- Device enumeration

## Memory Management

### Resource Lifetime

**Device Resources:**
- Created in `CreateDevice()`
- Released automatically via ComPtr
- Recreated on device loss

**Render Resources:**
- Created in `CreateResources()`
- Recreated on window resize
- Cleaned up on device loss

### Best Practices

1. **Use Smart Pointers**
   - `Microsoft::WRL::ComPtr` for COM objects
   - `std::unique_ptr` for owned objects
   - `std::shared_ptr` when needed

2. **RAII Pattern**
   - Resources acquired in constructor
   - Resources released in destructor
   - Exception safe

3. **Avoid Manual Memory Management**
   - Minimize `new`/`delete`
   - Use containers and smart pointers
   - Let destructors handle cleanup

## Error Handling

### Strategy

1. **HRESULT Checks**
   ```cpp
   ThrowIfFailed(hr);  // Throw com_exception on failure
   ```

2. **Exception Safety**
   - Use RAII for all resources
   - Catch exceptions at application boundary
   - Log errors for debugging

3. **Device Loss Handling**
   - Detect via DXGI error codes
   - Recreate device and resources
   - Resume rendering

### Debug Support

**Debug Layer:**
- Enabled in Debug builds
- Provides detailed error messages
- Validates API usage
- Checks for resource leaks

**Debug Output:**
```cpp
DebugTrace("Message: %s", str);  // Outputs to debug console
```

## Performance Considerations

### Target Frame Rate
- 60 FPS on Xbox One
- VSync enabled by default
- Frame pacing via swap chain

### Optimization Tips

1. **Minimize State Changes**
   - Batch similar draw calls
   - Sort by material/texture
   - Cache pipeline states

2. **Use Efficient Resources**
   - Texture atlases
   - Instance rendering
   - Constant buffer updates

3. **Profile Regularly**
   - Use PIX for Xbox
   - Visual Studio profiler for PC
   - Monitor GPU/CPU usage

## Extensibility

### Adding Features

**New Game Objects:**
1. Create class in `src/`
2. Add header to `include/`
3. Include in Game class
4. Initialize in `Game::Initialize()`
5. Update in `Game::Update()`
6. Render in `Game::Render()`

**New Shaders:**
1. Add .hlsl file to `shaders/`
2. Include in project (vcxproj)
3. Compile during build
4. Load in game code

**New Assets:**
1. Place in `assets/` directory
2. Update `.gitignore` if needed
3. Load at runtime
4. Manage lifetime

## Threading Model

**Current Implementation:**
- Single-threaded
- All updates on main thread
- Rendering on main thread

**Future Considerations:**
- Job system for parallel work
- Async resource loading
- Compute shaders for parallel processing

## Testing Strategy

### Development Testing
- Build on PC (x64 configuration)
- Test on local hardware
- Use Visual Studio debugger

### Console Testing
- Deploy to Xbox dev kit
- Test on target hardware
- Profile with PIX
- Validate performance

## Dependencies

**Required:**
- DirectX 11 (Windows SDK)
- Windows Runtime (WinRT)
- C++ Standard Library

**Optional:**
- DirectXMath (included)
- DirectXTK (can be added)
- Xbox Services API (for online features)

## Coding Standards

See [CONTRIBUTING.md](CONTRIBUTING.md) for detailed coding standards.

**Key Points:**
- C++17 standard
- 4-space indentation
- PascalCase for types/functions
- camelCase for variables
- m_ prefix for members
- Clear, descriptive names

## Security Considerations

1. **Input Validation**
   - Validate all user input
   - Check file sizes before loading
   - Sanitize network data

2. **Resource Management**
   - Prevent resource exhaustion
   - Limit memory allocations
   - Check buffer bounds

3. **Platform Security**
   - Follow Xbox security guidelines
   - Use secure APIs
   - Avoid deprecated functions

## Future Enhancements

Potential additions to the template:

- [ ] Audio system integration
- [ ] Input handling (gamepad, keyboard)
- [ ] Scene management
- [ ] Asset loading system
- [ ] Texture support
- [ ] Model loading
- [ ] Particle system
- [ ] Physics integration
- [ ] UI framework
- [ ] Networking support
- [ ] Xbox Live integration

## References

- [Microsoft GDK Documentation](https://aka.ms/gdk)
- [DirectX 11 Programming Guide](https://docs.microsoft.com/en-us/windows/win32/direct3d11/dx-graphics-overviews)
- [Xbox Developer Resources](https://developer.xbox.com/)
- [DirectX Samples](https://github.com/microsoft/DirectX-Graphics-Samples)

---

**Last Updated:** 2025-11-06
