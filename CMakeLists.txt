cmake_minimum_required (VERSION 3.11)

set(PROJ "rcMainBoard")
project ("rc_car_control_board")

set(APP_LIB_NAME "rcMainBoardLib")


# For diagnostic tools like rtags.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

MESSAGE(STATUS "Building for MCU")

add_definitions(-DSTM32F407xx -DUSE_HAL_DRIVER)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/board/STM32F407VGTx_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS -T ${LINKER_SCRIPT} )

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

set(EXECUTABLE_NAME ${PROJ})
add_executable(${EXECUTABLE_NAME}.elf ${SOURCE_FILES})
#add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
#set_target_properties(${EXECUTABLE_NAME} PROPERTIES SUFFIX ".out")


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