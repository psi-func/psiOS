PrintString:
    mov ah, 0x0e
    .Loop:
        cmp byte [bx], 0
        je .Exit
        mov al, [bx]
        int 0x10
        inc bx
        jmp .Loop
    .Exit:
    ret