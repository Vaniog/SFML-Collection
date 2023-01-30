cmake_minimum_required(VERSION 3.20)
project(SFML-Collection LANGUAGES CXX)

if (WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif ()

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)


add_executable(${PROJECT_NAME} main.cpp
        Scene/Scene.cpp
        Scene/SceneTools/SceneCollection.cpp
        Scene/SceneTools/Timer.cpp
        Scene/SceneTools/MenuScene/DirScene.cpp
        Scene/SceneTools/MenuScene/MenuScene.cpp
        Scene/SceneTools/MenuScene/ProjectCover.cpp
        Scene/SceneTools/MenuScene/DescriptionScene.cpp

        Scene/Animation/Interpolator.cpp
        Scene/Animation/IpFuncs.cpp

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

        # Interpolations
        Projects/Interpolations/IpField.cpp Projects/Interpolations/IpField.h
        Projects/Interpolations/IpExample.cpp Projects/Interpolations/IpExample.h
        Projects/Interpolations/IpSlider.cpp Projects/Interpolations/IpSlider.h
        Projects/Interpolations/IpGraph.cpp Projects/Interpolations/IpGraph.h

        )

target_include_directories(${PROJECT_NAME} PRIVATE Scene Scene/SceneTools Scene/Animation)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
