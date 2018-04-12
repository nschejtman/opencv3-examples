cmake_minimum_required(VERSION 3.9)
project(opencv_examples)

set(CMAKE_CXX_STANDARD 11)
find_package( OpenCV REQUIRED )

add_executable(opencv_examples main.cpp features.cpp features.h)
target_link_libraries( opencv_examples ${OpenCV_LIBS} )