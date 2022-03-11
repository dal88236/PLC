cmake_minimum_required(VERSION 3.1.0)

project(SocketConnection VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(src 
    ./src/mainWidget.cpp
    ./src/connection.cpp
)

add_library(source STATIC ${src})

include_directories(
    ./include
    ${Qt5Widgets_INCLUDE_DIRS}
)
target_link_libraries(source Qt5::Widgets Qt5::Core)

# add_executable(main ./src/main.cpp) 
# target_link_libraries(main source)

add_executable(test ./src/test.cpp)
target_link_libraries(test source)