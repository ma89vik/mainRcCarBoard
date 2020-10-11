set(SOURCE_DIR Src)
set(CMSIS_DIR Drivers/CMSIS)
set(DEVICE_DIR Drivers/CMSIS/Device/ST/STM32F4xx)
set(HAL_DIR Drivers/STM32F4xx_HAL_Driver)


# Look here for header files.

list(APPEND BOARD_INC_FILES
  "Inc"
  "${CMSIS_DIR}/Include"
  "${DEVICE_DIR}/Include"
  "${HAL_DIR}/Inc"
  "${RTOS_DIR}/include"
  "${RTOS_DIR}/CMSIS_RTOS"
  "${RTOS_DIR}/portable/GCC/ARM_CM4F"
  "${CMAKE_SOURCE_DIR}/app/include"
)


list(APPEND BOARD_SOURCE_FILES
  ${SOURCE_DIR}/stm32f4xx_it.c
  ${SOURCE_DIR}/stm32f4xx_hal_msp.c
  ${SOURCE_DIR}/gpio.c
  ${SOURCE_DIR}/dma.c
  ${SOURCE_DIR}/usart.c
  ${SOURCE_DIR}/system_stm32f4xx.c
  ${HAL_DIR}/Src/stm32f4xx_hal_cortex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_dma_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_dma.c
  ${HAL_DIR}/Src/stm32f4xx_hal_exti.c
  ${HAL_DIR}/Src/stm32f4xx_hal_flash_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_flash_ramfunc.c
  ${HAL_DIR}/Src/stm32f4xx_hal_flash.c
  ${HAL_DIR}/Src/stm32f4xx_hal_gpio.c
  ${HAL_DIR}/Src/stm32f4xx_hal_pwr_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_pwr.c
  ${HAL_DIR}/Src/stm32f4xx_hal_rcc_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_rcc.c
  ${HAL_DIR}/Src/stm32f4xx_hal_tim_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_tim.c
  ${HAL_DIR}/Src/stm32f4xx_hal_uart.c
  ${HAL_DIR}/Src/stm32f4xx_hal.c
  )

add_compile_definitions(STM32F407xx USE_HAL_DRIVER)

add_library(board STATIC ${BOARD_SOURCE_FILES})

target_compile_definitions(board PUBLIC STM32F407xx=1 USE_HAL_DRIVER=1)

target_include_directories(board PUBLIC ${BOARD_INC_FILES})


  

