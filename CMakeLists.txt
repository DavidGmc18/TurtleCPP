cmake_minimum_required(VERSION 3.22)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/shaders")
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
add_library(turtle SHARED ${SRC_FILES} "${GENERATED_CPP}")

target_compile_definitions(turtle PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(turtle PRIVATE
    $<$<CONFIG:Debug>:-O0 -g>
    $<$<CONFIG:Release>:-O2>
)

target_compile_options(turtle PRIVATE -fPIC)

pkg_check_modules(REQUIRED glfw3)
if(APPLE)
    target_link_libraries(turtle PRIVATE glfw "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation" m pthread dl)
elseif(WIN32)
    target_link_libraries(turtle PRIVATE glfw opengl32 gdi32 user32 kernel32)
else() # assume Linux
    target_link_libraries(turtle PRIVATE glfw X11 pthread dl m)
endif()