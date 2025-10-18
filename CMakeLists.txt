cmake_minimum_required(VERSION 3.28)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# SDL
add_library(turtle_sdl SHARED ${SRC_FILES})
target_compile_definitions(turtle_sdl PRIVATE BACKEND_SDL)
target_compile_options(turtle_sdl PRIVATE -fPIC)
target_include_directories(turtle_sdl PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(turtle_sdl PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m dl pthread)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(turtle_sdl PRIVATE DEBUG)
endif()

# OpenGL
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/shaders")
set(GENERATED_C "${CMAKE_CURRENT_BINARY_DIR}/shaders_gen.c")
add_custom_command(
    OUTPUT "${GENERATED_C}"
    COMMAND ${CMAKE_COMMAND}
        -DINPUT_DIR=${SHADER_DIR}
        -DOUTPUT_C=${GENERATED_C}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    DEPENDS ${SHADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    COMMENT "Generating shaders_gen.c"
)
add_library(turtle_gl SHARED ${SRC_FILES} "${GENERATED_C}")

target_compile_definitions(turtle_gl PRIVATE BACKEND_GL)
target_compile_options(turtle_gl PRIVATE -fPIC)

set(GLFW_STATIC_LIB $ENV{HOME}/glfw-static/lib/libglfw3.a)
if(APPLE)
    target_link_libraries(turtle_gl PRIVATE ${GLFW_STATIC_LIB} "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation" m pthread dl)
elseif(WIN32)
    target_link_libraries(turtle_gl PRIVATE ${GLFW_STATIC_LIB} opengl32 gdi32 user32 kernel32)
else() # assume Linux
    target_link_libraries(turtle_gl PRIVATE ${GLFW_STATIC_LIB} X11 pthread dl m)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(turtle_gl PRIVATE DEBUG)
endif()