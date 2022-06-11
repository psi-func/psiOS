#include "vga.hpp"
#include "IDT.hpp"
#include "generic_io.h"
#include "KeyboardScanCode.h"

extern const char Test[];

void KeyboardHandler(u8 scanCode, u8 chr) {
    static bool leftShiftPressed = false;
    static bool rightShiftPressed = false;
    if (chr != 0) {
        switch (leftShiftPressed | rightShiftPressed) {
            case true:
                print_char(chr - 32);
            break;
            case false:
                print_char(chr);
                break;
        }
    }
    else {
        switch(scanCode) {
            // print_screen(to_hex_string(scanCode));
            case 0x0E: // backspace
                set_cursor_position(CursorPosition - 1);
                print_char(' ');
                set_cursor_position(CursorPosition - 1);
                break;
            case 0x2A: //left shift
                leftShiftPressed = true;
                break;
            case 0xAA:
                leftShiftPressed = false;
                break;
            case 0x36: //left shift
                rightShiftPressed = true;
                break;
            case 0xB6:
                rightShiftPressed = false;
                break;
            case 0x9c:
                print_screen("\n\r");
            default:
                break;
        }
    }


}

extern "C" void isr1_handler() {
    u8 scancode = inb(0x60);
    u8 chr = 0;
    if (scancode < sizeof(ScanCodeTable)/ sizeof(ScanCodeTable[0])) {
        chr = ScanCodeTable[scancode];
    }

    if (MainKeyboardHandler != nullptr) {
        MainKeyboardHandler(scancode, chr);
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
    
    // setup driver
    MainKeyboardHandler = KeyboardHandler;

    initialize_idt();

    return;
}