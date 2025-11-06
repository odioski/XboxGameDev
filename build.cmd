@echo off
REM Build script for Xbox Game Development
REM Usage: build.cmd [Debug|Release] [Gaming.Xbox.XboxOne.x64|Gaming.Xbox.Scarlett.x64|x64]

setlocal

REM Set default configuration and platform
set CONFIG=%1
set PLATFORM=%2

if "%CONFIG%"=="" set CONFIG=Debug
if "%PLATFORM%"=="" set PLATFORM=Gaming.Xbox.XboxOne.x64

echo ========================================
echo Building Xbox Game
echo Configuration: %CONFIG%
echo Platform: %PLATFORM%
echo ========================================
echo.

REM Find MSBuild using vswhere (recommended) or fallback to known paths
set VSWHERE="C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

if exist %VSWHERE% (
    REM Use vswhere to find the latest MSBuild
    for /f "usebackq tokens=*" %%i in (`%VSWHERE% -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
        set MSBUILD="%%i"
    )
)

REM Fallback to known paths if vswhere didn't find MSBuild
if not exist %MSBUILD% set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
if not exist %MSBUILD% set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
if not exist %MSBUILD% set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
if not exist %MSBUILD% set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
if not exist %MSBUILD% set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe"
if not exist %MSBUILD% set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"

if not exist %MSBUILD% (
    echo ERROR: MSBuild not found. Please install Visual Studio 2019 or 2022.
    echo TIP: Run this script from a Visual Studio Developer Command Prompt.
    exit /b 1
)

REM Build the solution
%MSBUILD% XboxGame.sln /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /m /v:minimal

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ========================================
    echo Build FAILED
    echo ========================================
    exit /b %ERRORLEVEL%
)

echo.
echo ========================================
echo Build SUCCEEDED
echo ========================================
echo Output: bin\%PLATFORM%\%CONFIG%\
echo.

endlocal
