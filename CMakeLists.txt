cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Raycast3D)

set(Raycast3D ${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp

src/Core/3dEngine.cpp
src/Core/3dEngine.h

src/Core/Physics.h
src/Core/Physics.cpp 


src/Entity/StaticObject.h
src/Entity/StaticObject.cpp
src/Entity/Thing.h
src/Entity/Enemy.h
src/Entity/Enemy.cpp
src/Entity/Player.cpp
src/Entity/Player.h

src/World/map.cpp
src/World/map.h

src/Resources/ResourceHolder.h


src/Renderer/Renderer.h
src/Renderer/Renderer.cpp

src/Ai/AI.cpp 
src/Ai/AI.h

src/utils/MathLib.cpp
src/utils/MathLib.h

src/utils/PathFinder.h
src/utils/PathFinder.cpp
)


include_directories(
src/Ai
src/Core 
src/Entity 
src/Renderer 
src/Resources 
src/utils
src/World 
)

set(SFML_DIR "external/SFML-2.6.1/lib/cmake/SFML")

target_link_libraries(${PROJECT_NAME} sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
