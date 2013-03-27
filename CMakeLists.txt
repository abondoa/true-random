cmake_minimum_required(VERSION 2.8.4)
project(Random)
find_package(Boost 1.51)

SET(BOOST_ROOT C:/libs/boost_1_51_0)
SET(Boost_INCLUDE_DIR C:/libs/boost_1_51_0)
LINK_DIRECTORIES(C:/libs/boost_1_51_0/stage/lib)

#add_subdirectory(Dieharder)
add_subdirectory(Random)
add_subdirectory(Test)
add_subdirectory(truerand)
