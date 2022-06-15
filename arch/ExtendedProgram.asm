; [org 0x7e00]

jmp EnterProtectedMode

%include "gdt.asm"
%include "print.asm"
%include "DetectMemory.asm"

EnterProtectedMode:
    call DetectMemory 
    call EnableA20
    cli ; disable interrupts
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp codeseg:StartProtectedMode

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]

%include "CPUID.asm"
%include "SimplePaging.asm" 

StartProtectedMode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    mov byte [0xb8000], 'H' ; Start of video memory 
    mov byte [0xb8001],  0x75; attribute byte LOWEST 4 -> colour, HIGHEST 3 - background
    mov byte [0xb8002], 'E' ; odd numbers contain formatting
    mov byte [0xb8004], 'L'
    mov byte [0xb8006], 'L'
    mov byte [0xb8008], 'O'
    mov byte [0xb800A], ' '
    mov byte [0xb800C], 'W'
    mov byte [0xb800E], 'O'
    mov byte [0xb8010], 'R'
    mov byte [0xb8012], 'L'
    mov byte [0xb8014], 'D'
    mov byte [0xb8016], '!'

    call PrintCPUVendor
    call DetectCPUID
    call DetectLongMode

    call SetupIdentityPaging
    call EditGDT

    jmp codeseg:Start64Bit

[bits 64]
[extern _start]

%include "idt.asm"

Start64Bit:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq

    call ActivateSSE
    call _start
    jmp $


ActivateSSE:
    mov rax, cr0
    and ax, 0xFFFB ; Clear CR0.EM
    or ax, 0x02 ; Set CR0.MP
    mov cr0, rax
    
    mov rax, cr4
    or ax, 3 << 9 ; Set CR4.OSXSR CR4.OSXMMEXCPT
    mov cr4, rax
    ret

times 2048-($-$$) db 0
