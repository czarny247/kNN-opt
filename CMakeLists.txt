cmake_minimum_required (VERSION 3.5)
unset(CMAKE_CXX_FLAGS CACHE)

project(Knn_opt)

message("${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")
endif()

file(GLOB_RECURSE Knn_opt_SOURCES src/*.cpp)
file(GLOB_RECURSE Knn_opt_HEADERS src/*.h*)

find_package(Boost REQUIRED COMPONENTS system chrono)

set(Knn_opt_INCLUDE_DIRS "")
foreach (_headerFile ${Knn_opt_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND Knn_opt_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Knn_opt_INCLUDE_DIRS)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${Knn_opt_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

add_executable (Knn_opt_exec ${Knn_opt_SOURCES})
target_link_libraries(Knn_opt_exec ${Boost_LIBRARIES})

message("${CMAKE_CXX_FLAGS}")