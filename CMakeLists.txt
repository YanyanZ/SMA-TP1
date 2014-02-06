cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11")
set(SOURCES src/main.cpp)

add_subdirectory(src)
include_directories(src)

find_package(Boost 1.54 COMPONENTS system thread iostreams REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(simulation ${SOURCES})
    target_link_libraries(simulation ${Boost_LIBRARIES})
    target_link_libraries(simulation Agent)
endif()