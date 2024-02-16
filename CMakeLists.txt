cmake_minimum_required(VERSION 3.22)
project(chip_8_emulator VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

include_directories(${PROJECT_SOURCE_DIR}/src/include)

find_library(SDL2_LIBRARY NAMES SDL2)

if (NOT SDL2_LIBRARY)
  message(FATAL_ERROR "SDL2 not found")
endif()

file(GLOB SOURCES
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(c8 ${SOURCES})
target_link_libraries(c8 ${SDL2_LIBRARY})

# Debug

set(CMAKE_BUILD_TYPE Debug)

add_executable(c8d ${SOURCES})
target_link_libraries(c8d ${SDL2_LIBRARY})

target_compile_options(c8d PRIVATE -g)

add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

file(REMOVE_RECURSE
  ${CMAKE_BINARY_DIR}/*
)
