cmake_minimum_required(VERSION 3.22)
project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

add_library(turtle SHARED ${SRC_FILES})
target_compile_definitions(turtle PRIVATE BACKEND_SDL $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(turtle PRIVATE -fPIC)
target_include_directories(turtle PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(turtle PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m dl pthread)