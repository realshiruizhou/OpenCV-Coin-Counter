set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
add_executable( DisplayImage l7.cpp)
target_link_libraries( DisplayImage ${OpenCV_LIBS} )