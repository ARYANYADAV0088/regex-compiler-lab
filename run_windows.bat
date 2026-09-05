@echo off
setlocal
cd /d "%~dp0"
call build_windows.bat
if errorlevel 1 pause & exit /b 1
if not exist .venv python -m venv .venv
call .venv\Scripts\activate
python -m pip install -r requirements.txt
python backend\app.py
endlocal
