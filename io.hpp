#ifndef KERNEL_IO_HPP
#define KERNEL_IO_HPP

#include "ktypes.hpp"

#define VGA_MEMORY (u8*)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

extern char hexToStringOutput[128];

constexpr u8 FOREGROUND_BLACK = 0x00;
constexpr u8 FOREGROUND_BLUE = 0x01;
constexpr u8 FOREGROUND_GREEN = 0x02;
constexpr u8 FOREGROUND_CYAN = 0x03;
constexpr u8 FOREGROUND_RED = 0x04;
constexpr u8 FOREGROUND_MAGENTA = 0x05;
constexpr u8 FOREGROUND_BROWN = 0x06;
constexpr u8 FOREGROUND_LIGHTGRAY = 0x07;
constexpr u8 FOREGROUND_DARKGRAY = 0x08;
constexpr u8 FOREGROUND_LIGHTBLUE = 0x09;
constexpr u8 FOREGROUND_LIGHTGREEN = 0x0A;
constexpr u8 FOREGROUND_LIGHTCYAN = 0x0B;
constexpr u8 FOREGROUND_LIGHTRED = 0x0C;
constexpr u8 FOREGROUND_LIGHTMAGENTA = 0x0D;
constexpr u8 FOREGROUND_YELLOW = 0x0E;
constexpr u8 FOREGROUND_WHITE = 0x0F;

constexpr u8 BACKGROUND_BLACK = 0x00;
constexpr u8 BACKGROUND_BLUE = 0x10;
constexpr u8 BACKGROUND_GREEN = 0x20;
constexpr u8 BACKGROUND_CYAN = 0x30;
constexpr u8 BACKGROUND_RED = 0x40;
constexpr u8 BACKGROUND_MAGENTA = 0x50;
constexpr u8 BACKGROUND_BROWN = 0x60;
constexpr u8 BACKGROUND_LIGHTGRAY = 0x70;
constexpr u8 BACKGROUND_BLINKINGBLACK = 0x80;
constexpr u8 BACKGROUND_BLINKINGBLUE = 0x90;
constexpr u8 BACKGROUND_BLINKINGGREEN = 0xA0;
constexpr u8 BACKGROUND_BLINKINGCYAN = 0xB0;
constexpr u8 BACKGROUND_BLINKINGRED = 0xC0;
constexpr u8 BACKGROUND_BLINKINGMAGENTA = 0xD0;
constexpr u8 BACKGROUND_BLINKINGYELLOW = 0xE0;
constexpr u8 BACKGROUND_BLINKINGWHITE = 0xF0;

u8 inb(u16 port);

void outb(u16 port, u8 value);

void set_cursor_position(u16 position);

u16 coords_to_position(u8 x, u8 y);

void kprint(const char* str, u8 color = BACKGROUND_BLACK | FOREGROUND_WHITE);

void clear_screen(u64 clear_color = BACKGROUND_BLACK | FOREGROUND_WHITE);

template<typename T>
const char* to_hex_string(T value) {
    T* valPtr = &value;
    u8 size = sizeof(T) * 2 - 1;
    u8 temp = temp;
    for (u8 i = 0; i < size; ++i) {
        u8* ptr = reinterpret_cast<u8*>(valPtr) + i;
        temp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = (*ptr & 0x0F);
        hexToStringOutput[size - (i * 2)] = temp + (temp > 9 ? 55 : 48);
    }
    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}

#endif