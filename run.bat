@echo off
rem Determine script directory and bin directory
set SCRIPT_DIR=%~dp0
set BIN_DIR=%SCRIPT_DIR%bin

rem Find the first exe in bin that is not client.exe
set "OTHER_EXE="
for %%F in ("%BIN_DIR%\*.exe") do (
	if /I not "%%~nF.exe"=="client.exe" (
		set "OTHER_EXE=%%~fF"
		goto :found_other
	)
)
:found_other

if not exist "%BIN_DIR%\client.exe" (
	echo client.exe not found in %BIN_DIR%
	pause
	exit /b 1
)

if "%OTHER_EXE%"=="" (
	echo No other exe found in %BIN_DIR% besides client.exe
	pause
	exit /b 1
)

rem Start two separate terminals running the executables
start "Client" cmd /k "%BIN_DIR%\client.exe"
start "Other" cmd /k "%OTHER_EXE%"

exit /b 0
