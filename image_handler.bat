@echo off
setlocal

if "%~1"=="" goto menu

:process_args
if "%~1"=="$1" (
    set choice=1
    goto build
) else if "%~1"=="$2" (
    set choice=2
    set RUN_GIT_BASH=true
    goto build
) else if "%~1"=="$3" (
    goto end
) else (
    echo FLAG ERROR. Please use $1, $2, or $3.
    goto end
)

:menu
echo.
echo Select an option:
echo 1. Build only
echo 2. Build and run in QEMU
echo 3. Exit

choice /c 123 /n /m "Enter an option: "
set "choice=%errorlevel%"

if "%choice%"=="1" (
    goto build
) else if "%choice%"=="2" (
    set RUN_GIT_BASH=true
    goto build
) else if "%choice%"=="3" (
    goto end
) else (
    echo ARG ERROR. Please use 1, 2, or 3.
    goto menu
)

:build
docker run --rm -v "%cd%:/root/env" devos /bin/bash -c "make build-x86_64"

if "%RUN_GIT_BASH%"=="true" (
    start "" "C:\Program Files\Git\git-bash.exe" -c "cd /c/Users/%USERNAME%/devos && qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso"
)

:end
endlocal