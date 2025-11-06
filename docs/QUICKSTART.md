# Quick Start Guide

Get up and running with Xbox One game development in minutes!

## Prerequisites Checklist

Before you start, make sure you have:

- [ ] Windows 11 (64-bit) installed and updated
- [ ] Visual Studio 2019 or 2022 installed
- [ ] "Game development with C++" workload installed in Visual Studio
- [ ] Microsoft GDK (Game Development Kit) installed
- [ ] Xbox Developer Account (for console deployment)

## Step-by-Step Setup

### 1. Install Visual Studio

1. Download Visual Studio 2022 Community (free) from https://visualstudio.microsoft.com/
2. During installation, select these workloads:
   - ✅ **Game development with C++**
   - ✅ **Desktop development with C++**
   - ✅ **Universal Windows Platform (UWP) development**
3. In Individual Components, ensure you have:
   - ✅ Windows 10 SDK (latest version)
   - ✅ C++ CMake tools for Windows
   - ✅ MSVC v143 build tools

### 2. Install Microsoft GDK

1. Visit https://aka.ms/gdkdl
2. Sign in with your Microsoft account
3. Download the latest GDK
4. Run installer as Administrator
5. Follow the installation wizard
6. **Important:** Restart your computer after installation

### 3. Get Xbox Developer Access

**Option A: ID@Xbox (Independent Developers)**
1. Apply at https://www.xbox.com/developers/id
2. Wait for approval (can take several weeks)
3. Once approved, access Partner Center

**Option B: Microsoft Partner (Managed Partners)**
1. Visit https://partner.microsoft.com/
2. Follow enrollment process

**Option C: Local Development Only**
- You can develop and test on Windows PC without Xbox console access
- Use the x64 platform configuration for local testing

### 4. Clone and Build the Project

```bash
# Clone the repository
git clone https://github.com/odioski/XboxGameDev.git
cd XboxGameDev
```

### 5. Open in Visual Studio

1. Double-click `XboxGame.sln`
2. Wait for Visual Studio to load the project
3. Wait for IntelliSense to finish indexing

### 6. Configure Build Settings

**For Xbox One Console:**
1. In the toolbar, set Configuration to **Debug**
2. Set Platform to **Gaming.Xbox.XboxOne.x64**

**For Xbox Series X|S:**
1. In the toolbar, set Configuration to **Debug**
2. Set Platform to **Gaming.Xbox.Scarlett.x64**

**For Local PC Testing:**
1. In the toolbar, set Configuration to **Debug**
2. Set Platform to **x64**

### 7. Build the Project

**Using Visual Studio:**
1. Press `Ctrl+Shift+B` or select Build → Build Solution
2. Watch the Output window for build progress
3. Verify "Build succeeded" message

**Using Command Line:**
```cmd
# Navigate to project directory
cd C:\path\to\XboxGameDev

# Build for Xbox One
build.cmd Debug Gaming.Xbox.XboxOne.x64

# Or build for PC
build.cmd Debug x64
```

### 8. Run the Game

**On PC (Local Testing):**
1. Set Platform to **x64**
2. Press `F5` or select Debug → Start Debugging
3. You should see a window with a cornflower blue background

**On Xbox Console:**
1. Put your Xbox in Developer Mode:
   - Go to Settings → System → Console info
   - Select "Switch to Developer Mode"
   - Follow on-screen instructions
2. In Visual Studio:
   - Select **Gaming.Xbox.XboxOne.x64** platform
   - In the toolbar, select "Device" dropdown
   - Choose "Manage Connections"
   - Add your Xbox by IP address
3. Press `F5` to deploy and run

## Verify Installation

### Check 1: Environment Variables

Open PowerShell and run:
```powershell
Write-Host "GDK Path: $env:GXDK"
Write-Host "XDK Edition: $env:XdkEditionTarget"
```

Both should show valid paths. If not, reinstall GDK.

### Check 2: Build Configurations

In Visual Studio:
1. Go to Build → Configuration Manager
2. Verify you see these platforms:
   - Gaming.Xbox.XboxOne.x64
   - Gaming.Xbox.Scarlett.x64
   - x64

If missing, GDK may not be properly installed.

### Check 3: Sample Build

1. Open `src/main.cpp`
2. Verify no red squiggly lines under `#include` statements
3. Try to build (Ctrl+Shift+B)
4. Should complete without errors

## Common First-Time Issues

### "Platform 'Gaming.Xbox.XboxOne.x64' not found"

**Fix:**
1. Restart Visual Studio
2. If still not found, reinstall GDK
3. Run GDK installer with "Repair" option

### "Cannot find d3d11_x.h"

**Fix:**
1. Open Visual Studio Installer
2. Modify installation
3. Ensure "Windows 10 SDK" is installed
4. Install latest available version

### "MSBuild not found" when using build.cmd

**Fix:**
- Edit `build.cmd`
- Update MSBuild path to match your VS installation
- Or use Visual Studio instead

## Next Steps

Once you have the project building successfully:

1. **Explore the Code**
   - Read through `src/main.cpp` - the entry point
   - Check `src/Game.cpp` - the main game loop
   - Review `include/Game.h` - the game class definition

2. **Customize the Template**
   - Change the clear color in `Game::Clear()`
   - Add your game logic in `Game::Update()`
   - Add rendering code in `Game::Render()`

3. **Add Assets**
   - Place textures in `assets/` folder
   - Add shaders to `shaders/` folder
   - Update project to include new files

4. **Learn DirectX**
   - Check out Microsoft's DirectX samples
   - Read the GDK documentation
   - Explore Xbox-specific APIs

5. **Deploy to Console**
   - Follow Xbox Developer documentation
   - Test on real hardware
   - Profile using PIX

## Resources

- [Full Setup Guide](SETUP.md) - Detailed installation instructions
- [Troubleshooting Guide](TROUBLESHOOTING.md) - Solve common problems
- [Contributing](CONTRIBUTING.md) - Help improve this project
- [Microsoft GDK Docs](https://aka.ms/gdk) - Official documentation

## Getting Help

If you're stuck:

1. Check [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
2. Search existing issues on GitHub
3. Open a new issue with details
4. Include error messages and system info

## Success!

You should now have:
- ✅ A working build environment
- ✅ A compilable Xbox One game project
- ✅ Understanding of the basic structure
- ✅ Ready to start developing

**Happy coding!** 🎮

---

**Need more help?** Open an issue or check the full [SETUP.md](SETUP.md) guide.
