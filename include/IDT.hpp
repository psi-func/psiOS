#ifndef KERNEL_INTERRUPT_DESCRIPTOR_TABLE
#define KERNEL_INTERRUPT_DESCRIPTOR_TABLE

#include "stdint.h"

#define IDT_MAX_ENTRIES 256

struct IDT64_entry {
    u16 offset_1;
    u16 selector;
    u8 ist;
    u8 type_attributes;
    u16 offset_2;
    u32 offset_3;
    u32 zero;
};

void initialize_idt(); 

#endif