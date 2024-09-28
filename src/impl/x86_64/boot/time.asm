section .text
global time

time:
    rdtsc
    shl rdx, 32
    or rax, rdx
    ret