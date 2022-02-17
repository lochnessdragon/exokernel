# runs qemu with a few parameters
# -d = run qemu with support for gdb debugging (opens a port on localhost:1234)

extraflags="-monitor stdio"

while getopts d: flag
do
    case "${flag}" in
        d) extraflags="${extraflags} -s";;
    esac
done

qemu-system-x86_64 -cdrom build/os.iso ${extraflags}