cmake_minimum_required(VERSION 3.17)
project(Crystalline)

set(CMAKE_CXX_STANDARD 11)

add_executable(Crystalline main.cpp)

target_link_libraries(Crystalline PUBLIC src)
target_include_directories(Crystalline PUBLIC src/include)

create_pbp_file(
    TARGET Crystalline
    TITLE Crystalline
    BUILD_PRX ON
)