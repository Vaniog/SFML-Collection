if (WIN32)
    set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)

    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif (WIN32)

add_library(scene Scene.cpp Scene.h
        SceneTools/SceneCollection.h SceneTools/SceneCollection.cpp
        SceneTools/MenuScene.h SceneTools/MenuScene.cpp
        SceneTools/ProjectCover.h SceneTools/ProjectCover.cpp
        SceneTools/Timer.h SceneTools/Timer.cpp)