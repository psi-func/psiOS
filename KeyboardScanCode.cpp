#include "KeyboardScanCode.h"
#include "stdint.h"
#include "vga.hpp"
#include "generic_io.h"

// const char ScanCodeTable[] = {
//     0, 0, '1', '2',
//     '3', '4', '5', '6',
//     '7', '8', '9', '0',
//     '-', '=', 0, 0,
//     'q', 'w', 'e', 'r',
//     't', 'y', 'u', 'i',
//     'o', 'p', '[', ']',
//     0, 0, 'a', 's',
//     'd', 'f', 'g', 'h',
//     'j', 'k', 'l', ';',
//     '\'', '\"', 0, '\\',
//     'z', 'x', 'c', 'v',
//     'b', 'n', 'm', ',',
//     '.', '/', 0, '*',
//     0, ' '
// };

keyboard_cb MainKeyboardHandler = nullptr;

void StandardKeyboardHandler(u8 scanCode, u8 chr) {
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

void KeyboardHandler0xE0(u8 scanCode) {
    switch (scanCode) {
        case 0x50:
            set_cursor_position(CursorPosition + VGA_WIDTH);
            break;
        case 0x48:
            set_cursor_position(CursorPosition - VGA_WIDTH);
            break;
        default:
            break;
    }
}

void KeyboardHandler(u8 scanCode, u8 chr) {
    static u8 lastScanCode;
    
    switch(lastScanCode) {
    case 0xE0:
        KeyboardHandler0xE0(scanCode);
        break;
    default:
        StandardKeyboardHandler(scanCode, chr);
        break;
    }
    
    lastScanCode = scanCode;
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

