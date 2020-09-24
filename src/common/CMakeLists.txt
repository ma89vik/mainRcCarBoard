
list(APPEND COMMON_INC_DIRS
   "include"
)

set(COMMON_LIB common)

add_library(${COMMON_LIB} INTERFACE)

target_include_directories(${COMMON_LIB} INTERFACE ${COMMON_INC_DIRS})
