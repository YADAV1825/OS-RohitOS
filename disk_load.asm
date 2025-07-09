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
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

sectors_error:
    mov bx, SECTORS_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG db "Disk read error!", 0
SECTORS_ERROR_MSG db "Incorrect sectors read!", 0

print_string:
    pusha
    mov ah, 0x0e
.repeat:
    mov al, [bx]
    cmp al, 0
    je .done
    int 0x10
    inc bx
    jmp .repeat
.done:
    popa
    ret