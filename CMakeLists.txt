cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Raycast3D)

set(Raycast3D ${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp
src/3dEngine.cpp
src/ResourceHolder.cpp
src/Player.cpp
src/map.cpp

headers/3dEngine.h
headers/ResourceHolder.h
headers/Player.h
headers/map.h
)


set(SFML_DIR "external/SFML-2.6.1/lib/cmake/SFML")

target_link_libraries(${PROJECT_NAME} sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
