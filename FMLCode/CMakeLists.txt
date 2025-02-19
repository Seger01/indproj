cmake_minimum_required(VERSION 3.15)

# Project name and version
project(indproj VERSION 1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# Include directories
include_directories(${INC_DIR})

# Collect all source files recursively
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the build options for the assimp library
set(ASSIMP_HUNTER_ENABLED OFF CACHE BOOL "Enable Hunter package manager support")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Generation of shared libs")
set(ASSIMP_BUILD_FRAMEWORK OFF CACHE BOOL "Build package as Mac OS X Framework bundle")
set(ASSIMP_DOUBLE_PRECISION OFF CACHE BOOL "All data will be stored as double values")
set(ASSIMP_OPT_BUILD_PACKAGES OFF CACHE BOOL "Generate CPack configuration files and packaging targets")
set(ASSIMP_ANDROID_JNIIOSYSTEM OFF CACHE BOOL "Android JNI IOSystem support")
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp's export functionality")
set(ASSIMP_BUILD_ZLIB OFF CACHE BOOL "Build our own zlib")
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT ON CACHE BOOL "Build Assimp with all exporters enabled")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT ON CACHE BOOL "Build Assimp with all importers enabled")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Supplementary tools for Assimp")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build official samples")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build test suite for Assimp")
set(ASSIMP_COVERALLS OFF CACHE BOOL "Measure test coverage")
set(ASSIMP_INSTALL OFF CACHE BOOL "Install Assimp library")
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat all warnings as errors")
set(ASSIMP_ASAN OFF CACHE BOOL "Enable AddressSanitizer")
set(ASSIMP_UBSAN OFF CACHE BOOL "Enable Undefined Behavior sanitizer")
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "Build documentation using Doxygen")
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "Inject debug postfix in lib names")
set(ASSIMP_IGNORE_GIT_HASH OFF CACHE BOOL "Don't call git to get the hash")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Install MSVC debug files")
set(USE_STATIC_CRT OFF CACHE BOOL "Link against the static MSVC runtime libraries")
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "Build Draco libraries")
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "Build Assimp view tool")

# Include and build external libraries
file(GLOB EXTERNAL_PROJECTS ${EXTERNAL_DIR}/*)
foreach(EXTERNAL_PROJECT ${EXTERNAL_PROJECTS})
    if(EXISTS ${EXTERNAL_PROJECT}/CMakeLists.txt)
        add_subdirectory(${EXTERNAL_PROJECT})
    endif()
endforeach()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link external libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glm assimp freetype)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(COMPILE_COMMANDS_OUTPUT_DIR "${CMAKE_SOURCE_DIR}")
    # file(MAKE_DIRECTORY ${COMPILE_COMMANDS_OUTPUT_DIR})

    add_custom_target(
        CopyCompileCommands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${COMPILE_COMMANDS_OUTPUT_DIR}/compile_commands.json
        # COMMENT "Copying compile_commands.json to ${COMPILE_COMMANDS_OUTPUT_DIR}"
    )
endif()
