cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

set(SOURCES Server.cpp)
find_package(Boost 1.54 COMPONENTS system thread iostreams REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(server ${SOURCES})
    target_link_libraries(server ${Boost_LIBRARIES})
endif()