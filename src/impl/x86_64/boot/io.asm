section .text
global inb_asm, outb_asm

inb_asm:
    push rbx

    mov dx, di
    in al, dx

    movzx rbx, al

    pop rbx
    ret

outb_asm:
    mov dx, di
    mov al, sil
    out dx, al
    
    ret