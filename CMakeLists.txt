cmake_minimum_required (VERSION 3.5)
unset(CMAKE_CXX_FLAGS CACHE)

project(Knn_opt)

#add_definitions(-DENABLE_OPENMP=${ENABLE_OPENMP})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")

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

#find_package(OpenMP)
#if("${ENABLE_OPENMP}" EQUAL 1)
#	message("OPENMP IS ENABLED")
#	if(OPENMP_FOUND)
#		message("OPENMP FOUND")
#     	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#     	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
#     	include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})
#		link_directories(${OpenMP_LIBRARY_DIRS})
#		target_link_libraries(Knn_opt_exec ${OpenMP_CXX_LIBRARIES})
#  	endif()
#endif()

message("${CMAKE_CXX_FLAGS}")
