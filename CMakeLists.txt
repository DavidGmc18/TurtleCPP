cmake_minimum_required(VERSION 3.22)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CheckSymbolExists)
check_symbol_exists(M_PI "math.h" HAVE_M_PI)
if(NOT HAVE_M_PI)
    add_compile_definitions(M_PI=3.14159265358979323846)
endif()

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders")
set(GENERATED_CPP "${CMAKE_CURRENT_BINARY_DIR}/shaders_gen.cpp")
add_custom_command(
    OUTPUT "${GENERATED_CPP}"
    COMMAND ${CMAKE_COMMAND}
        -DINPUT_DIR=${SHADER_DIR}
        -DOUTPUT_CPP=${GENERATED_CPP}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    DEPENDS ${SHADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    COMMENT "Generating shaders_gen.c"
)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
add_library(turtle SHARED ${SRC_FILES} "${GENERATED_CPP}")

target_compile_definitions(turtle PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(turtle PRIVATE
    $<$<CONFIG:Debug>:-O0 -g>
    $<$<CONFIG:Release>:-O2>
)

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(REQUIRED glfw3)
    target_compile_options(turtle PRIVATE -fPIC)
    target_link_libraries(turtle PRIVATE glfw X11 pthread dl m)
elseif (WIN32)
    find_package(glfw3 CONFIG REQUIRED)
    target_compile_definitions(turtle PRIVATE TURTLE_EXPORTS)
    target_link_libraries(turtle PRIVATE glfw)
endif()