@echo off
echo Deploying Xbox One X Game to 192.168.8.138...

set XBOX_IP=192.168.8.138
set XBOX_USER=odani
set XBOX_PASS=app64

REM First deploy locally for validation
echo [STEP 1] Deploying game package locally for validation...
powershell.exe -Command "try { Add-AppxPackage -Path 'bin/Gaming.Xbox.Scorpio.x64/Debug/XboxOneXGame.appx' -Verbose; Write-Host 'Local deployment completed successfully!' -ForegroundColor Green } catch { Write-Host 'Local deployment failed:' $_.Exception.Message -ForegroundColor Red; exit 1 }"

if %ERRORLEVEL% NEQ 0 (
    echo Local deployment failed. Cannot proceed to Xbox console deployment.
    pause
    exit /b %ERRORLEVEL%
)

REM Prompt for Visual Studio PIN before Xbox deployment
echo.
echo [STEP 2] Preparing Xbox Console Deployment...
set /p VS_PIN="Enter Visual Studio PIN for Xbox %XBOX_IP%: "

REM Deploy to Xbox console using PowerShell and Xbox Device Portal API
echo.
echo [STEP 3] Deploying to Xbox Console at %XBOX_IP%...
echo Connecting to Xbox at %XBOX_IP% with user %XBOX_USER%...

powershell.exe -Command "$xbox_ip='%XBOX_IP%'; $user='%XBOX_USER%'; $pass='%XBOX_PASS%'; $pin='%VS_PIN%'; try { Write-Host 'Uploading XboxOneXGame.appx to Xbox console...' -ForegroundColor Yellow; $uri = \"http://${xbox_ip}:11443/api/app/packagemanager/package\"; $cred = [Convert]::ToBase64String([Text.Encoding]::ASCII.GetBytes(\"${user}:${pass}\")); $headers = @{'Authorization' = \"Basic $cred\"}; $boundary = [System.Guid]::NewGuid().ToString(); $LF = \"`r`n\"; $fileBytes = [System.IO.File]::ReadAllBytes('XboxOneXGame.appx'); $bodyLines = ( '--' + $boundary, 'Content-Disposition: form-data; name=\"file\"; filename=\"XboxOneXGame.appx\"', 'Content-Type: application/octet-stream', '', [System.Text.Encoding]::GetEncoding('iso-8859-1').GetString($fileBytes), '--' + $boundary + '--', '' ) -join $LF; Invoke-WebRequest -Uri $uri -Method Post -Headers $headers -Body $bodyLines -ContentType \"multipart/form-data; boundary=$boundary\"; Write-Host 'Xbox deployment completed successfully!' -ForegroundColor Green } catch { Write-Host 'Xbox deployment failed:' $_.Exception.Message -ForegroundColor Red; exit 1 }"

if %ERRORLEVEL% == 0 (
    echo Game successfully deployed to Xbox One X at %XBOX_IP%!
) else (
    echo Xbox deployment failed with error code %ERRORLEVEL%
    echo.
    echo ======= MANUAL DEPLOYMENT OPTIONS =======
    echo Option 1: Xbox Device Portal Web Interface
    echo   1. Open browser and go to: http://%XBOX_IP%:11443
    echo   2. Login with username: %XBOX_USER% and password: %XBOX_PASS%
    echo   3. Go to Apps ^> Install from file
    echo   4. Browse and select: XboxOneXGame.appx
    echo   5. Click Install
    echo.
    echo Option 2: Copy via Network Share (if enabled)
    echo   1. Copy XboxOneXGame.appx to Xbox shared folder
    echo   2. Install via Xbox File Explorer
    echo.
    echo Option 3: USB Drive
    echo   1. Copy XboxOneXGame.appx to USB drive
    echo   2. Insert USB into Xbox One X
    echo   3. Install via Xbox File Manager
    echo.
    echo Current package location: %cd%\XboxOneXGame.appx
    echo =========================================
)

pause
