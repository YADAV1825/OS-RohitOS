[bits 16]
[org 0x7c00]

start:
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load

    cli
    lgdt [gdt_descriptor]         ; Load GDT before switching to protected mode

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Use hardcoded segment value (0x08) instead of CODE_SEG for jump
    jmp 0x08:init_pm

; ===================== GDT and Protected Mode =====================
[bits 32]
init_pm:
    mov ax, 0x10    ; DATA_SEG is 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_OFFSET   ; Jump to 0x1000, where kernel is loaded

; ===================== GDT =====================
[bits 16]
gdt_start:
    dq 0x0

gdt_code:
    dw 0xFFFF           ; Limit low
    dw 0x0000           ; Base low
    db 0x00             ; Base middle
    db 10011010b        ; Access
    db 11001111b        ; Flags and limit high
    db 0x00             ; Base high

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; ===================== Disk Load =====================
disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, disk_err_msg
    call print_string
    jmp $

sectors_error:
    mov bx, sectors_err_msg
    call print_string
    jmp $

print_string:
    pusha
.print_char:
    mov al, [bx]
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    inc bx
    jmp .print_char
.done:
    popa
    ret

disk_err_msg db "Disk read error!", 0
sectors_err_msg db "Incorrect sectors read!", 0

BOOT_DRIVE db 0
KERNEL_OFFSET equ 0x1000

times 510 - ($ - $$) db 0
dw 0xAA55
