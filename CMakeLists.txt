cmake_minimum_required(VERSION 3.16)

# Set C++ standard to C++23 for all targets
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Turning this on means that clang can resolve the
# directory of the glfw includes.
# https://github.com/clangd/clangd/issues/770. Also this
# shows that clang searches the build folder for the
# compile commands as well, so don't need to move it to the source
# directory
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set project name to the folder name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME target_name)

project(${target_name} VERSION 1.0 LANGUAGES CXX)

# Find all src files in current directory
# Note: need to add a wildcard per depth! Better way of doing this?
file(GLOB SRC_FILES CONFIGURE_DEPENDS  src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp ./vendor/glad/src/glad.cpp)

message("Source files: \"${SRC_FILES}\"")

# Use the name of the folder as the executable name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME DIRECTORY)
message("Creating executable \"${target_name}\"")

# Note: can now refer to this target in subsequent
# lines.
add_executable(${target_name} ${SRC_FILES})

# Add directories to library files
target_link_directories(${target_name} PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw
${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/lib
)

# Can use this to add in header files that need to be included.
# Doesn't work at the static analysis stage though, even though it will
# still compile.
target_include_directories(${target_name} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/includes
${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt/single_include/entt
${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/includes
${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include
${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(APPLE)
    # Link static library
    target_link_libraries(${target_name} PRIVATE libglfw3.a libassimp.dylib)

    # Link dynamic library into code.
    # target_link_libraries(${DIRECTORY} PRIVATE libglfw3.dylib)

    # Mac specific libraries
    target_link_libraries(${target_name} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework IOKit -framework CoreServices")

    # Copy compile commands from build to source directory
    add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json
    )

    # Add symbolic link to resources directory which contains images, shader files
    set(link_src "${CMAKE_SOURCE_DIR}/resources")
    set(link_dst "${CMAKE_BINARY_DIR}/resources")
    set(link_dst "${CMAKE_BINARY_DIR}/$<CONFIG>/resources")

    add_custom_command(
    TARGET ${target_name}
    POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${link_src} ${link_dst}
    COMMENT "symbolic link ${link_src} => ${link_dst}"
    )
elseif(WIN32)
    target_link_libraries(${target_name} PRIVATE glfw3.lib OpenGL32.lib assimp-vc143-mt.lib) 

    # This currently doesn't work. Need to set the working directory
    # correctly for the resources under project properties, debugging
    # working directory. Basically tells it where to look for file paths.
    # Set to $(ProjectDir)..
    # Update: No longer the case, keeping comment here for learning purposes
    set_target_properties(${project_name} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    configure_file("vendor/assimp/lib/assimp-vc143-mt.dll" "${CMAKE_BINARY_DIR}" COPYONLY)
endif()

target_precompile_headers(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch/pch.h)
