# Xbox One Game Development Setup on Windows 11

This repository contains a clean build setup for developing Xbox One games on Windows 11.

## Prerequisites

### Required Software

1. **Windows 11** (64-bit)
   - Make sure your system is fully updated

2. **Visual Studio 2019 or later** (Visual Studio 2022 recommended)
   - Download from: https://visualstudio.microsoft.com/
   - Required workloads:
     - "Game development with C++"
     - "Desktop development with C++"
     - "Universal Windows Platform (UWP) development"

3. **Microsoft GDK (Game Development Kit)** or **Xbox One XDK**
   - For independent developers: Use the Microsoft GDK (https://aka.ms/gdkdl)
   - For approved Xbox developers: Use Xbox One XDK from the Partner Portal
   - Note: You need to be enrolled in the ID@Xbox program or have a developer account

4. **Windows 10/11 SDK**
   - Usually included with Visual Studio
   - Latest version recommended: 10.0.19041.0 or later

## Xbox Developer Account Setup

To develop for Xbox One, you need:

1. **ID@Xbox Program Enrollment** (for independent developers)
   - Apply at: https://www.xbox.com/developers/id
   - OR

2. **Microsoft Partner Center Account**
   - For managed partners: https://partner.microsoft.com/

## Project Structure

```
XboxGameDev/
├── src/              # Source code files
├── include/          # Header files
├── assets/           # Game assets (textures, models, sounds)
├── shaders/          # HLSL shader files
├── docs/             # Additional documentation
└── XboxGame.sln      # Visual Studio solution file
```

## Building the Project

### Using Visual Studio

1. Open `XboxGame.sln` in Visual Studio
2. Select the appropriate build configuration:
   - **Debug** - For development and testing
   - **Release** - For optimized builds
3. Select the target platform:
   - **Gaming.Xbox.Scarlett.x64** - For Xbox Series X|S
   - **Gaming.Xbox.XboxOne.x64** - For Xbox One
4. Press F7 or select Build > Build Solution

### Using MSBuild (Command Line)

```cmd
# From the repository root
msbuild XboxGame.sln /p:Configuration=Debug /p:Platform=Gaming.Xbox.XboxOne.x64
```

## Running and Debugging

### On Xbox Development Kit

1. Ensure your Xbox One console is in Developer Mode
2. Connect your PC and Xbox to the same network
3. In Visual Studio, select your Xbox as the deployment target
4. Press F5 to deploy and debug

### On PC (Windows 11)

For initial development and testing, you can use the Desktop configuration:

1. Select Configuration: Debug
2. Select Platform: x64
3. Press F5 to run locally

## Common Build Issues

### Issue: "Cannot find Xbox One SDK"

**Solution:** 
- Ensure GDK/XDK is properly installed
- Check environment variables: `GXDK` or `XdkEditionTarget`
- Restart Visual Studio after SDK installation

### Issue: "Platform 'Gaming.Xbox.XboxOne.x64' not found"

**Solution:**
- Install the Microsoft GDK
- Ensure "Game development with C++" workload is installed in Visual Studio
- Re-run the GDK installer if necessary

### Issue: Build fails with DirectX errors

**Solution:**
- Update Windows 10/11 SDK to the latest version
- Check that DirectX headers are included in the project

## Development Tips

1. **Use Incremental Builds**: Enable incremental linking for faster iteration
2. **Profile Early**: Use PIX for Xbox to profile your game regularly
3. **Test on Hardware**: Always test on actual Xbox hardware before submission
4. **Memory Management**: Xbox One has 8GB RAM (5GB available to games)
5. **Shader Compilation**: Pre-compile shaders for better load times

## Resources

- [Microsoft Game Development Kit Documentation](https://aka.ms/gdk)
- [Xbox Developer Portal](https://developer.xbox.com/)
- [DirectX Graphics Samples](https://github.com/microsoft/DirectX-Graphics-Samples)
- [PIX on Windows](https://devblogs.microsoft.com/pix/)

## Next Steps

1. Review the sample code in `src/` directory
2. Familiarize yourself with the project structure
3. Run a test build to ensure everything is configured correctly
4. Start developing your game!

## Support

For issues specific to this template:
- Open an issue on this repository

For Xbox development questions:
- Visit the Xbox Developer Forums
- Consult the GDK documentation

## License

See LICENSE file for details.
