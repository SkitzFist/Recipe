cmake_minimum_required(VERSION 3.0)
project(recept CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(sqlite3 URL "https://www.sqlite.org/2023/sqlite-amalgamation-3410100.zip")
if (NOT sqlite3_POPULATED)
  FetchContent_Populate(sqlite3)
endif()

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") 

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES} ${sqlite3_SOURCE_DIR}/sqlite3.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE} ${sqlite3_SOURCE_DIR})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib stdc++fs)

  #compile with: cmake .. -G "MinGW Makefiles" %*  -DCMAKE_C_COMPILER=<gcc> -DCMAKE_CXX_COMPILER=<g++>