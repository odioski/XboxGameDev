@echo off
echo Building Xbox One X Game...
msbuild XboxOneXGame.sln /p:Configuration=Debug /p:Platform=Gaming.Xbox.Scorpio.x64
if %ERRORLEVEL% == 0 (
    echo Build completed successfully!
) else (
    echo Build failed with error code %ERRORLEVEL%
    pause
    exit /b %ERRORLEVEL%
)
pause
