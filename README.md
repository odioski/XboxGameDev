# Xbox One X Scorpio Game Development Environment

This is a minimal Xbox One X Scorpio game development environment built using Microsoft's official GDK boilerplate.

## Project Structure

### Core Files
- **Main.cpp** - Entry point with Xbox One X Scorpio detection
- **XboxGame.h/cpp** - Main game class optimized for Scorpio hardware
- **DeviceResources.h/cpp** - D3D12 device management for Xbox One X
- **StepTimer.h** - High-precision timing for game loops
- **pch.h/cpp** - Precompiled headers for Xbox development

### Configuration Files
- **MicrosoftGame.config** - Xbox package manifest with Scorpio enhancements
- **XboxOneXGame.vcxproj** - Visual Studio project targeting Gaming.Xbox.Scorpio.x64
- **XboxOneXGame.sln** - Visual Studio solution

## Xbox One X Scorpio Features

### Hardware Specifications
- **GPU**: 6 TFLOPS AMD Polaris with 40 Compute Units
- **Memory**: 12GB GDDR5 (9GB available to games)
- **CPU**: Custom Jaguar 8-core @ 2.3GHz
- **Resolution**: Native 4K (3840x2160) support
- **HDR**: HDR10 support

### Enhanced Features Enabled
- 4K/HDR rendering pipeline
- Xbox One X hardware detection
- Scorpio GPU optimization utilization
- Enhanced memory bandwidth usage
- Variable refresh rate support

## Building

### Requirements
- Visual Studio 2019/2022 with Xbox One development tools
- Microsoft Game Development Kit (GDK) or GDK with Xbox Extensions (GDKX)
- Xbox One X console or Xbox One X development kit

### Build Instructions
1. Open `XboxOneXGame.sln` in Visual Studio
2. Select **Gaming.Xbox.Scorpio.x64** platform
3. Choose Debug or Release configuration
4. Build solution (Ctrl+Shift+B)
###
#### Optional:
I believe Visual Studio can streamline this build process. 
However, code is code and we like to know what's going on under the hood.
Therefore you'll need to run ./build-game.bat first to create an .exe and then ./BuildAppx.ps1 to wrap your app as a game for your Xbox One if using VS Code, unless you Engineer another way. Both scripts can be found in / of XboxGameDev/.
Afterwhich you may need to apply a certificate to the resulting *appx or Xbox One App or Game before your Xbox One will accept it or load it.

Change the credentials in BuildAppx.ps1 to match your Xbox One local ip address and login credentials if you applied those.

### Deployment to Xbox One X
The built package (.msixvc) can be deployed directly to Xbox One X console using:
- Xbox Device Portal
- Visual Studio remote debugging
- Xbox One Manager XDK tool

## Key Classes

### Sample (XboxGame.h)
Main game class that detects Xbox One X Scorpio hardware and enables enhanced features.

### DeviceResources
Manages D3D12 device creation optimized for Xbox One X:
- 4K rendering support
- HDR10 color space
- Enhanced GPU utilization

### StepTimer  
High-precision timing for consistent frame rates at 60fps or variable refresh rates.

## Xbox One X Optimizations

The code includes specific optimizations for Xbox One X Scorpio:
- Automatic hardware detection using `XSystemGetDeviceType()`
- Enhanced GPU compute utilization
- 4K rendering pipeline setup
- HDR metadata configuration
- Variable refresh rate support

## Notes

- This is a minimal console-only environment 
- Uses Microsoft's official GDK APIs and best practices
- Targets Gaming.Xbox.Scorpio.x64 platform exclusively
- Ready for Xbox console deployment and testing
