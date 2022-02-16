# todo: strip final kernel file
# todo: debug/release modes

cmake_minimum_required(VERSION 3.0.0)

option(BUILD_ISO "Build an iso file" ON)
option(BUILD_HDD "Build a hard drive image" ON)

project(kernel)

enable_language(ASM_NASM)

# setup assembly source files
file(GLOB_RECURSE KASMSRC "kernel/*.asm")
set_property(SOURCE ${KASMSRC} PROPERTY LANGUAGE ASM_NASM)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

file(GLOB KCSRC "kernel/*.c")

set(KFILES ${KASMSRC} ${KCSRC})

add_executable(kernel.elf ${KFILES})
target_include_directories(kernel.elf PRIVATE ${CMAKE_SOURCE_DIR}/kernel/common/ ${CMAKE_SOURCE_DIR}/kernel/arch/i386/)
target_compile_options(kernel.elf PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

# make sure to link with the custom script and strip the files!
target_link_options(kernel.elf PRIVATE -T${CMAKE_SOURCE_DIR}/kernel/link.ld -s)

if(BUILD_ISO)
	add_custom_target(os-iso ALL 
     COMMAND mkdir -p iso/boot/grub
     COMMAND cp kernel.elf iso/boot/
     COMMAND cp ${CMAKE_SOURCE_DIR}/boot/grub.cfg iso/boot/grub
     COMMAND grub-mkrescue -o os.iso iso/
     BYPRODUCTS os.iso
     DEPENDS kernel.elf
     VERBATIM)
endif()