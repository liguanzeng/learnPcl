cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(pcd_concatenate)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINATIONS})

add_executable(pcd_concatenate cloud_concatenate.cpp)
target_link_libraries(pcd_concatenate ${PCL_LIBRARIES})