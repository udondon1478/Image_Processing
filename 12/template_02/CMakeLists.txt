cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(template_02)

find_package(OpenCV 4.5.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (template_02 ${SOURCES})
target_link_libraries (template_02
	PRIVATE ${OpenCV_LIBS}
)