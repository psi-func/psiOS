CC=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-gcc
CXX=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-g++
LD=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-ld
OBJCOPY=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-objcopy

CFLAGS=-Iinclude

run: clean runnable.flp
	@chmod +x runnable.flp
	qemu-system-x86_64 runnable.flp

runnable.flp: boot.bin kernel.bin
	@cat $^ > $@

boot.bin: boot/boot.asm
	nasm -f bin $^ -i boot -o $@

kernel.bin: ExtendedProgram.o kernel.o vga.o Binaries.o IDT.o PIC.o KeyboardScanCode.o
	$(LD) -T"link.ld" $^

ExtendedProgram.o: arch/ExtendedProgram.asm
	nasm -f elf64 $^ -i arch -o $@

kernel.o: kernel.cpp
	$(CC) $(CFLAGS) -Ttext 0x800 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

vga.o: vga.cpp
	$(CC) $(CFLAGS) -Ttext 0x800 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

IDT.o: IDT.cpp
	$(CC) $(CFLAGS) -Ttext 0x800 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

PIC.o: PIC.cpp
	$(CC) $(CFLAGS) -Ttext 0x800 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

KeyboardScanCode.o: KeyboardScanCode.cpp 
	$(CC) $(CFLAGS) -Ttext 0x800 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

Binaries.o: Binaries.asm
	nasm -f elf64 $^ -o $@

clean:
	rm -f *.bin *.flp *.o *.tmp