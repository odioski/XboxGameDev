# Xbox One Game Development

> 🎮 A complete, production-ready template for Xbox One/Series X|S game development on Windows 11

A clean build environment for developing Xbox One games on Windows 11.

## Overview

This repository provides a ready-to-use template for Xbox One game development with:

- Visual Studio 2019/2022 project configuration
- DirectX 11 rendering setup
- Support for Xbox One and Xbox Series X|S (Scarlett) platforms
- Clean project structure following best practices
- Comprehensive build configurations (Debug/Release)

## Quick Start

1. **Install Prerequisites** (see SETUP.md for details)
   - Windows 11 (64-bit)
   - Visual Studio 2019 or 2022
   - Microsoft GDK (Game Development Kit)
   - Xbox Developer Account

2. **Clone the Repository**
   ```bash
   git clone https://github.com/odioski/XboxGameDev.git
   cd XboxGameDev
   ```

3. **Open the Solution**
   - Open `XboxGame.sln` in Visual Studio
   - Select your target platform (Gaming.Xbox.XboxOne.x64 or Gaming.Xbox.Scarlett.x64)
   - Build and run (F5)

## Documentation

- [SETUP.md](SETUP.md) - Detailed setup instructions and requirements
- [docs/](docs/) - Additional documentation and guides

## Project Structure

```
XboxGameDev/
├── src/              # Source code files
│   ├── main.cpp      # Entry point
│   └── Game.cpp      # Main game class
├── include/          # Header files
│   └── Game.h        # Game class definition
├── assets/           # Game assets (textures, models, sounds)
├── shaders/          # HLSL shader files
├── docs/             # Additional documentation
├── XboxGame.sln      # Visual Studio solution
└── XboxGame.vcxproj  # Visual Studio project
```

## Build Configurations

- **Debug|Gaming.Xbox.XboxOne.x64** - Debug build for Xbox One
- **Release|Gaming.Xbox.XboxOne.x64** - Optimized build for Xbox One
- **Debug|Gaming.Xbox.Scarlett.x64** - Debug build for Xbox Series X|S
- **Release|Gaming.Xbox.Scarlett.x64** - Optimized build for Xbox Series X|S
- **Debug|x64** - Desktop debug build for local testing
- **Release|x64** - Desktop release build

## Features

- ✅ DirectX 11 rendering pipeline
- ✅ Basic game loop implementation
- ✅ Resource management
- ✅ Multiple platform support (Xbox One, Series X|S, Desktop)
- ✅ Proper project structure
- ✅ Build artifacts excluded from version control

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## Resources

- [Microsoft Game Development Kit](https://aka.ms/gdkdl)
- [Xbox Developer Portal](https://developer.xbox.com/)
- [DirectX Documentation](https://docs.microsoft.com/en-us/windows/win32/directx)

## License

See LICENSE file for details.

## Support

For questions or issues:
- Open an issue on this repository
- Visit the Xbox Developer Forums
- Check the GDK documentation
