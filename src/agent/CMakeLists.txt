cmake_minimum_required(VERSION 2.8)

set(SOURCES Dummy.cpp)
find_package(Boost 1.54 COMPONENTS system  thread iostreams REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_library(Agent ${SOURCES})
    target_link_libraries(Agent ${Boost_LIBRARIES})
endif()