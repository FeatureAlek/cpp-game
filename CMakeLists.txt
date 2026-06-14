cmake_minimum_required(VERSION 3.10)
project(2DGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
endif()

# update if needed
include_directories(include include/core include/entities include/managers include/ui)

# directory - what files to compile; ./game to run it
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game ${SRC_FILES})
target_compile_options(game PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
target_compile_definitions(game PRIVATE GAME_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

if(MINGW)
    target_link_options(game PRIVATE -static-libgcc -static-libstdc++)
endif()

if(TARGET SFML::Graphics)
    target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System)
else()
    target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
endif()

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
