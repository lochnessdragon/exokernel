# Exokernel

Another exokernel project. Hopefully, we can study some pitfalls and shortcomings of exokernels and find solutions with this repo.

## Usage

### Building

To build the file, make sure you have grub, cmake, xorriso, nasm and gcc or clang installed. Then, just run cmake as normal.

### Running
After you get the output iso file, you can probably flash it to a disk, however, this is not recommended nor supported at this time.

Instead, if you have qemu or bochs installed, you can boot the os image with either `./run_os_bochs.sh` or `./run_os_qemu.sh`.

## Contributing

## License
This code is licensed under an MIT license.
