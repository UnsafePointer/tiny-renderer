cmake_minimum_required(VERSION 3.10.2)
project(cpp-template)

add_subdirectory(glad)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE CPP_TEMPLATE_SOURCES src/*.cpp)
include_directories(include)
add_executable(cpp-template ${CPP_TEMPLATE_SOURCES})
set_property(TARGET cpp-template PROPERTY CXX_STANDARD 17)
target_link_libraries(cpp-template ${SDL2_LIBRARIES})
target_link_libraries(cpp-template glad)
target_compile_options(cpp-template PRIVATE -Werror -Wall -Wextra)
