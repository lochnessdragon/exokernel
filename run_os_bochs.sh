# echo Generating os image...

# mkdir -p build/iso/boot/grub/

# # copy requisite files.
# #cp boot/bootloader_eltorito build/iso/boot/grub # copy the grub bootloader
# cp build/kernel.elf build/iso/boot/ # copy the kernel
# cp boot/grub.cfg build/iso/boot/grub # copy the configuration information

# cd build 
# # genisoimage -R                              \
# #     -b boot/grub/bootloader_eltorito    \
# #     -no-emul-boot                   \
# #     -boot-load-size 4               \
# #     -A os                           \
# #     -input-charset utf8             \
# #     -quiet                          \
# #     -boot-info-table                \
# #     -o os.iso                       \
# #     iso

# grub-mkrescue -o os.iso iso/

# cd ../

echo Running os image in bochs..
bochs -f bochsrc.txt 