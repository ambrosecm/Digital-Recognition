cmake_minimum_required(VERSION 3.16)

project(main)

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQIUIRED True) 
set(CMAKE_INCLUDE_CURRENT_DIR ON) 


set(CMAKE_PREFIX_PATH  "D:/libtorch;D:/Qt/5.13.0/msvc2017_64/lib")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) 

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Torch REQUIRED)

include_directories(
    D:/Qt/5.13.0/msvc2017_64/include
    D:/op/install/include
)

link_directories(
    D:/Qt/5.13.0/msvc2017_64/lib
    D:/op/install/x64/vc16/lib
)

aux_source_directory(. SOURCES)
add_executable(main ${SOURCES})
message(${SOURCES})

target_link_libraries(
    main
    "${TORCH_LIBRARIES}" 
    opencv_core420d.lib
    opencv_imgcodecs420d.lib 
    opencv_imgproc420d.lib
    opencv_videoio420d.lib 
    Qt5Cored.lib  
    Qt5Widgetsd.lib 
    Qt5Guid.lib
)

