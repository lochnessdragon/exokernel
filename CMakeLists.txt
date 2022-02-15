cmake_minimum_required(VERSION 3.0.0)

project(kernel)

enable_language(ASM_NASM)

# setup assembly source files
file(GLOB KASMSRC "kernel/*.asm")
set_property(SOURCE ${KASMSRC} PROPERTY LANGUAGE ASM_NASM)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

file(GLOB KCSRC "kernel/*.c")

set(KFILES ${KASMSRC} ${KCSRC})

add_executable(kernel ${KFILES})
target_compile_options(kernel PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)