cmake_minimum_required (VERSION 3.11)
enable_language(C ASM)

set(RC_CAR_CONTROL_BOARD_ELF "rc_car_control_board.elf")

project ("rc_car_control_board")

set(APP_LIB_NAME "rcMainBoardLib")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/app)

# Flash firmware to target.
add_custom_target(flash
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  -c "flash write_image erase ${RC_CAR_CONTROL_BOARD_ELF}" -c "reset run" -c "shutdown"
  DEPENDS ${RC_CAR_CONTROL_BOARD_ELF}
  COMMENT "Flashing target hardware")

# Run OpenOCD as a GDB host.
add_custom_target(gdbhost
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  DEPENDS ${RC_CAR_CONTROL_BOARD_ELF}
  COMMENT "Running OpenOCD as a GDB host.")

