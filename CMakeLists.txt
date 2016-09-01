cmake_minimum_required(VERSION 3.6)
project(tncg15)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(BIN_DIR "../bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
FILE(GLOB HEADER_FILES ${INCLUDE_DIR}/*.h)
include_directories(${INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_executable(tncg15 ${SOURCE_FILES} ${HEADER_FILES})
