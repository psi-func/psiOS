#include "vga.hpp"
#include "IDT.hpp"
#include "generic_io.h"
#include "KeyboardScanCode.h"

extern const char Test[];

extern "C" void isr1_handler() {
    u8 scancode = inb(0x60);
    if (scancode < sizeof(ScanCodeTable)/ sizeof(ScanCodeTable[0])) {
        print_char(ScanCodeTable[scancode]);
    }
    
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}

extern "C" void _start()
{
    set_cursor_position(coords_to_position(0, 0));
    print_screen("Hello world!\n");
    print_screen(to_hex_string(0x1234abcde), FOREGROUND_LIGHTCYAN | BACKGROUND_BLINKINGMAGENTA);
    clear_screen(BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    set_cursor_position(coords_to_position(0, 0));
    print_screen(Test, BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    print_screen("psiFunction@PC: ", BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    
    initialize_idt();

    return;
}