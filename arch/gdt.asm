;    ██████╗ ██████╗ ████████╗                                                   
;   ██╔════╝ ██╔══██╗╚══██╔══╝                                                   
;   ██║  ███╗██║  ██║   ██║                                                      
;   ██║   ██║██║  ██║   ██║                                                      
;   ╚██████╔╝██████╔╝   ██║                                                      
;    ╚═════╝ ╚═════╝    ╚═╝                                                      
                                                                               
;   ██████╗ ███████╗███████╗ ██████╗██████╗ ██╗██████╗ ████████╗ ██████╗ ██████╗ 
;   ██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██║██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
;   ██║  ██║█████╗  ███████╗██║     ██████╔╝██║██████╔╝   ██║   ██║   ██║██████╔╝
;   ██║  ██║██╔══╝  ╚════██║██║     ██╔══██╗██║██╔═══╝    ██║   ██║   ██║██╔══██╗
;   ██████╔╝███████╗███████║╚██████╗██║  ██║██║██║        ██║   ╚██████╔╝██║  ██║
;        ╚═════╝ ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝╚═╝        ╚═╝    ╚═════╝ ╚═╝  ╚═╝

; size + offset structure

gdt_nulldesc:
    dd 0
    dd 0
gdt_codedesc:
    dw 0xFFFF ; Limit 0:15
    dw 0x0000 ; Base 0:15
    db 0x00 ; Base 16:23
    db 10011010b; Access byte
    db 11001111b; Flags (access) + Limit 16:19
    db 0x00; base 24:31
gdt_datadesc:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b ; Access byte (- exec flag)
    db 11001111b
    db 0x00
gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nulldesc - 1
        dq gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc

[bits 32]

EditGDT:
    mov byte [gdt_codedesc + 6], 10101111b
    mov byte [gdt_datadesc + 6], 10101111b

    ret

[bits 16]