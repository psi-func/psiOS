#include "vga.hpp"
#include "IDT.hpp"
#include "generic_io.h"

extern const char Test[];

extern "C" void isr1_handler() {
    print_screen(to_hex_string(inb(0x60)));
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