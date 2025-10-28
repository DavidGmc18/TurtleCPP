cmake_minimum_required(VERSION 3.22)

if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(Turtle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if((WIN32 OR APPLE) AND NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER clang)
endif()
if((WIN32 OR APPLE) AND NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER clang++)
endif()
if(NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/color_map.hpp
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generate_color_map.py
    DEPENDS ${CMAKE_SOURCE_DIR}/scripts/generate_color_map.py
    COMMENT "Generating color_map.hpp using Python"
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/icon.hpp
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generate_icon.py
    DEPENDS ${CMAKE_SOURCE_DIR}/scripts/generate_icon.py
    COMMENT "Generating icon.hpp using Python"
)
add_custom_target(generate_headers DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/color_map.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/icon.hpp
)

include(CheckSymbolExists)
check_symbol_exists(M_PI "math.h" HAVE_M_PI)
if(NOT HAVE_M_PI)
    add_compile_definitions(M_PI=3.14159265358979323846)
endif()

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders")
file(GLOB SHADER_FILES "${SHADER_DIR}/*")
set(GENERATED_CPP "${CMAKE_CURRENT_BINARY_DIR}/shaders_gen.cpp")
add_custom_command(
    OUTPUT "${GENERATED_CPP}"
    COMMAND ${CMAKE_COMMAND}
        -DINPUT_SHADERS="${SHADER_FILES}"
        -DOUTPUT_CPP=${GENERATED_CPP}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    DEPENDS ${SHADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_shaders.cmake
    COMMENT "Generating shaders_gen.cpp"
)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
add_library(turtle SHARED ${SRC_FILES} "${GENERATED_CPP}")

add_dependencies(turtle generate_headers)

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
elseif(APPLE)
    find_package(glfw3 CONFIG QUIET)
    if(NOT glfw3_FOUND)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GLFW REQUIRED glfw3)
        include_directories(${GLFW_INCLUDE_DIRS})
        link_directories(${GLFW_LIBRARY_DIRS})
        target_link_libraries(turtle PRIVATE ${GLFW_LIBRARIES})
    else()
        target_link_libraries(turtle PRIVATE glfw)
    endif()
    target_link_libraries(turtle PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()