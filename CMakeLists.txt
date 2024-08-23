cmake_minimum_required(VERSION 3.28)
project(mephOS C ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_COMPILER riscv64-elf-gcc)
set(CMAKE_ASM_COMPILER riscv64-elf-gcc)

set(CMAKE_C_FLAGS "-Wall -Wextra -mcmodel=medany -ffreestanding -nostdlib")
add_link_options(-T linker.ld -lgcc -nostdlib)

# Copy the linker.ld file to the build directory
configure_file(kernel/impl/linker.ld linker.ld COPYONLY)
# standard lib
include_directories(kstdlib/headers)
file(GLOB KSTD_SOURCE kstdlib/impl/*.c)
add_library(kstdlib STATIC ${KSTD_SOURCE})

# libfdt
file(GLOB LIBFDT_SOURCES kernel/external/dtc/libfdt/*.c)
file(GLOB LIBFDT_HEADERS kernel/external/dtc/libfdt/*.h)

foreach (header ${LIBFDT_HEADERS})
    file(RELATIVE_PATH header_rel ${CMAKE_CURRENT_SOURCE_DIR}/kernel/external/dtc/libfdt ${header})
    configure_file(${header} kernel/generated/headers/${header_rel} COPYONLY)
endforeach ()

add_library(libfdt STATIC ${LIBFDT_SOURCES} ${LIBFDT_HEADERS})
target_include_directories(libfdt PRIVATE kernel/external/dtc/libfdt)

file(GLOB SOURCES kernel/impl/*.c kernel/impl/*.s)

add_executable(kernelbin ${SOURCES})
target_link_libraries(kernelbin libfdt  kstdlib)
target_include_directories(kernelbin PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/kernel/generated/headers" kernel/headers)
