import serial
import time
import subprocess
from pathlib import Path
import crcmod
from cobs import cobs
from enum import IntEnum

import state_pb2 as car_state
import cmds_pb2 as car_cmd

PROTOC_PATH = Path("C:/Users/Marius/Downloads/protoc-3.14.0-win64/bin/protoc")
PROTO_FILES_DIR = Path("../../Protobuf/Messages")
PROTO_FILES = [str(file_path) for file_path in  list(PROTO_FILES_DIR.glob("*.proto"))]

# this is a standard CCITT CRC even if it does not look like
# (crcmod applies xorOut to initCrc, so initCrc is in reality 0xffff, not 0)
_CRC_FUNC = crcmod.mkCrcFun(0x11021, initCrc=0xFFFF, xorOut=0, rev=False)


def generate_proto(protoc_path):
    print("Generate python files for: {}".format(PROTO_FILES))
    #subprocess.run([str(PROTOC_PATH), "-I={}".format(str(PROTO_FILES_DIR)), "--python_out=.", *PROTO_FILES])
    return

class MsgId(IntEnum):
    ID_ERROR = 0
    ID_SPEED_CMD = 1
    ID_STEERING_CMD = 2
    ID_STATE_CMD = 3


def create_steering_cmd_msg(steering_setpoint):
    steering_cmd = car_cmd.SteeringCmd()
    steering_cmd.steeringSetPoint = steering_setpoint

    return steering_cmd


def create_speed_cmd_msg(steering_setpoint):
    steering_cmd = car_cmd.SteeringCmd()
    steering_cmd.steeringSetPoint = steering_setpoint

    return steering_cmd

def create_state_cmd_msg(state):
    state_cmd = car_cmd.StateCmd()
    state_cmd.setCarState = state

    return state_cmd

def encode_message(protobuf_msg, msg_id):
    protobuf_bytes = protobuf_msg.SerializeToString()
    crc_res = _CRC_FUNC(protobuf_bytes)

    header = [len(protobuf_bytes), msg_id, crc_res & 0xff, (crc_res >> 8) & 0xff]
    msg = bytearray(header)
    msg += (protobuf_bytes)

    print("Sending message: {} with crc = {}".format(protobuf_msg, crc_res))

    encoded_msg = bytearray(cobs.encode(msg))
    encoded_msg.append(0x0)

    return encoded_msg


class ControlBoard():

    def __init__(self):
        print("Init")
        generate_proto(PROTOC_PATH)


    def connect(self, port):
        self.serial = serial.Serial(port, baudrate=115200)


    def set_steering(self, steering_cmd):
        msg = create_steering_cmd_msg(steering_cmd)
        print(msg)
        self.serial.write(encode_message(msg, MsgId.ID_STEERING_CMD))


    def set_speed(self, speed_cmd):
        msg = create_speed_cmd_msg(speed_cmd)
        print(msg)
        self.serial.write(encode_message(msg, MsgId.ID_SPEED_CMD))

    def set_mode(self, state):
        msg = create_state_cmd_msg(state)
        print(repr(msg))
        self.serial.write(encode_message(msg, MsgId.ID_STATE_CMD))        


def main():

    with serial.Serial('COM4', baudrate=115200) as ser:
        while(1):
            ser.write(encode_message(create_cmd_msg(50), 2))
            print("Sleeping...")
            time.sleep(1)

if __name__ == "__main__":
    main()