# todo: strip final kernel file
# todo: debug/release modes

cmake_minimum_required(VERSION 3.0.0)

option(BUILD_ISO "Build an iso file" ON)
option(BUILD_HDD "Build a hard drive image" ON)

option(CI "Option should be on only on CI servers." OFF)
if(CI)
set(BUILD_ISO OFF)
set(BUILD_HDD OFF)
endif()

add_subdirectory(runtime/)

project(kernel)

enable_language(ASM_NASM)

# setup assembly source files
file(GLOB_RECURSE KASMSRC "kernel/*.asm")
set_property(SOURCE ${KASMSRC} PROPERTY LANGUAGE ASM_NASM)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f ${CMAKE_ASM_NASM_OBJECT_FORMAT}")

file(GLOB_RECURSE KCSRC "kernel/*.c")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -fno-pie -mno-red-zone")

set(KFILES ${KASMSRC} ${KCSRC})

add_executable(kernel.elf ${KFILES})

target_include_directories(kernel.elf PRIVATE ${CMAKE_SOURCE_DIR}/kernel/common/ ${CMAKE_SOURCE_DIR}/kernel/arch/i386/ ${CMAKE_SOURCE_DIR}/kernel/ ${CMAKE_SOURCE_DIR}/runtime/include)
target_link_libraries(kernel.elf k)
# make sure to link with the custom script and strip the files! (-s to strip files maybe add to release candidate)
target_link_options(kernel.elf PRIVATE -T${CMAKE_SOURCE_DIR}/kernel/link.ld -fno-pie)

if(BUILD_ISO)
	add_custom_target(os-iso ALL 
     COMMAND echo Building cd-rom image
     COMMAND mkdir -p iso/boot/grub
     COMMAND cp kernel.elf iso/boot/
     COMMAND cp ${CMAKE_SOURCE_DIR}/boot/grub.cfg iso/boot/grub
     COMMAND grub-mkrescue -o os.iso iso/
     BYPRODUCTS os.iso
     DEPENDS kernel.elf
     VERBATIM)
endif()

if(BUILD_HDD)
     add_custom_target(os-hdd ALL
          COMMAND echo Building harddisk image
          COMMAND cp ../configure-hd/fdisk_script ./
          COMMAND ../configure-hd/generate_hdd.sh
          BYPRODUCTS os.img 
          DEPENDS kernel.elf 
          VERBATIM)
endif()