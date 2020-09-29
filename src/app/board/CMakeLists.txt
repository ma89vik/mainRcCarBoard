set(SOURCE_DIR Src)
set(CMSIS_DIR Drivers/CMSIS)
set(DEVICE_DIR Drivers/CMSIS/Device/ST/STM32F4xx)
set(HAL_DIR Drivers/STM32F4xx_HAL_Driver)
set(RTOS_DIR Middlewares/Third_Party/FreeRTOS/Source)


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
  ${SOURCE_DIR}/freertos.c
  ${SOURCE_DIR}/stm32f4xx_it.c
  ${SOURCE_DIR}/stm32f4xx_hal_msp.c
  ${SOURCE_DIR}/stm32f4xx_hal_timebase_tim.c
  ${SOURCE_DIR}/gpio.c
  ${SOURCE_DIR}/dma.c
  ${SOURCE_DIR}/i2c.c
  ${SOURCE_DIR}/spi.c
  ${SOURCE_DIR}/tim.c
  ${SOURCE_DIR}/usart.c
  ${SOURCE_DIR}/system_stm32f4xx.c
  startup_stm32f407xx.S
  ${HAL_DIR}/Src/stm32f4xx_hal.c
  ${HAL_DIR}/Src/stm32f4xx_hal_exti.c
  ${HAL_DIR}/Src/stm32f4xx_hal_cortex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_dma.c
  ${HAL_DIR}/Src/stm32f4xx_hal_dma_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_flash.c
  ${HAL_DIR}/Src/stm32f4xx_hal_flash_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_gpio.c
  ${HAL_DIR}/Src/stm32f4xx_hal_i2c.c
  ${HAL_DIR}/Src/stm32f4xx_hal_i2c_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_uart.c
  ${HAL_DIR}/Src/stm32f4xx_hal_pwr.c
  ${HAL_DIR}/Src/stm32f4xx_hal_pwr_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_rcc.c
  ${HAL_DIR}/Src/stm32f4xx_hal_rcc_ex.c
  ${HAL_DIR}/Src/stm32f4xx_hal_spi.c
  ${HAL_DIR}/Src/stm32f4xx_hal_tim.c
  ${HAL_DIR}/Src/stm32f4xx_hal_tim_ex.c
  ${RTOS_DIR}/croutine.c 
  ${RTOS_DIR}/event_groups.c 
  ${RTOS_DIR}/list.c 
  ${RTOS_DIR}/queue.c 
  ${RTOS_DIR}/stream_buffer.c 
  ${RTOS_DIR}/tasks.c 
  ${RTOS_DIR}/timers.c 
  ${RTOS_DIR}/CMSIS_RTOS/cmsis_os.c 
  ${RTOS_DIR}/portable/MemMang/heap_4.c 
  ${RTOS_DIR}/portable/GCC/ARM_CM4F/port.c  
  )

add_compile_definitions(STM32F407xx USE_HAL_DRIVER)

add_library(board STATIC ${BOARD_SOURCE_FILES})

target_compile_definitions(board PUBLIC STM32F407xx=1 USE_HAL_DRIVER=1)

target_include_directories(board PUBLIC ${BOARD_INC_FILES})


  

