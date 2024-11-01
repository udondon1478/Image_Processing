cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(median)

find_package(OpenCV 4.5.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (median ${SOURCES})
target_link_libraries (median
	PRIVATE ${OpenCV_LIBS}
)