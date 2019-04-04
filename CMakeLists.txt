cmake_minimum_required(VERSION 3.9)

project("ray_tracer")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /bigobj")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -O3 -std=c++14 -lpthread")
endif()

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
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--stack,8388608") #set stack size to 8mb
endif()
add_subdirectory("lib/assimp")

find_package(OpenMP REQUIRED)
if(NOT OPENMP_FOUND)
    message(FATAL_ERROR "Please install OpenMP")
endif()

file(GLOB sources src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${sources})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
