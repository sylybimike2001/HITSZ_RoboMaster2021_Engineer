cmake_minimum_required(VERSION 3.7)
project(RoboMaster2021_Engineer_Final)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-O3)
set(SOURCE_FILES main.cpp rmconfig/parameter.h
        com/src/datatypes.cpp com/src/rmserial.cpp
        com/src/serial.cpp com/include/serial/impl/unix.h
        com/include/serial/impl/win.h com/src/impl/unix.cpp
        com/src/impl/list_ports/list_ports_linux.cpp
        com/include/serial/serial.h com/include/serial/v8sydint.h
        mineral/include/mineral.h
        mineral/src/init/default_constructor.cpp
        rmconfig/rmconfig.h
        mineral/src/send/send_target.cpp
        mineral/src/get/get_fit_points.cpp
        mineral/run.cpp mineral/src/detect/detect_mineral_yellow.cpp
        mineral/src/tool/sort.cpp mineral/src/get/get_send_data.cpp
        rmconfig/parameter.h
        rmconfig/uvc_v4l2.h
        mineral/src/mor/mor_hang_high_mineral.cpp
        mineral/src/detect/detect_mineral_white.cpp
        mineral/src/tool/gamma_transform.cpp
        mineral/src/mor/mor_dropped_yellow_mineral.cpp
        mineral/src/mor/mor_hang_high_mineral.cpp
        mineral/src/mor/mor_white_mineral.cpp
        com/include/datatypes.h
        com/include/rmserial.h
        com/include/serial/serial.h
        com/include/serial/v8sydint.h
        com/include/serial/impl/unix.h
        com/include/serial/impl/win.h
        com/src/datatypes.cpp
        com/src/rmserial.cpp
        com/src/serial.cpp
        com/src/impl/list_ports/list_ports_linux.cpp
        com/src/impl/unix.cpp mineral/include/mineral.h
        mineral/run.cpp
        mineral/src/detect/detect_mineral_yellow.cpp
        mineral/src/get/get_fit_points.cpp
        mineral/src/get/get_send_data.cpp
        mineral/src/init/default_constructor.cpp
        mineral/src/mor/mor_dropped_yellow_mineral.cpp
        mineral/src/mor/mor_hang_high_mineral.cpp
        mineral/src/mor/mor_white_mineral.cpp
        mineral/src/send/send_target.cpp
        mineral/src/tool/gamma_transform.cpp
        mineral/src/tool/sort.cpp rmconfig/rmconfig.h
        rmconfig/parameter.h
        rmconfig/uvc_v4l2.h
        mineral/src/detect/detect_mineral_white.cpp
        rmconfig/uvc_v4l2.cpp
        mineral/src/get/get_target_points.cpp
        mineral/src/init/init_mineral.cpp com/include/data_manager.h com/src/data_manager.cpp mineral/src/get/get_fit_contours.cpp)

add_executable(RoboMaster2021_Engineer_Final ${SOURCE_FILES})
include_directories(${PROJECT_SOURCE_DIR}/flash/include)
include_directories(${PROJECT_SOURCE_DIR}/mineral/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include/serial)
include_directories(${PROJECT_SOURCE_DIR}/rmconfig)
find_package(OpenCV 4 REQUIRED)

link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(RoboMaster2021_Engineer_Final ${OpenCV_LIBS} -lpthread)







