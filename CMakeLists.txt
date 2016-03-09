project(KiteOS)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_FLAGS "-g -std=gnu99 -ffreestanding -Iinclude -Iinclude/libc -Wall")
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_NASM_FLAGS -felf32)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

enable_language(ASM_NASM)

file(GLOB_RECURSE C_SOURCES
src/kernel/*.c
src/kernel/init/*.c
src/kernel/mem/*.c
src/kernel/drivers/*.c
src/kernel/drivers/fs/*.c
src/kernel/drivers/input/*.c
src/kernel/drivers/timing/*.c
src/kernel/sys/*.c
src/libc/*.c
)

file(GLOB_RECURSE ASM_SOURCES
src/kernel/init/*.asm
)

file(COPY other/hdd.img DESTINATION .${CMAKE_FILES_DIRECTORY}/..)

include_directories(include include/libc)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-T ../src/kernel/link.ld -lgcc -ffreestanding -nostdlib")
add_executable(kernelimz src/kernel/boot/boot.asm ${C_SOURCES} ${ASM_SOURCES})
