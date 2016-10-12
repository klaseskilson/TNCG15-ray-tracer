cmake_minimum_required(VERSION 2.8)
project(tncg15)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(BIN_DIR "bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

FILE(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
FILE(GLOB HEADER_FILES ${INCLUDE_DIR}/*.h)
include_directories(${INCLUDE_DIR})

find_package(GLM REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BIN_DIR}")

add_executable(tncg15 ${SOURCE_FILES} ${HEADER_FILES})
