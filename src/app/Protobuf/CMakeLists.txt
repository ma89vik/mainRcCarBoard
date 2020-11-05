
set(MESSAGE_FOLDER "${CMAKE_CURRENT_LIST_DIR}/Messages")

list(APPEND PROTO_FILES
    "${MESSAGE_FOLDER}/cmds.proto"
    "${MESSAGE_FOLDER}/state.proto"
    "${MESSAGE_FOLDER}/telemetry.proto")

list(APPEND MESSAGES_SRCS
    "cmds.pb.c"
    "state.pb.c"
    "telemetry.pb.c")

list(APPEND MESSAGES_HEADERS
    "cmds.pb.c"
    "state.pb.c"
    "telemetry.pb.c")

list(APPEND PB_SRCS
    "pb_common.c"
    "pb_decode.c"
    "pb_encode.c")

#set(MESSAGE_SOURCES ${MESSAGES})
#list(TRANSFORM MESSAGE_SOURCES PREPEND "${CMAKE_CURRENT_BINARY_DIR}/")
#list(TRANSFORM MESSAGE_SOURCES APPEND ".c")

#set(MESSAGE_HEADERS ${MESSAGES})
#list(TRANSFORM MESSAGE_HEADERS PREPEND "${CMAKE_CURRENT_BINARY_DIR}/")
#list(TRANSFORM MESSAGE_HEADERS APPEND ".h")


add_custom_command(OUTPUT ${MESSAGES_SRCS} ${MESSAGE_HEADERS}
                   COMMAND nanopb_generator -D . -I ${MESSAGE_FOLDER} ${PROTO_FILES}
                   DEPENDS ${PROTO_FILES})

message(WARNING "${MESSAGE_SOURCES}")

add_library(protobuf STATIC ${MESSAGES_SRCS} ${MESSAGE_HEADERS} ${PB_SRCS})
target_include_directories(protobuf PUBLIC .)