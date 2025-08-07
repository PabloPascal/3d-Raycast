cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(Raycast3D)

set(Raycast3D ${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")


find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)


add_executable(${PROJECT_NAME} 
src/main.cpp

src/Core/Engine.cpp
src/Core/Engine.h
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
src/utils/defines.h

src/Renderer/Renderer.h
src/Renderer/Renderer.cpp
src/Renderer/Minimap.h


src/Ai/AI.cpp 
src/Ai/AI.h

src/utils/MathLib.cpp
src/utils/MathLib.h
src/utils/PathFinder.h
src/utils/PathFinder.cpp

src/Weapons/Weapon.h
src/Weapons/Weapon.cpp

src/InputSystem/keyboardInput.cpp
src/InputSystem/keyboardInput.h

)


include_directories(
src/Ai
src/Core 
src/Entity 
src/Renderer 
src/Resources 
src/utils
src/World 
src/Weapons
src/InputSystem
)



target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)







