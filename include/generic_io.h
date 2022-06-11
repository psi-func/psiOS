#ifndef KERNEL_GENERIC_IO_OPS
#define KERNEL_GENERIC_IO_OPS

#include "stdint.h"

void inline outb(u16 port, u8 value) {
    asm volatile ("outb %0, %1" 
    :
    : "a"(value), "Nd"(port)
    );
}

u8 inline inb(u16 port) {
    u8 returnval;
    asm volatile ("inb %1, %0" 
    : "=a"(returnval)
    : "Nd"(port)
    );
    return returnval;
}

#endif