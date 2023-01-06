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

include_directories(Scene Scene/SceneTools)

add_executable(${PROJECT_NAME} main.cpp
        Projects/GetSceneByName.h
        Projects/CircleViewer/CircleViewer.h Projects/CircleViewer/CircleViewer.cpp
        Projects/SquareViewer/SquareViewer.h Projects/SquareViewer/SquareViewer.cpp
        )


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
add_subdirectory(Scene)
target_link_libraries(${PROJECT_NAME} scene)
add_subdirectory(Projects)
target_link_libraries(${PROJECT_NAME} projects)