run: clean runnable.flp 
	qemu-system-x86_64 runnable.flp

boot: boot.bin
	qemu-system-x86_64 $^

runnable.flp: boot.bin ExtendedProgram.bin
	rm -f $@
	cat $^ > $@

boot.bin: boot.asm
	rm -f $@
	nasm -f bin $^ -o $@

ExtendedProgram.bin: ExtendedProgram.asm
	rm -f $@
	nasm -f bin $^ -o $@

clean:
	rm -f *.bin *.flp