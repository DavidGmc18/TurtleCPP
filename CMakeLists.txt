cmake_minimum_required(VERSION 3.28)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif() #  TOOD defualt debug

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

add_library(turtle_sdl SHARED ${SRC_FILES})
target_compile_definitions(turtle_sdl PRIVATE BACKEND_SDL)
target_compile_options(turtle_sdl PRIVATE -fPIC)
target_include_directories(turtle_sdl PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(turtle_sdl PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m dl pthread)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(turtle_sdl PRIVATE DEBUG)
endif()

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/shaders_gen.o
           ${CMAKE_BINARY_DIR}/shaders_gen.h
    COMMAND ${CMAKE_SOURCE_DIR}/gen_shaders.sh
            "src/renderer/shaders"
            "src/renderer/shaders/shaders.h"
            "build/shaders_gen.o"
    DEPENDS ${CMAKE_SOURCE_DIR}/gen_shaders.sh
)
add_library(turtle_gl SHARED ${SRC_FILES} ${CMAKE_BINARY_DIR}/shaders_gen.o)
target_compile_definitions(turtle_gl PRIVATE BACKEND_GL)
target_compile_options(turtle_gl PRIVATE -fPIC)
target_include_directories(turtle_gl PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(turtle_gl PRIVATE glfw m dl pthread)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(turtle_gl PRIVATE DEBUG)
endif()