cmake_minimum_required (VERSION 3.5)
project(Knn_opt)

file(GLOB_RECURSE Knn_opt_SOURCES src/*.cpp)
file(GLOB_RECURSE Knn_opt_HEADERS src/*.hpp)

set(Knn_opt_INCLUDE_DIRS "")
foreach (_headerFile ${Knn_opt_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND Knn_opt_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Knn_opt_INCLUDE_DIRS)

include_directories(${Knn_opt_INCLUDE_DIRS})
add_executable (Knn_opt_exec ${Knn_opt_SOURCES})