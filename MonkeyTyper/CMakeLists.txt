cmake_minimum_required(VERSION 3.25)
project(PROJEKT)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(PROJEKT main.cpp
        GeneralSettings.cpp
        GameplayState.cpp
        MenuState.cpp
        StartScreen.cpp
        FontState.cpp
        DifficultyState.cpp
        ScoreBoard.cpp
        AfterGameState.cpp
        ExitMenuState.cpp
        BackupGame.cpp
)
target_link_libraries(PROJEKT fmt sfml-graphics)