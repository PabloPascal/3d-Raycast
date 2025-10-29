cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(Raycast3D)

set(Raycast3D ${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE "Debug")


find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)


add_executable( ${PROJECT_NAME} 
src/main.cpp

src/Core/Game.cpp
src/Core/Game.h
src/Core/Physics.h
src/Core/Physics.cpp 


src/Entity/StaticObject.h
src/Entity/StaticObject.cpp
src/Entity/Thing.h
src/Entity/Enemy.h
src/Entity/Player.cpp
src/Entity/Player.h
src/Entity/Demon.h 
src/Entity/Demon.cpp

src/World/map.cpp
src/World/map.h

src/Resources/ResourceHolder.h
src/Resources/ResourceHolder.cpp 

src/utils/defines.h

src/Renderer/Renderer.h
src/Renderer/Renderer.cpp
src/Renderer/Minimap.h
src/Renderer/raycast.h
src/Renderer/raycast.cpp

src/Ai/AI.cpp 
src/Ai/AI.h

src/utils/thread_pool.hpp
src/utils/MathLib.cpp
src/utils/MathLib.h
src/utils/PathFinder.h
src/utils/PathFinder.cpp

src/Weapons/Weapon.h
src/Weapons/shotgun.cpp 
src/Weapons/shotgun.hpp 
src/Weapons/Pistol.cpp
src/Weapons/Pistol.hpp

src/Systems/keyboardInput.cpp
src/Systems/keyboardInput.h


src/Systems/animationSystem.cpp
src/Systems/animationSystem.hpp

src/Systems/soundSystem.cpp
src/Systems/soundSystem.hpp

src/Entity/EntityManager.hpp
src/Entity/EntityManager.cpp

src/UI/debug_ui.hpp

tests/test.cpp
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
src/Systems
src/UI
)



target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)







