cmake_minimum_required (VERSION 3.6)

set(PROJ "rcMainBoard")
project (${PROJ})

set(APP_LIB_NAME "rcMainBoardLib")

set(ARM_NONE_EABI_TOOLCHAIN_PATH "/usr")


# For diagnostic tools like rtags.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




# language standard/version settings
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 98)

if(${BUILD_TYPE} STREQUAL "MCU")
  MESSAGE(STATUS "Building for MCU")
  # configure cmake to use the arm-none-eabi-gcc
  set(CMAKE_C_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")
  set(CMAKE_CXX_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/arm-none-eabi-c++")
  set(CMAKE_ASM_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")

  set(CPU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mno-thumb-interwork -mthumb")
  add_definitions(-DSTM32F407xx -DUSE_HAL_DRIVER)

  set(CMAKE_EXE_LINKER_FLAGS "-lc -lm -lnosys -T ${CMAKE_SOURCE_DIR}/board/STM32F407VGTx_FLASH.ld -Wl,--gc-section")
elseif(${BUILD_TYPE} STREQUAL "UNIT_TEST")
  MESSAGE(STATUS "Building for unit test")
  set(CMAKE_C_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/gcc")
  set(CMAKE_CXX_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/c++")
  set(CMAKE_ASM_COMPILER "${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin/gcc")

  set(CPU_FLAGS "")
  add_definitions(-DSTM32F407xx -DUSE_HAL_DRIVER)
endif()

set(COMMON_FLAGS "-O0 -g -Wall -ffunction-sections -fdata-sections ${CPU_FLAGS}")

# compiler/assambler/linker flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")

add_subdirectory(app)
add_subdirectory(board)


list(APPEND SOURCE_FILES
    ${BOARD_SOURCE_FILES}
    ${APP_SOURCE_FILES}
)

list(APPEND INC_FILES
    ${BOARD_INC_FILES}
    ${APP_INC_FILES}
)



include_directories(${INC_FILES})


 # Some trickery to get CMake to deal with our assembler code.
set_property(SOURCE ${CMAKE_SOURCE_DIR}/board/startup_stm32f407xx.s PROPERTY LANGUAGE C)

add_executable(${PROJ}.elf ${SOURCE_FILES})

if(${BUILD_TYPE} STREQUAL "UNIT_TEST")
  add_library(${APP_LIB_NAME} ${SOURCE_FILES})
  add_subdirectory(test)
endif()


# Generate assembly listing.
add_custom_command(
  TARGET ${PROJ}.elf
  COMMAND "arm-none-eabi-objdump"
  ARGS "-S" "${PROJ}.elf" ">>" "${PROJ}.lst")

# Flash firmware to target.
add_custom_target(flash
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  -c "flash write_image erase ${PROJ}.elf" -c "reset run" -c "shutdown"
  DEPENDS ${PROJ}.elf
  COMMENT "Flashing target hardware")

# Run OpenOCD as a GDB host.
add_custom_target(gdbhost
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  DEPENDS ${PROJ}.elf
  COMMENT "Running OpenOCD as a GDB host.")