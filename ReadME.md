# Running

## Windows only (for now)

Docker container tag: `devos`

Make sure Docker desktop (or Docker) is running on your computer, otherwise the images will not be found

1) Run `docker build buildenv -t devos` in Powershell
2) Run `image_handler.bat` in Powershell

Note: you may run `image_handler.bat` with flags like `image_handler.bat $1` to automatically run the option you want to.

Flag options:
- `image_handler.bat -b` to build the image
- `image_handler.bat -r` to run the image
- `image_handler.bat -e` exit the prompt shell

---

1) Run `docker rmi devos -f` to remove image

# ASM Registers reference

# Semantics

 - Any constants or variables that interact with the HWL are declared in all capital letters
 - Any functions are declared in camelCase
 - Any functions or pointers in assembly are declared in snake_case
