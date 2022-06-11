#include "IDT.hpp"
#include "generic_io.h"

extern IDT64_entry _idt[IDT_MAX_ENTRIES];
extern u64 isr1;
extern "C" void LoadIDT();

void initialize_idt() {
    for (u64 t = 0; t < IDT_MAX_ENTRIES; ++t) {
        _idt[t].zero = 0;
        _idt[t].offset_1 = (u16)((u64)&isr1 & 0xFFFF);
        _idt[t].offset_2 = (u16)(((u64)(&isr1) >> 16) & 0xFFFF);
        _idt[t].offset_3 = (u16)(((u64)(&isr1) >> 32) & 0xFFFFFFFF);
        _idt[t].ist = 0;
        _idt[t].type_attributes = 0x8e;
        _idt[t].selector = 0x8;
    }

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}