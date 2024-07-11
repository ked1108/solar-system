cmake_minimum_required(VERSION 3.20)
project(solar_system)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(AddJsonCpp)

add_subdirectory(src)

add_executable(solar_system main.cpp)
target_link_libraries(solar_system raylib jsoncpp_static system)

add_subdirectory(test)