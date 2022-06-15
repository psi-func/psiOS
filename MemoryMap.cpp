#include "MemoryMap.h"
#include "vga.hpp"

void PrintMemoryMap(MemoryMapEntry* memoryMap, u16 position) {
    set_cursor_position(position);
    print_screen("Memory Base: "); 
    print_screen(to_string(memoryMap->BaseAddress));

    set_cursor_position(position + VGA_WIDTH);
    print_screen("Region Length: ");
    print_screen(to_string(memoryMap->RegionLength));

    set_cursor_position(position + 2 * VGA_WIDTH);
    print_screen("Memory Type: ");
    print_screen(to_string(memoryMap->RegionType));

    set_cursor_position(position + 3 * VGA_WIDTH);
    print_screen("Memory Attributes: ");
    print_screen(to_hex_string(memoryMap->ExtendedAttributes));
    
    set_cursor_position(position + 5 * VGA_WIDTH);

}

MemoryMapEntry** GetUsableMemoryRegions() {
    static MemoryMapEntry* UsableMemoryRegions[10];
    static bool MemoryRegionInit = false;
    if (MemoryRegionInit) {
        return UsableMemoryRegions;
    } 
    u8 UsableMemoryRegionIndex = 0;
    for (u8 i = 0; i < MemoryRegionCount; ++i) {
        MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
        memMap += i;
        if (memMap->RegionType == 1) {
            UsableMemoryRegions[UsableMemoryRegionIndex] = memMap;
            ++UsableMemoryRegionIndex;
        }
    }
    
    UsableMemoryRegions[UsableMemoryRegionIndex] = nullptr;
    MemoryRegionInit = true;
    return UsableMemoryRegions;
}