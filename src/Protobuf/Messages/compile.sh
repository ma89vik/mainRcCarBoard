#!/bin/bash
protoc -ocmds.pb cmds.proto
protoc -otelemetry.pb telemetry.proto
protoc -ostate.pb state.proto
python ~/NRF/Tools/nanopb/generator/nanopb_generator.py cmds.pb
python ~/NRF/Tools/nanopb/generator/nanopb_generator.py telemetry.pb
python ~/NRF/Tools/nanopb/generator/nanopb_generator.py state.pb
