set(CMAKE_SYSTEM_NAME stm32)
set(CMAKE_SYSTEM_PROCESSOR STM32F4)

if(NOT $ENV{TOOLCHAIN_PATH})
    message(WARNING "TOOLCHAIN_PATH not set")
end()

set(CMAKE_C_COMPILER $ENV{TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER $ENV{TOOLCHAIN_PATH}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER $ENV{TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")


set(CPU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mno-thumb-interwork -mthumb -specs=nosys.specs")
set(COMMON_FLAGS "-Wall -ffunction-sections -fdata-sections ${CPU_FLAGS}")

set(CMAKE_C_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_INIT "-lc -lm -lnosys -Wl,--gc-section")
