cmake_minimum_required(VERSION 2.8)

set(SOURCES client.cpp)
find_package(Boost 1.54 COMPONENTS filesystem system serialization thread iostreams date_time chrono regex REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(client ${SOURCES})
    target_link_libraries(client ${Boost_LIBRARIES})
endif()