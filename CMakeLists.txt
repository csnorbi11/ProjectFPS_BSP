cmake_minimum_required(VERSION 3.30)
project(ProjectFPS_BSP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "./src/*.cpp")
file(GLOB HEADERS "./src/headers/*.hpp")

add_executable(ProjectFPS_BSP ${SOURCES} ${HEADERS})

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
# Compiler warnings and flags
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Configuring Clang warnings")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -Wpedantic
            -Wconversion -Wsign-conversion
            -Wshadow -Wdouble-promotion
            -Wnull-dereference -Wold-style-cast
            -Wnon-virtual-dtor -Woverloaded-virtual
            -Wduplicated-cond -Wlogical-op
            -Wuseless-cast -Wcast-align
            -Werror
    )
endif()

# Enable sanitizers (Debug only)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
endif()

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)

include_directories(glad PUBLIC "/home/csnorbi/Glad/include")
add_library(glad STATIC "src/glad.c")
target_link_libraries(ProjectFPS_BSP PRIVATE glfw glm glad assimp::assimp stdc++fs)


set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/assets/shaders)
set(BUILD_SHADERS_DIR ${CMAKE_BINARY_DIR}/assets/shaders)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS_BSP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} ${BUILD_SHADERS_DIR}
        COMMENT "Copying shaders to build directory"
)

set(MODELS_DIR ${CMAKE_SOURCE_DIR}/assets/models)
set(BUILD_MODELS_DIR ${CMAKE_BINARY_DIR}/assets/models)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS_BSP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${MODELS_DIR} ${BUILD_MODELS_DIR}
        COMMENT "Copying models to build directory"
)