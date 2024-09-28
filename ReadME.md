# Running

## Windows only (for now)

Docker container tag: `devos`

1) Run `docker build buildenv -t devos` in Powershell
2) Run `./build_image.bat` in Powershell
3) Run `cd .. && cd C:/users/$USER/devos && qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso` in MSYS2 MINGW64 terminal

---

1) Run `docker rmi devos -f` to remove image
