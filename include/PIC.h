#ifndef PIC_INTERRUPT_CONTROLLER
#define PIC_INTERRUPT_CONTROLLER

#include "stdint.h"

constexpr u16 PIC1_COMMAND = 0x20;
constexpr u16 PIC1_DATA = PIC1_COMMAND + 1;
constexpr u16 PIC2_COMMAND = 0xa0;
constexpr u16 PIC2_DATA=PIC2_COMMAND + 1;

// control words
constexpr u16 ICW1_ICW4 = 0x01;
constexpr u16 ICW1_SINGLE = 0x02;	/* Single (cascade) mode */
constexpr u16 ICW1_INTERVAL4 = 0x04;		/* Call address interval 4 (8) */
constexpr u16 ICW1_LEVEL = 0x08;		/* Level triggered (edge) mode */
constexpr u16 ICW1_INIT = 0x10;


constexpr u16 ICW4_8086 = 0x01; // 8086 PIC mode 
constexpr u16 ICW4_AUTO = 0x02; // AUTO (normal) EOI
constexpr u16 ICW4_BUF_SLAVE = 0x08; // Buffered mode/slave
constexpr u16 ICW4_BUF_MASTER = 0x0C; // Buffered mode/master
constexpr u16 ICW4_SFNM = 0x10; // Special fully nested (not)

/**
 * @brief initialize PIC device
 * 
 * @param offset1 vector offset for Master PIC1 -> vectors become [offset1..offset1+7]
 * @param offset2 vector offset for PIC2 (same as offset1 for PIC1)
 */
void PIC_remap(u8 offset1, u8 offset2);

/**
 * @brief disable PIC device
 * 
 */
void PIC_disable();


#endif