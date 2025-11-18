# Xbox One X APPX Package Builder
# This script creates an APPX package for Xbox One X deployment

param(
    [string]$Configuration = "Debug",
    [string]$Platform = "Gaming.Xbox.Scorpio.x64"
)

$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Definition
$BinPath = Join-Path $ProjectRoot "bin\$Platform\$Configuration"
$PackageRoot = Join-Path $ProjectRoot "AppxPackage"
$OutputPath = Join-Path $ProjectRoot "bin\$Platform\$Configuration"

Write-Host "Building Xbox One X APPX Package..." -ForegroundColor Green
Write-Host "Configuration: $Configuration" -ForegroundColor Yellow
Write-Host "Platform: $Platform" -ForegroundColor Yellow

# Clean and create package directory
if (Test-Path $PackageRoot) {
    Remove-Item $PackageRoot -Recurse -Force
}
New-Item -ItemType Directory -Path $PackageRoot -Force | Out-Null

# Copy executable and dependencies
Write-Host "Copying game files..." -ForegroundColor Cyan
Copy-Item "$BinPath\XboxOneXGame.exe" $PackageRoot -Force
Copy-Item "$BinPath\XboxOneXGame.pdb" $PackageRoot -Force -ErrorAction SilentlyContinue

# Copy manifest
Copy-Item "$ProjectRoot\Package.appxmanifest" (Join-Path $PackageRoot "AppxManifest.xml") -Force

# Copy MicrosoftGame.config for Xbox
Copy-Item "$ProjectRoot\MicrosoftGame.config" $PackageRoot -Force

# Create Assets directory and copy assets
$AssetsDir = Join-Path $PackageRoot "Assets"
New-Item -ItemType Directory -Path $AssetsDir -Force | Out-Null

# Create placeholder assets if they don't exist
$AssetFiles = @(
    "Logo.png",
    "SmallLogo.png",
    "StoreLogo.png",
    "WideLogo.png"
)

foreach ($asset in $AssetFiles) {
    $assetPath = Join-Path $AssetsDir $asset
    if (-not (Test-Path $assetPath)) {
        # Create a simple 1x1 PNG placeholder
        $bytes = [System.Convert]::FromBase64String("iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAADUlEQVR42mNkYPhfDwAChwGA60e6kgAAAABJRU5ErkJggg==")
        [System.IO.File]::WriteAllBytes($assetPath, $bytes)
    }
}

Write-Host "Package structure created at: $PackageRoot" -ForegroundColor Green

# Try to create APPX using MakeAppx (if available)
try {
    $makeAppxPath = Get-Command "MakeAppx.exe" -ErrorAction Stop
    Write-Host "Creating APPX package using MakeAppx..." -ForegroundColor Cyan

    $appxFile = Join-Path $OutputPath "XboxOneXGame.appx"
    & $makeAppxPath.Source pack /d "$PackageRoot" /p "$appxFile" /o

    if ($LASTEXITCODE -eq 0) {
        Write-Host "APPX package created successfully!" -ForegroundColor Green
        Write-Host "Package location: $appxFile" -ForegroundColor Yellow

        # Show package info
        $size = (Get-Item $appxFile).Length / 1MB
        Write-Host "Package size: $($size.ToString('F2')) MB" -ForegroundColor Cyan
    } else {
        throw "MakeAppx failed with exit code $LASTEXITCODE"
    }
} catch {
    Write-Warning "MakeAppx.exe not found or failed. Package files are ready at: $PackageRoot"
    Write-Host "To manually create APPX:" -ForegroundColor Yellow
    Write-Host "1. Install Windows 10 SDK" -ForegroundColor White
    Write-Host "2. Run: MakeAppx.exe pack /d `"$PackageRoot`" /p `"$OutputPath\XboxOneXGame.appx`" /o" -ForegroundColor White

    Write-Host "`nPackage contents:" -ForegroundColor Green
    Get-ChildItem $PackageRoot -Recurse | ForEach-Object {
        Write-Host "   $($_.FullName.Replace($PackageRoot, ''))" -ForegroundColor Gray
    }
}

Write-Host "`nReady for Xbox One X deployment!" -ForegroundColor Green
