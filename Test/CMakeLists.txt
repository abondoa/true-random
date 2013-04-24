cmake_minimum_required(VERSION 2.8.4)
project(Test)

find_package(Boost COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


file(GLOB sources "*.cpp")
file(GLOB headers "*.h")
add_library(Test ${sources} ${headers})

source_group("Headers" FILES ${headers})

source_group("Sources" FILES ${sources})

TARGET_LINK_LIBRARIES( Test Random )
