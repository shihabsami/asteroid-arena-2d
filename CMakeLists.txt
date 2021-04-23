cmake_minimum_required(VERSION 3.16)
project(Asteroid_Arena_2D)
set(CMAKE_CXX_STANDARD 14)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

include_directories("/usr/include/GL")
set(SOURCE_FILES main/main.cpp
        main/config.cpp main/config.h
        main/game_window.cpp main/game_window.h
        main/game_init.cpp main/game_init.h
        utilities/game_manager.cpp utilities/game_manager.h
        utilities/game_ui.cpp utilities/game_ui.h
        objects/game_object.cpp objects/game_object.h
        objects/game_arena.cpp objects/game_arena.h
        objects/wall.cpp objects/wall.h
        objects/spaceship.cpp objects/spaceship.h
        objects/asteroid.cpp objects/asteroid.h
        objects/bullet.h
        objects/blackhole.cpp objects/blackhole.h
        objects/particle.cpp objects/particle.h
        utilities/particle_system.cpp utilities/particle_system.h
        utilities/object_register.cpp utilities/object_register.h
        utilities/collision_handler.cpp utilities/collision_handler.h
        utilities/input_handler.cpp utilities/input_handler.h
        math/point2d.cpp math/point2d.h
        math/vector2d.cpp math/vector2d.h
        math/game_math.h
        )

add_executable(Asteroid_Arena_2D ${SOURCE_FILES})
target_link_libraries(Asteroid_Arena_2D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
