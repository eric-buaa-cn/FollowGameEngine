cmake_minimum_required(VERSION 3.0.0)
project(FollowGameEngine VERSION 0.1.0)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -msse2")

find_package(spdlog CONFIG REQUIRED)

include(CTest)
enable_testing()

file(GLOB COMMON_SRC_FILES ${PROJECT_SOURCE_DIR}/common/src/*.cpp)
add_library(common ${COMMON_SRC_FILES})
target_include_directories(common
    PUBLIC ${PROJECT_SOURCE_DIR}/common
)
target_link_libraries(common
    PUBLIC spdlog::spdlog_header_only
)

add_executable(FollowGameEngine main.cpp)
target_link_libraries(FollowGameEngine PRIVATE
    common
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
