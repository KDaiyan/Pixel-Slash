@echo off

echo Creating build directory 'out'...
mkdir out
cd out

:: Run CMake with MinGW in Release mode
echo Configuring project with CMake...
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..

IF ERRORLEVEL 1 (
    echo [ERROR] CMake configuration failed.
    pause
    exit /b 1
)

:: Build
echo Building project with make...
mingw32-make

IF ERRORLEVEL 1 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

echo.
echo Build completed!
pause
