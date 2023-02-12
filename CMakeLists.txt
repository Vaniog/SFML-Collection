cmake_minimum_required(VERSION 3.20)
project(SFML-Collection)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)

    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif (WIN32)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(Scene Scene/SceneTools Scene/Animation)

add_executable(${PROJECT_NAME} main.cpp
        Scene/Scene.cpp
        Scene/SceneTools/SceneCollection.cpp
        Scene/SceneTools/MenuScene/DirScene.cpp
        Scene/SceneTools/MenuScene/MenuScene.cpp
        Scene/SceneTools/MenuScene/ProjectCover.cpp
        Scene/SceneTools/Timer.cpp
        Scene/Animation/Interpolator.cpp

        Projects/GetSceneByName.h

        # Circle Viewer
        Projects/CircleViewer/CircleViewer.h

        # Square Viewer
        Projects/SquareViewer/SquareViewer.cpp Projects/SquareViewer/SquareViewer.h

        # Snake
        Projects/SnakeGame/SnakeScene.cpp Projects/SnakeGame/SnakeScene.h

        # mandlebrotSet
        Projects/Fractals/mandlebrotSet/mandlebrotSet.cpp Projects/Fractals/mandlebrotSet/mandlebrotSet.h

        # abs difference
        Projects/abs_difference/abs_difference.h

        # domain_warping
        Projects/domain_warping/domain_warping.cpp Projects/domain_warping/domain_warping.h

        # blob
        Projects/blob/blob.cpp Projects/blob/blob.h

        # boids
        Projects/boids/boids.cpp Projects/boids/boids.h

        Scene/Animation/InterpolFunctions.h Scene/SceneTools/MenuScene/DescriptionScene.cpp Scene/SceneTools/MenuScene/DescriptionScene.h
        )


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)