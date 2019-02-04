cmake_minimum_required(VERSION 2.8)

project("ray_tracer")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)

set(ASSIMP_LIBRARY_DIR "lib/assimp/code")
set(ASSIMP_INCLUDE_DIR "lib/assimp/include")
include_directories(${ASSIMP_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/build/lib/assimp/include)
link_directories(${ASSIMP_LIBRARY_DIR})

file(GLOB sources src/*.cpp)
add_executable(ray_tracer ${sources})
