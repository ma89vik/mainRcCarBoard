set(TEST_APP_NAME "RunAllTests")

set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(CPPUTEST_HOME "~/cpputest/")


set(CPPUTEST_INCLUDE_DIRS "${CPPUTEST_HOME}/include")
set(CPPUTEST_LIBRARIES "${CPPUTEST_HOME}/src/CppUTest")
set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)


list(APPEND TEST_SOURCE_FILES
  ${TEST_DIR}/ring_buffer_test.cpp
  ${TEST_DIR}/AllTest.cpp

)


list(APPEND TEST_INC_FILES
  )

include_directories(${CPPUTEST_INCLUDE_DIRS})
link_directories(${CPPUTEST_LIBRARIES})


add_executable(${TEST_APP_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS})
