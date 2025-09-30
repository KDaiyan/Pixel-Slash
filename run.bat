@echo off
setlocal

:: Navigate to the folder
cd /d "%~dp0out\src\app"

:: Look for the first .exe file
for %%f in (*.exe) do (
    echo [INFO] Running %%f...
    start "" "%%f"
    goto :DONE
)

echo [ERROR] No executable found in out\src\app
exit /b 1

:DONE
endlocal
pause
