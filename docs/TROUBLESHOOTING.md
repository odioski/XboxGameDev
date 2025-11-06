# Troubleshooting Guide

This guide helps resolve common issues when building and running Xbox One games on Windows 11.

## Build Issues

### Error: "Cannot find Xbox One SDK"

**Symptoms:**
- Build fails with errors about missing Xbox SDK
- Platform toolset errors

**Solutions:**

1. **Install Microsoft GDK**
   - Download from: https://aka.ms/gdkdl
   - Run the installer as Administrator
   - Restart Visual Studio after installation

2. **Verify Environment Variables**
   ```cmd
   echo %GXDK%
   echo %XdkEditionTarget%
   ```
   These should point to your GDK installation directory

3. **Check Visual Studio Installation**
   - Open Visual Studio Installer
   - Modify your installation
   - Ensure "Game development with C++" workload is installed
   - Include "Xbox Development Tools" component

### Error: "Platform 'Gaming.Xbox.XboxOne.x64' not found"

**Symptoms:**
- Platform dropdown in Visual Studio doesn't show Xbox platforms
- Build configuration manager missing Xbox platforms

**Solutions:**

1. **Install GDK Platform Support**
   - Re-run GDK installer
   - Select "Repair" or "Modify"
   - Ensure platform support is checked

2. **Reset Visual Studio**
   ```cmd
   devenv /ResetSettings
   ```

3. **Check Project Configuration**
   - Right-click solution → Configuration Manager
   - Verify Xbox platforms are listed
   - If missing, may need to recreate project from template

### Error: "MSB8020: The build tools for v143 cannot be found"

**Symptoms:**
- Build fails with platform toolset error

**Solutions:**

1. **Update Project Toolset**
   - Open XboxGame.vcxproj in text editor
   - Find `<PlatformToolset>v143</PlatformToolset>`
   - Change to `v142` if using VS 2019
   - Or update to VS 2022

2. **Install Required Components**
   - Open Visual Studio Installer
   - Install "MSVC v143 build tools" component

### Error: "DirectX SDK not found" or "d3d11_x.h not found"

**Symptoms:**
- Cannot find DirectX headers
- d3d11_x.h or DirectXMath.h missing

**Solutions:**

1. **Install Windows SDK**
   - Open Visual Studio Installer
   - Modify installation
   - Install "Windows 10 SDK (10.0.19041.0)" or later
   - Restart Visual Studio

2. **Update Project SDK Version**
   - Right-click project → Properties
   - General → Windows SDK Version
   - Select latest installed version

### Error: "LNK1104: cannot open file 'kernel32.lib'"

**Symptoms:**
- Linker cannot find system libraries

**Solutions:**

1. **Check Installation Paths**
   - Verify Windows SDK is installed
   - Check project Include/Library paths in Properties

2. **Repair Visual Studio**
   - Run Visual Studio Installer
   - Click "Repair" on your VS installation

## Runtime Issues

### Error: "The application was unable to start correctly (0xc000007b)"

**Symptoms:**
- Application fails to launch on Xbox or PC

**Solutions:**

1. **Check Platform Target**
   - Ensure you're building for correct architecture (x64)
   - Verify Xbox console is in Developer Mode

2. **Rebuild from Clean**
   ```cmd
   msbuild XboxGame.sln /t:Clean
   msbuild XboxGame.sln /p:Configuration=Debug /p:Platform=Gaming.Xbox.XboxOne.x64
   ```

### Error: "Could not connect to Xbox console"

**Symptoms:**
- Cannot deploy or debug on Xbox hardware

**Solutions:**

1. **Enable Developer Mode**
   - On Xbox: Settings → System → Console info
   - Switch to "Developer Mode"
   - Note the IP address displayed

2. **Configure Network**
   - Ensure PC and Xbox are on same network
   - Disable VPNs or virtual adapters
   - Check Windows Firewall settings

3. **Add Xbox in Visual Studio**
   - Tools → Options → Cross Platform
   - Add your Xbox console by IP address
   - Test the connection

### Error: "D3D11 device creation failed"

**Symptoms:**
- Application crashes on startup
- DirectX initialization errors

**Solutions:**

1. **Update Graphics Drivers**
   - On PC: Update to latest GPU drivers
   - Restart system

2. **Check Debug Layer**
   - If in Debug mode, ensure "Graphics Tools" are installed
   - Windows Settings → Apps → Optional Features
   - Add "Graphics Tools"

3. **Verify Feature Level**
   - Ensure target hardware supports D3D_FEATURE_LEVEL_11_0 minimum

## Development Issues

### Issue: Slow build times

**Solutions:**

1. **Enable Incremental Linking**
   - Project Properties → Linker → General
   - Enable Incremental Linking: Yes (/INCREMENTAL)

2. **Use Multiple CPU Cores**
   ```cmd
   msbuild XboxGame.sln /m
   ```

3. **Disable Unnecessary Features in Debug**
   - Reduce optimization level if needed
   - Disable features not needed during development

### Issue: IntelliSense errors but builds successfully

**Solutions:**

1. **Refresh IntelliSense Database**
   - Delete `.vs` folder
   - Restart Visual Studio
   - Let IntelliSense rebuild

2. **Reset IntelliSense**
   - Edit → IntelliSense → Rescan Solution

## Xbox Console Issues

### Issue: Console not showing in deployment targets

**Solutions:**

1. **Check Xbox Network Settings**
   - Xbox should be on same subnet as PC
   - Note Xbox IP address

2. **Manually Add Console**
   - Visual Studio toolbar
   - Select "Device" dropdown
   - "Manage Connections"
   - Add Xbox by IP

3. **Verify Xbox is in Developer Mode**
   - Dev Home should be installed on Xbox
   - Console should show "Developer Mode" in settings

### Issue: "Package deployment failed"

**Solutions:**

1. **Free Up Xbox Storage**
   - Remove unused games/apps
   - Ensure at least 10GB free space

2. **Clean Previous Deployment**
   - On Xbox: Dev Home → Remove app
   - Rebuild and redeploy

3. **Check Package Manifest**
   - Verify appxmanifest.xml is valid
   - Check package identity settings

## Getting Help

If you continue to experience issues:

1. **Check Build Output**
   - View → Output window
   - Read complete error messages
   - Note error codes for searching

2. **Enable Diagnostic Logging**
   ```cmd
   msbuild XboxGame.sln /v:detailed > build.log 2>&1
   ```

3. **Search Resources**
   - [Microsoft GDK Documentation](https://aka.ms/gdk)
   - [Xbox Developer Forums](https://forums.xboxlive.com/)
   - [Stack Overflow - xbox-one tag](https://stackoverflow.com/questions/tagged/xbox-one)

4. **Report Issues**
   - Open an issue on this repository
   - Include error messages, build logs, and system info
   - Describe steps to reproduce

## Useful Commands

```cmd
# Clean build
msbuild XboxGame.sln /t:Clean

# Rebuild solution
msbuild XboxGame.sln /t:Rebuild /p:Configuration=Debug /p:Platform=Gaming.Xbox.XboxOne.x64

# Build with detailed output
msbuild XboxGame.sln /v:detailed

# Check MSBuild version
msbuild /version

# List available SDKs
dir "C:\Program Files (x86)\Windows Kits\10\Include"
```

## System Requirements Checklist

- [ ] Windows 11 (64-bit)
- [ ] Visual Studio 2019/2022 with Game Development workload
- [ ] Microsoft GDK installed
- [ ] Windows 10 SDK (10.0.19041.0 or later)
- [ ] Xbox Developer Account active
- [ ] Xbox console in Developer Mode (if testing on hardware)
- [ ] At least 20GB free disk space
- [ ] DirectX 11 capable GPU (for PC testing)

---

**Last Updated:** 2025-11-06
