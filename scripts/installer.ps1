# ==============================
# Configuration (editable)
# ==============================

# Set default paths
$QMAKE_EXE = "C:\Qt\6.8.2\msvc2022_64\bin\qmake.exe"
$MAKE_EXE = "C:\Qt\Tools\QtCreator\bin\jom\jom.exe"
$QT_DESIGNER_PLUGIN_DIR = "C:\Qt\Tools\QtCreator\bin\plugins\designer\"

# ==============================
# Configuration (editable) - END
# ==============================

$QT_SPEC = "win32-msvc"

# Set project root (this script must be placed at the root)
$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ROOT_DIR = Split-Path -Parent $SCRIPT_DIR
$PLUGINS_DIR = Join-Path $ROOT_DIR "Plugins"
$LIBRARIES_DIR = Join-Path $ROOT_DIR "Libraries"
$X64_DIR = Join-Path $ROOT_DIR "x64"

# ==============================
# Available plugins
# ==============================

$PLUGINS = @(
    "ParametersWidgets",
    "FrameViewer"
    # Add other plugin directories here...
)

# ==============================
# Helper functions
# ==============================

function Normalize-Path($path) {
    return $path -replace '/', '\'
}

function Init-Environment {
    # Check if 'cl' compiler is available
    if (-not (Get-Command cl -ErrorAction SilentlyContinue)) {
        Write-Host "`ncl compiler is not available`n" -ForegroundColor Yellow

        Write-Host "Initializing Visual Studio environment..." -ForegroundColor Cyan

        $vcvars = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

        if (-Not (Test-Path $vcvars)) {
            Write-Error "File not found: $vcvars" -ForegroundColor Red
            exit 1
        }

        # restart PowerShell with Visual Studio environment initialized
        cmd /c "`"$vcvars`" && powershell -ExecutionPolicy Bypass -File `"$PSCommandPath`" $args"
        exit
    }
    else {
        Write-Host "`ncl compiler is available`n" -ForegroundColor Green
    }
}

function Compile-Plugin($plugin) {
    $global:compilationFailed++

    $plugin_dir = Join-Path $PLUGINS_DIR $plugin
    $pro_file = Join-Path $plugin_dir "$plugin.pro"
    $build_debug = Join-Path $plugin_dir "build\Desktop_Qt_6_8_2_MSVC2022_64bit-Debug"
    $build_release = Join-Path $plugin_dir "build\Desktop_Qt_6_8_2_MSVC2022_64bit-Release"

    Write-Host "`n[*] Building plugin: $plugin`n" -ForegroundColor Magenta

    if (-Not (Test-Path -Path $plugin_dir -PathType Container)) {
        Write-Host "Error: Folder '$plugin_dir' not found." -ForegroundColor Red
        return
    }

    if (-Not (Test-Path -Path $pro_file -PathType Leaf)) {
        Write-Host "Error: File '$pro_file' not found." -ForegroundColor Red
        return
    }
    
    # ---------------------
    # Debug build
    # ---------------------
    Write-Host "`n[*] Debug build..." -ForegroundColor Cyan
    New-Item -ItemType Directory -Force -Path $build_debug | Out-Null
    Push-Location $build_debug

    Write-Host ("`n> $QMAKE_EXE " + (Normalize-Path $pro_file) + " -spec $QT_SPEC CONFIG+=debug CONFIG+=qml_debug") -ForegroundColor Green
    & $QMAKE_EXE (Normalize-Path $pro_file) -spec $QT_SPEC "CONFIG+=debug" "CONFIG+=qml_debug"
    
    Write-Host "`n> $MAKE_EXE qmake_all" -ForegroundColor Green
    & $MAKE_EXE qmake_all
    if (-not $?) {
        Write-Host "Debug build failed for $plugin" -ForegroundColor Red
        Pop-Location
        return
    }

    Write-Host "`n> $MAKE_EXE" -ForegroundColor Green
    & $MAKE_EXE
    if (-not $?) {
        Write-Host "Debug build failed for $plugin" -ForegroundColor Red
        Pop-Location
        return
    }
    
    & $MAKE_EXE clean
    Write-Host "`n> $MAKE_EXE clean" -ForegroundColor Green

    Pop-Location

    # ---------------------
    # Release build
    # ---------------------
    Write-Host "`n[*] Release build..." -ForegroundColor Cyan
    New-Item -ItemType Directory -Force -Path $build_release | Out-Null
    Push-Location $build_release

    Write-Host ("`n> $QMAKE_EXE " + (Normalize-Path $pro_file) + " -spec $QT_SPEC CONFIG+=qtquickcompiler") -ForegroundColor Green
    & $QMAKE_EXE (Normalize-Path $pro_file) -spec $QT_SPEC "CONFIG+=qtquickcompiler"

    Write-Host "`n> $MAKE_EXE qmake_all" -ForegroundColor Green
    & $MAKE_EXE qmake_all
    if (-not $?) {
        Write-Host "Release build failed for $plugin" -ForegroundColor Red
        Pop-Location
        return
    }
    
    Write-Host "`n> $MAKE_EXE" -ForegroundColor Green
    & $MAKE_EXE
    if (-not $?) {
        Write-Host "Release build failed for $plugin" -ForegroundColor Red
        Pop-Location
        return
    }
    
    Write-Host "`n> $MAKE_EXE install" -ForegroundColor Green
    & $MAKE_EXE install

    Write-Host "`n> $MAKE_EXE clean" -ForegroundColor Green
    & $MAKE_EXE clean

    Pop-Location

    # ---------------------
    # Copy outputs to Libraries/
    # ---------------------
    Write-Host "`n[*] Copying compiled files to Libraries/" -ForegroundColor Cyan
    $lib_dir = Join-Path $LIBRARIES_DIR $plugin
    New-Item -ItemType Directory -Force -Path (Join-Path $lib_dir "include") | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $lib_dir "lib") | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $lib_dir "bin") | Out-Null

    Copy-Item -Path (Join-Path $build_debug "debug\$($plugin)d.dll") -Destination (Join-Path $lib_dir "bin") -Force
    Copy-Item -Path (Join-Path $build_release "release\$plugin.dll") -Destination (Join-Path $lib_dir "bin") -Force
    Copy-Item -Path (Join-Path $build_debug "debug\$($plugin)d.lib") -Destination (Join-Path $lib_dir "lib") -Force
    Copy-Item -Path (Join-Path $build_release "release\$plugin.lib") -Destination (Join-Path $lib_dir "lib") -Force

    Get-ChildItem -Path $plugin_dir -Recurse -Filter *.h | Where-Object { $_.Name -notlike '*Plugin.h' } | ForEach-Object {
        Copy-Item $_.FullName -Destination (Join-Path $lib_dir "include") -Force
    }

    # ---------------------
    # Copy to x64/
    # ---------------------
    Write-Host "`n[*] Copying DLLs to x64 directory..." -ForegroundColor Cyan
    New-Item -ItemType Directory -Force -Path (Join-Path $X64_DIR "Debug") | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $X64_DIR "Release") | Out-Null
    Copy-Item -Path (Join-Path $build_debug "debug\$($plugin)d.dll") -Destination (Join-Path $X64_DIR "Debug") -Force
    Copy-Item -Path (Join-Path $build_release "release\$plugin.dll") -Destination (Join-Path $X64_DIR "Release") -Force

    # ---------------------
    # Copy outputs to Designer Plugins/
    # ---------------------
    Write-Host "`n[*] Copying release DLLs to Qt Designer Plugins directory..." -ForegroundColor Cyan
    Copy-Item -Path (Join-Path $build_release "release\$plugin.dll") -Destination $QT_DESIGNER_PLUGIN_DIR -Force

    Write-Host "`nDone: $plugin`n" -ForegroundColor Magenta

    $global:compilationFailed--
    $global:compilationSucceeded++
}

function Print-Configuration {
    Write-Host "Installer Configuration" -Foreground Cyan
    Write-Host "======================="
    Write-Host "qmake.exe: $QMAKE_EXE" -ForegroundColor Yellow
    Write-Host "make.exe: $MAKE_EXE" -ForegroundColor Yellow
    Write-Host "Qt Designer Plugins Dir: $QT_DESIGNER_PLUGIN_DIR" -ForegroundColor Yellow
    Write-Host " "
    Write-Host "Compilation spec: " $QT_SPEC
    Write-Host "Root dir: " $ROOT_DIR
    Write-Host "Plugins dir: " $PLUGINS_DIR
    Write-Host "Libraries dir: " $LIBRARIES_DIR
    Write-Host "x64 dir: " $X64_DIR
    Write-Host " "
}

function Print-Menu {
    Write-Host "Plugin Installer" -Foreground Cyan
    Write-Host "================"
    Write-Host "0. All"
    for ($i = 0; $i -lt $PLUGINS.Count; $i++) {
        Write-Host "$($i + 1). $($PLUGINS[$i])"
    }

    Write-Host "`nYou can select multiple plugins using space (e.g. '1 2 3')"
    Write-Host "Use '0' to compile all plugins"
    Write-Host "Use '-h' or '--help' for usage"

    $choice = Read-Host "`nEnter your choice(s)"
    return $choice
}

function Print-Usage {
    Write-Host "Usage:" -Foreground Cyan
    Write-Host "------"
    Write-Host ".\installer.ps1              # Interactive mode"
    Write-Host ".\installer.ps1 0            # Compile all plugins"
    Write-Host ".\installer.ps1 1            # Compile selected plugin: 1"
    Write-Host ".\installer.ps1 1 2 3        # Compile selected plugins: 1, 2 and 3"
    Write-Host ".\installer.ps1 -h | --help  # Show this help message"
    Write-Host ""
}

# ==============================
# Main entry point
# ==============================

Init-Environment
Print-Configuration

$pluginChoices = @()

# Handle arguments
if ($args.Count -gt 0) {
    if ($args -contains "-h" -or $args -contains "--help") {
        Print-Usage
        exit
    }

    $pluginChoices = $args
}
else {
    $pluginChoices = (Print-Menu).Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
}

# Analyse choices
$pluginsToCompile = @()

if ($pluginChoices -contains "0") {
    $pluginsToCompile = $PLUGINS
}
else {
    foreach ($choice in $pluginChoices) {
        if ($choice -match '^\d+$') {
            $index = [int]$choice - 1
            if ($index -ge 0 -and $index -lt $PLUGINS.Count) {
                $pluginsToCompile += $PLUGINS[$index]
            }
        }
    }
}

# Remove duplicates
$pluginsToCompile = $pluginsToCompile | Select-Object -Unique

# Status
Write-Host " "
Write-Host "Selected plugins to compile:" -Foreground Cyan
Write-Host "============================"
foreach ($p in $pluginsToCompile) {
    Write-Host " - $p" -ForegroundColor Gray
}

# Compile loop
$compilationSucceeded = 0
$compilationFailed = 0

foreach ($plugin in $pluginsToCompile) {
    Compile-Plugin $plugin
}

# Result
Write-Host "`nResult" -Foreground Cyan
Write-Host "======" 
Write-Host ("Plugins to compile: " + $pluginsToCompile.Count) -ForegroundColor Yellow
Write-Host ("Plugins succeeded: " + $compilationSucceeded) -ForegroundColor Green
Write-Host ("Plugins failed: " + $compilationFailed) -ForegroundColor Red
Write-Host ""
