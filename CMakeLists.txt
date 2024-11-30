cmake_minimum_required(VERSION 3.16)
project(builder)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(builder ${SOURCES})

# Link SFML libraries
target_link_libraries(builder sfml-graphics sfml-window sfml-system)

# Set up assets directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# Copy assets to the build folder (where the executable will run)
add_custom_command(TARGET builder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    $<TARGET_FILE_DIR:builder>/assets
)

install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_PREFIX}/assets)
