[![Build Actions Status](https://github.com/ma89vik/rc_car_control_board/workflows/CMake/badge.svg)](https://github.com/ma89vik/rc_car_control_board/actions)
# Main Control Board for Radio Controlled Car

# Building the project
 * Set TOOLCHAIN_PATH to the path to your arm-none-eabi folder
 * Install python requirements from requirements.txt

# Features
 * Bootloader with ECDSA signature

ToDO: App:

uC: map from BT cmds to vehicle cmds safety functions: watchdog, bootloader, OTA logging, over BLE, to flash?

Ideas: BLE: long range mode, test limits

OpenMV -> ACS, Road following

Distance sensor -> ACS

IMU -> INS GPS -> Google maps integration, logging, waypoints

PCB layout

RFID ignition key

QR code for ?

Headlights, other "visual" stash

Controller
