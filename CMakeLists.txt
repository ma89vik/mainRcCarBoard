cmake_minimum_required (VERSION 3.11)
enable_language(C ASM)

set(RC_CAR_CONTROL_BOARD_ELF "rc_car_control_board.elf")

project ("rc_car_control_board")

set(APP_LIB_NAME "rcMainBoardLib")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(BOOTLOADER_NAME "rc_control_bootloader")

add_custom_command(OUTPUT app_bootloader.bin
                   COMMAND cat src/bootloader/${BOOTLOADER_NAME}.bin src/app/${PROJECT_NAME}.bin > app_bootloader.bin
                   DEPENDS src/bootloader/${BOOTLOADER_NAME}.elf src/app/${PROJECT_NAME}.elf)

add_subdirectory(src)

# Flash firmware to target.
add_custom_target(bootloader_flash
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  -c "flash write_image erase src/bootloader/rc_control_bootloader.elf" -c "reset run" -c "shutdown"
  DEPENDS rc_control_bootloader.elf
  COMMENT "Flashing target hardware")

add_custom_target(app_flash
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  -c "flash write_image erase src/app/rc_car_control_board.elf" -c "reset run" -c "shutdown"
  DEPENDS rc_car_control_board.elf
  COMMENT "Flashing target hardware")

add_custom_target(app_bootloader_flash
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd"
  -f target/stm32f4x.cfg -c "init" -c "reset halt"
  -c "flash write_image erase app_bootloader.bin 0x8000000" -c "reset run" -c "shutdown"
  DEPENDS app_bootloader.bin
  COMMENT "Flashing target hardware")


# Run OpenOCD
add_custom_target(openocd
  openocd -f interface/stlink-v2-1.cfg -c "transport select hla_swd" -f target/stm32f4x.cfg -c "init" -c "reset halt"
  COMMENT "Running OpenOCD as a GDB host.")

