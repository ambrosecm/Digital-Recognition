cmake_minimum_required(VERSION 3.16)

project(main)
set(CMAKE_PREFIX_PATH  "D:/libtorch")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
find_package(Torch REQUIRED)

# opencv的配置
include_directories("D:/op/install/include")
link_directories("D:/op/install/x64/vc16/lib")

add_executable(main main.cpp)
target_link_libraries(main "${TORCH_LIBRARIES}"  "opencv_core420d.lib" "opencv_imgcodecs420d.lib" "opencv_imgproc420d.lib" )
set_property(TARGET main PROPERTY CXX_STANDARD 11)
