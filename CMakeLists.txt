cmake_minimum_required(VERSION 2.8.4)
project(Random)
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.53)

IF(WIN32)
SET(BOOST_ROOT C:/libs/boost_1_51_0)
SET(Boost_INCLUDE_DIR C:/libs/boost_1_51_0)
LINK_DIRECTORIES(C:/libs/boost_1_51_0/stage/lib)
ENDIF(WIN32)

IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF(UNIX)

#add_subdirectory(Dieharder)
add_subdirectory(Random)
add_subdirectory(Test)
add_subdirectory(truerand)
