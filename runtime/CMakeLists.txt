# this project compiles into both the kernel and the userspace c runtime
# libk and libc respectively

project(runtime)

file(GLOB_RECURSE LIB_K_SOURCES "src/*.c")

add_library(k STATIC ${LIB_K_SOURCES})
target_compile_options(k PRIVATE -m32 -ffreestanding -fno-stack-protector -nostartfiles -nodefaultlibs -fno-pie -Wall -Wextra -Werror -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mgeneral-regs-only -D__kernel_libk)
include_directories(include/ ../kernel/)