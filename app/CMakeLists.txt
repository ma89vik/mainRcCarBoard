
set(APP_DIR ${CMAKE_SOURCE_DIR}/app)

# Look here for header files.


list(APPEND APP_SOURCE_FILES
  ${APP_DIR}/app_main.c
  ${APP_DIR}/board.c
  ${APP_DIR}/BleBoardHandler/ble_board_handler.c
  ${APP_DIR}/BleBoardHandler/ble_board_message_handler.c
  ${APP_DIR}/BleBoardHandler/message_parser.c
  ${APP_DIR}/Cobs/cobs.c
  ${APP_DIR}/Crc/crc.c
  ${APP_DIR}/Control/car.c
  ${APP_DIR}/Control/car_control.c
  ${APP_DIR}/Control/car_interface.c
  ${APP_DIR}/Control/car_state.c
  ${APP_DIR}/Control/pwm.c
  ${APP_DIR}/Device/I2c/i2c_stm32_hal.c
  ${APP_DIR}/Device/Serial/serial_stm32_hal.c
  ${APP_DIR}/GPS/gps_handler.c
  ${APP_DIR}/IMU/ak8963.c
  ${APP_DIR}/IMU/imu_handler.c
  ${APP_DIR}/IMU/mpu9250.c
  ${APP_DIR}/LinearBuffer/linear_buffer.c
  ${APP_DIR}/Log/log.c
  ${APP_DIR}/Log/usb_log.c
  ${APP_DIR}/Observer/observer.c
  ${APP_DIR}/Protobuf/pb_encode.c
  ${APP_DIR}/Protobuf/pb_decode.c
  ${APP_DIR}/Protobuf/pb_common.c
  ${APP_DIR}/Protobuf/Messages/cmds.pb.c
  ${APP_DIR}/Protobuf/Messages/telemetry.pb.c

  ${APP_DIR}/RingBuffer/ring_buffer.c

)


list(APPEND APP_INC_FILES
  ${APP_DIR}
  ${APP_DIR}/BleBoardHandler
  ${APP_DIR}/Control
  ${APP_DIR}/Cobs
  ${APP_DIR}/Crc
  ${APP_DIR}/Device
  ${APP_DIR}/Device/I2c
  ${APP_DIR}/Device/Serial
  ${APP_DIR}/GPS
  ${APP_DIR}/IMU
  ${APP_DIR}/Log
  ${APP_DIR}/Observer
  ${APP_DIR}/Protobuf/
  ${APP_DIR}/Protobuf/Messages/
  ${APP_DIR}/LinearBuffer
  ${APP_DIR}/RingBuffer
  
 
)


set(APP_SOURCE_FILES ${APP_SOURCE_FILES} PARENT_SCOPE)
set(APP_INC_FILES ${APP_INC_FILES} PARENT_SCOPE)