cmake_minimum_required(VERSION 3.30)

project(LechemBriocheWM)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(LechemBriocheWM src/main.cpp)

find_package(X11 REQUIRED)
target_include_directories(LechemBriocheWM PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(LechemBriocheWM ${X11_LIBRARIES})
