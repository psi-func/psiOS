PROGRAM_SPACE equ 0x7e00

ReadDisk:
    mov ah, 0x02 ; cmd
    mov bx, PROGRAM_SPACE ; where to load them? es * 16 + bx
    mov al, 5 ; how many sectors?
    mov dl, [BOOT_DISK] ; Disk number
    mov ch, 0x00 ; C (cylinder)
    mov dh, 0x00 ; H (head)
    mov cl, 0x02 ; S (sector)

    int 0x13

    jc DiskReadFailed ; check carry flag

    ret

BOOT_DISK:
    db 0

DiskReadErrorString:
    db 'Disk Read Failed', 0

DiskReadFailed:
    mov bx, DiskReadErrorString
    call PrintString

    jmp $