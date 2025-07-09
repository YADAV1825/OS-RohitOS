[bits 32]
global kernel_entry
extern kernel_main
extern sbss
extern ebss

kernel_entry:
    mov edi, sbss
    mov ecx, ebss
    sub ecx, edi
    xor eax, eax
    rep stosb

    call kernel_main
    jmp $
