#include "vga.hpp"
#include "IDT.hpp"
#include "generic_io.h"
#include "KeyboardScanCode.h"
#include "MemoryMap.h"

extern const char Test[];

extern "C" void _start()
{
    set_cursor_position(coords_to_position(0, 0));
    print_screen("Hello world!\n");
    print_screen(to_hex_string(0x1234abcde), FOREGROUND_LIGHTCYAN | BACKGROUND_BLINKINGMAGENTA);
    clear_screen(BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    set_cursor_position(coords_to_position(0, 0));
    // print_screen(Test, BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    // print_screen("psiFunction@PC: ", BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    
    // const volatile float testFloat = -672.938f;

    // print_screen(to_string(testFloat, 5));

    // setup driver
    initialize_idt();

    MainKeyboardHandler = KeyboardHandler;

    MemoryMapEntry** ptr = GetUsableMemoryRegions();
    // PrintMemoryMap(ptr, CursorPosition);
    for( u8 i = 0 ; ptr[i] != nullptr ; ++i) {
        PrintMemoryMap(ptr[i], CursorPosition);
    }


    return;
}