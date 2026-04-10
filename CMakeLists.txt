cmake_minimum_required(VERSION 3.10)
project(2DGame)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# update if needed
include_directories(include)

# directory - what files to compile; ./game to run it
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game ${SRC_FILES})

target_link_libraries(game sfml-graphics sfml-window sfml-system)

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)