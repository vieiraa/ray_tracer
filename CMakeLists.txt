cmake_minimum_required(VERSION 2.8)

project("ray_tracer")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -O3 -std=c++14" )

include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)

set(ASSIMP_LIBRARY_DIR "lib/assimp/code")
set(ASSIMP_INCLUDE_DIR "lib/assimp/include")

include_directories(${ASSIMP_INCLUDE_DIR})
SET(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
SET(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
if(CMAKE_COMPILER_IS_MINGW)
    message(STATUS "SMD importer disabled")
    #add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)
    add_definitions(-DASSIMP_BUILD_NO_SMD_IMPORTER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj" )
endif()
add_subdirectory("lib/assimp")

file(GLOB sources src/*.cpp)
add_executable(ray_tracer ${sources})
target_link_libraries(ray_tracer PUBLIC assimp)
