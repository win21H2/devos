section .text
global inb_asm, outb_asm

; byte read from io
inb_asm:
    push rbx

    mov dx, di
    in al, dx

    movzx rbx, al

    pop rbx
    ret

; byte write to io
outb_asm:
    mov dx, di
    mov al, sil
    out dx, al
    
    ret