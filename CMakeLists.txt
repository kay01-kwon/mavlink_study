cmake_minimum_required(VERSION 3.12)
project(mavlink_example)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(mavlink_read_data_impl
    src/mavlink_read_data_impl.cpp
    include/comm/read_data_impl.cpp
    include/comm/serial_port.cpp
)

target_link_libraries(mavlink_read_data_impl
PRIVATE  pthread
)