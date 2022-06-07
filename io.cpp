#include "io.hpp"

static u16 CursorPosition = 0;

char hexToStringOutput[128];

void outb(u16 port, u8 value) {
    asm volatile ("outb %0, %1" 
    :
    : "a"(value), "Nd"(port)
    );
}

u8 inb(u16 port) {
    u8 returnval;
    asm volatile ("inb %1, %0" 
    : "=a"(returnval)
    : "Nd"(port)
    );
    return returnval;
}

void set_cursor_position(u16 position) {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((position >> 8) & 0xFF));

    CursorPosition = position;
}

u16 coords_to_position(u8 x, u8 y) {
    u16 position;
    if (x > 79) return -1;
    position = x + VGA_WIDTH * y;
    if (position > VGA_WIDTH * VGA_HEIGHT) return -1;
    return position;
}

void kprint(const char* str, u8 color) {
    auto char_ptr = (u8*)str;
    u16 index = CursorPosition;
    while (*char_ptr) {
        switch (*char_ptr) {
            case '\n':
                index += VGA_WIDTH;
                index -= index % VGA_WIDTH;
                break;
            default:
                *(VGA_MEMORY + index * 2) = *char_ptr;
                *(VGA_MEMORY + index * 2 + 1) = color;
                ++index;

        }
        ++char_ptr;
    }
    set_cursor_position(index);
}

void clear_screen(u64 clear_color) {
    u64 value = 0;
    value += clear_color << 8;
    value += clear_color << 24;
    value += clear_color << 40;
    value += clear_color << 56;
    for (u64* i = (u64*)VGA_MEMORY; i < (u64*)(VGA_MEMORY + 4000); ++i) {
        *i = value;
    }

}