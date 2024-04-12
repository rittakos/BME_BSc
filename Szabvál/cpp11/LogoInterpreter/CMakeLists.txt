cmake_minimum_required(VERSION 3.2)
project(LOGO_INTERPRETER)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)


set(SOURCE_FILES main.cpp header.h window.cpp window.h page.cpp page.h turtle.cpp turtle.h commandBox.cpp commandBox.h drawable.cpp drawable.h point.h command.cpp command.h exception.h rectangle.h renderer.h line.h)
add_executable(SDL_Demo ${SOURCE_FILES})

target_link_libraries(SDL_Demo SDL2main SDL2 )