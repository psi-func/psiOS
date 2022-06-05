#include "io.hpp"

extern "C" void _start()
{
    set_cursor_position(coords_to_position(12, 18));
    kprint("Hello world!\n");
    return;
}