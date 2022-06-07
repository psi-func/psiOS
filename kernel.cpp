#include "io.hpp"

extern "C" void _start()
{
    set_cursor_position(coords_to_position(0, 0));
    kprint("Hello world!\n");
    kprint(to_hex_string(0x1234abcde), FOREGROUND_LIGHTCYAN | BACKGROUND_BLINKINGMAGENTA);
    clear_screen(BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN);
    return;
}