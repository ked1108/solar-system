include(AddRaylib)
add_library(system planet.cpp)
target_link_libraries(system raylib)
target_include_directories(system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
