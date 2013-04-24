cmake_minimum_required(VERSION 2.8.4)
project(truerand)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


file(GLOB sources "*.cpp")
file(GLOB headers "*.h")
add_executable(truerand ${sources} ${headers})

source_group("Headers" FILES ${headers})

source_group("Sources" FILES ${sources})

TARGET_LINK_LIBRARIES( truerand Random )