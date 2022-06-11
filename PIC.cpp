#include "PIC.h"

#include "generic_io.h"

void PIC_remap(u8 offset1, u8 offset2) {
    u8 a1,a2;

    a1 = inb(PIC1_DATA); // save masks
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_ICW4 | ICW1_INIT);
    io_wait();
    outb(PIC1_DATA, offset1); // ICW2 -> MASTER PIC vector offset
    io_wait();
    outb(PIC2_DATA, offset2); // ICW2 -> SLAVE PIC vector offset
    io_wait();
    outb(PIC1_DATA, 4); // ICW3 ->> MASTER PIC set mask at IRQ2 (0000 0100)
    io_wait();
    outb(PIC2_DATA, 2); // ICW3 ->> SLAVE PIC set cascade identity IRQ2 (0000 0010)
    io_wait();


    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1); // restore saved masks
    outb(PIC2_DATA, a2);

}

void PIC_disable() {
    asm volatile (
        "mov 0xff, %%al;"
        "out %%al, %[pic2_data];"
        "out %%al, %[pic1_data];"
        :
        : [pic2_data] "N" (PIC2_DATA), [pic1_data] "N" (PIC1_DATA)
        : "%al"
        );
}