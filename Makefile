CC=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-gcc
CXX=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-g++
LD=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-ld
OBJCOPY=/home/psifunction/tools/x86_64-elf/bin/x86_64-elf-objcopy

run: clean runnable.flp 
	qemu-system-x86_64 runnable.flp

boot: boot.bin
	qemu-system-x86_64 $^

runnable.flp: boot.bin kernel.bin
	cat $^ > $@

boot.bin: boot.asm
	nasm -f bin $^ -o $@

kernel.bin: kernel.tmp
	$(OBJCOPY) -O binary $^ $@

kernel.tmp: ExtendedProgram.o kernel.o
	$(LD) -o $@ -Ttext 0x7e00 $^

ExtendedProgram.o: ExtendedProgram.asm
	nasm -f elf64 $^ -o $@

kernel.o: kernel.cpp
	$(CC) -ffreestanding -mno-red-zone -m64 -c $^ -o $@


clean:
	rm -f *.bin *.flp *.o *.tmp