cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)
project(Knn_opt)

file(GLOB_RECURSE Knn_opt_SOURCES src/*.cpp)
file(GLOB_RECURSE Knn_opt_HEADERS src/*.h*)

set(Knn_opt_INCLUDE_DIRS "")
foreach (_headerFile ${Knn_opt_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND Knn_opt_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Knn_opt_INCLUDE_DIRS)

include_directories(${Knn_opt_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})
add_executable (Knn_opt_exec ${Knn_opt_SOURCES})
