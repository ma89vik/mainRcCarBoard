
set(APP_DIR ${CMAKE_SOURCE_DIR}/app)

# Look here for header files.


list(APPEND APP_SOURCE_FILES
  ${APP_DIR}/app_main.c
  ${APP_DIR}/board.c
  ${APP_DIR}/Control/car_control.c
  ${APP_DIR}/Control/pwm.c
  ${APP_DIR}/Device/I2c/i2c_stm32_hal.c
  ${APP_DIR}/Device/Serial/serial_stm32_hal.c
  ${APP_DIR}/GPS/gps_handler.c
  ${APP_DIR}/IMU/ak8963.c
  ${APP_DIR}/IMU/imu_handler.c
  ${APP_DIR}/IMU/mpu9250.c
  ${APP_DIR}/LinearBuffer/linear_buffer.c
  ${APP_DIR}/Log/log.c
  ${APP_DIR}/Observer/observer.c
  ${APP_DIR}/RingBuffer/ring_buffer.c

)


list(APPEND APP_INC_FILES
  ${APP_DIR}
  ${APP_DIR}/Control
  ${APP_DIR}/Device
  ${APP_DIR}/Device/I2c
  ${APP_DIR}/Device/Serial
  ${APP_DIR}/GPS
  ${APP_DIR}/IMU
  ${APP_DIR}/Log
  ${APP_DIR}/Observer
  ${APP_DIR}/LinearBuffer
  ${APP_DIR}/RingBuffer
  
 
)


set(APP_SOURCE_FILES ${APP_SOURCE_FILES} PARENT_SCOPE)
set(APP_INC_FILES ${APP_INC_FILES} PARENT_SCOPE)