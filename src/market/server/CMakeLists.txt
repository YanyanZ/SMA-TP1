cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11")

set(SOURCES connection.cpp mime_types.cpp posix_main.cpp
  reply.cpp request_handler.cpp request_parser.cpp server.cpp
  init_server_stocks.cpp)

find_package(Boost 1.54 COMPONENTS filesystem system serialization thread iostreams date_time chrono regex REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(server ${SOURCES})
    target_link_libraries(server ${Boost_LIBRARIES})
endif()