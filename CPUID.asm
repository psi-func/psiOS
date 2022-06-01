DetectCPUID:
    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd 

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz NoCPUID
    ret

DetectLongMode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NoLongMode
    ret

NoLongMode:
    hlt; No ong Mode Support

NoCPUID:
    hlt ; No CPUID support

PrintCPUVendor:
    push eax
    push ebx
    push edx
    push ecx
    mov eax, 0x00
    cpuid
    mov eax, ebx
    and eax, 0xFF 
    mov byte [0xb8000], al ; Start of video memory 
    mov byte [0xb8001],  0x75; attribute byte LOWEST 4 -> colour, HIGHEST 3 - background
    mov eax, ebx
    and eax, 0xFF00
    shr eax, 8
    mov byte [0xb8002], al ; odd numbers contain formatting
    mov eax, ebx
    and eax, 0xFF0000
    shr eax, 16
    mov byte [0xb8004], al
    mov eax, ebx
    and eax, 0xFF000000
    shr eax, 24
    mov byte [0xb8006], al
    mov eax, edx
    and eax, 0xFF
    mov byte [0xb8008], al
    mov eax, edx
    and eax, 0xFF00
    shr eax, 8
    mov byte [0xb800A], al
    mov eax, edx
    and eax, 0xFF0000
    shr eax, 16
    mov byte [0xb800C], al
    mov eax, edx
    and eax, 0xFF000000
    shr eax, 24
    mov byte [0xb800E], al
    mov eax, ecx
    and eax, 0xFF
    mov byte [0xb8010], al
    mov eax, ecx
    and eax, 0xFF00
    shr eax, 8
    mov byte [0xb8012], al
    mov eax, ecx
    and eax, 0xFF0000
    shr eax, 16
    mov byte [0xb8014], al
    mov eax, ecx
    and eax, 0xFF000000
    shr eax, 24
    mov byte [0xb8016], al
    pop ecx
    pop edx
    pop ebx
    pop eax
    ret

