{ pkgs }: {
  deps = [
      pkgs.clang
      pkgs.nasm
			pkgs.cmake
			pkgs.grub2
			pkgs.xorriso
			pkgs.qemu
  ];
}