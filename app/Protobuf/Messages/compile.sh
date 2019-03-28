#!/bin/bash
protoc -ocmds.pb cmds.proto
protoc -otelemetry.pb telemetry.proto
python ~/NRF/Tools/nanopb/generator/nanopb_generator.py cmds.pb
python ~/NRF/Tools/nanopb/generator/nanopb_generator.py telemetry.pb
