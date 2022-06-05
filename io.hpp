#ifndef KERNEL_IO_HPP
#define KERNEL_IO_HPP

#include "ktypes.hpp"

#define VGA_MEMORY (u8*)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void set_cursor_position(u16 position);

u16 coords_to_position(u8 x, u8 y);

void kprint(const char* str);

#endif