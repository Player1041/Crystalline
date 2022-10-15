cmake_minimum_required(VERSION 3.16)
project(Crystalline)

set(CMAKE_CXX_STANDARD 11)

add_executable(Crystalline main.cpp)
add_subdirectory(../QuickGame)

target_link_libraries(basic PUBLIC QuickGame)
target_include_directories(basic PUBLIC ../QuickGame/include)
target_link_libraries(Crystalline PUBLIC src)
target_include_directories(Crystalline PUBLIC src/include)

create_pbp_file(
    TARGET Crystalline
    TITLE Crystalline
    BUILD_PRX ON
)
