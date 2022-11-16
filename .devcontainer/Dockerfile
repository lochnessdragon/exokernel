FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

# install grub-mkrescue, nasm and qemu
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends nasm qemu qemu-system qemu-system-gui grub2 grub2-common xorriso