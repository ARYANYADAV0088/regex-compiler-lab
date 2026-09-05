@echo off
setlocal
cd /d "%~dp0"
where g++ >nul 2>nul
if errorlevel 1 (
  echo ERROR: g++ was not found in PATH.
  echo Install MinGW-w64/MSYS2 and add g++ to PATH.
  exit /b 1
)
if not exist cpp mkdir cpp

g++ -std=c++17 -O2 -Wall -Wextra -Icpp\include cpp\src\*.cpp -o cpp\regex_engine.exe
if errorlevel 1 (
  echo ERROR: C++ build failed.
  exit /b 1
)
echo Built cpp\regex_engine.exe
endlocal
