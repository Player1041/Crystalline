cmake_minimum_required(VERSION 3.16)
project(Crystalline)

set(CMAKE_CXX_STANDARD 17)

add_executable(Crystalline main.cpp)
add_subdirectory(./QuickGame)

target_link_libraries(Crystalline PUBLIC QuickGame)
target_include_directories(Crystalline PUBLIC ./QuickGame/include)
target_include_directories(Crystalline PUBLIC src/include)

create_pbp_file(
    TARGET Crystalline
    TITLE Crystalline
    ICON_PATH "build/sprites/ICON0.png"
    BUILD_PRX ON
)
