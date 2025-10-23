cmake_minimum_required(VERSION 3.22)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# SDL
add_library(turtle_sdl SHARED ${SRC_FILES})
target_compile_definitions(turtle_sdl PRIVATE BACKEND_SDL $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(turtle_sdl PRIVATE -fPIC)
target_include_directories(turtle_sdl PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(turtle_sdl PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m dl pthread)

# OpenGL
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
add_library(turtle_gl SHARED ${SRC_FILES} "${GENERATED_CPP}")

target_compile_definitions(turtle_gl PRIVATE BACKEND_GL $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(turtle_gl PRIVATE
    $<$<CONFIG:Debug>:-O0 -g>
    $<$<CONFIG:Release>:-O2>
)

target_compile_options(turtle_gl PRIVATE -fPIC)

pkg_check_modules(REQUIRED glfw3)
if(APPLE)
    target_link_libraries(turtle_gl PRIVATE glfw "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation" m pthread dl)
elseif(WIN32)
    target_link_libraries(turtle_gl PRIVATE glfw opengl32 gdi32 user32 kernel32)
else() # assume Linux
    target_link_libraries(turtle_gl PRIVATE glfw X11 pthread dl m)
endif()