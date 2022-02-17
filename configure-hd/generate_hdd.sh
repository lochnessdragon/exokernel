#!/bin/sh

new_image=false

if test ! -f "os.img"; then 
    echo "Creating initial os hd image."; 
    new_image=true

    # create the image file
    dd if=/dev/zero of=os.img bs=512 count=131072

    # use fdisk to setup the partition in the disk
    sfdisk os.img < fdisk_script
fi

# setup loopback devices
mbr_dev=$(sudo losetup --show -f os.img)
echo MBR Device: ${mbr_dev}

normal_dev=$(sudo losetup --show -f os.img -o 1048576)
echo Regular FS: ${normal_dev}

# make an ext4 filesystem with mkfs.ext4
sudo mkfs.ext4 ${normal_dev}
# mount the partition
sudo mkdir /mnt/exokernel-mnt
sudo mount ${normal_dev} /mnt/exokernel-mnt

# install grub with grub-install
if ${new_image}; then
    sudo grub-install --root-directory=/mnt/exokernel-mnt --no-floppy --modules="normal part_msdos ext2 multiboot" ${mbr_dev}
fi

# copy over kernel files
sudo cp ../boot/grub.cfg /mnt/exokernel-mnt/boot/grub
sudo cp ../build/kernel.elf /mnt/exokernel-mnt/boot/

# flush file writes before we unmount the partition
sync

# unmount partition
sudo umount /mnt/exokernel-mnt
sudo rm -rf /mnt/exokernel-mnt

# teardown loopback devices
sudo losetup -d ${mbr_dev}
sudo losetup -d ${normal_dev}
