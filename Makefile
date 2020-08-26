
objects := $(patsubst src/%.cpp,tmp/%.o,$(shell find src/ -name "*.cpp")) $(patsubst src/%.s,tmp/%.o,$(shell find src/ -name "*.s"))

tmp/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -o $@ -c $<

tmp/%.o: src/%.s
	mkdir -p $(@D)
	as --32 -o $@ $<

export/mykernel.bin: linker.ld $(objects)
	mkdir -p $(@D)
	ld -melf_i386 -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

export/mykernel.iso: export/mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "RicardOS" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

.PHONY: clean
clean:
	rm -rf tmp
	rm -rf export

build:
	make clean
	make export/mykernel.iso