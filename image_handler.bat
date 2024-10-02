@echo off
setlocal

if "%~1"=="" goto menu

:process_args
if "%~1"=="-b" (
    set choice=1
    goto build
) else if "%~1"=="-r" (
    set choice=2
    set RUN_GIT_BASH=true
    goto build
) else if "%~1"=="-e" (
    goto end
) else (
    echo FLAG ERROR. Please use -b, -r, or -e.
    goto end
)

:menu
echo.
echo Select an option:
echo b. Build only
echo r. Build and run in QEMU
echo e. Exit

choice /c 123 /n /m "Enter an option: "
set "choice=%errorlevel%"

if "%choice%"=="b" (
    goto build
) else if "%choice%"=="r" (
    set RUN_GIT_BASH=true
    goto build
) else if "%choice%"=="e" (
    goto end
) else (
    echo ARG ERROR. Please use b, r, or e.
    goto menu
)

:build
docker run --rm -v "%cd%:/root/env" devos /bin/bash -c "make build-x86_64"

if "%RUN_GIT_BASH%"=="true" (
    start "" "C:\Program Files\Git\git-bash.exe" -c "cd /c/Users/%USERNAME%/devos && qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso"
)

:end
endlocal