#ifndef KERNEL_MEMORY_MAP
#define KERNEL_MEMORY_MAP

#include "stdint.h"

struct MemoryMapEntry {
    u64 BaseAddress;
    u64 RegionLength;
    u32 RegionType;
    u32 ExtendedAttributes;
};

extern u8 MemoryRegionCount;

void PrintMemoryMap(MemoryMapEntry* memoryMap, u16 position);

MemoryMapEntry** GetUsableMemoryRegions();

#endif