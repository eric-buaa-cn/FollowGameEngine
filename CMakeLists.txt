cmake_minimum_required(VERSION 3.16)
project(FollowGameEngine VERSION 0.1.0)

add_definitions(-DHZ_ENABLE_ASSERTS -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM)
add_definitions(-DGLFW_INCLUDE_NONE)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -msse2")

find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

include(CTest)
enable_testing()

# common library begin
file(GLOB COMMON_SRC_FILES ${PROJECT_SOURCE_DIR}/common/*.cpp)
add_library(common ${COMMON_SRC_FILES})
target_include_directories(common
    PUBLIC ${PROJECT_SOURCE_DIR}/common
)
target_link_libraries(common PUBLIC
    spdlog::spdlog_header_only
)
# common library end

# hazel library begin
file(GLOB HAZEL_SRC_FILES
    ${PROJECT_SOURCE_DIR}/hazel/*.cpp
    ${PROJECT_SOURCE_DIR}/hazel/imgui/*.cpp
    ${PROJECT_SOURCE_DIR}/hazel/vendor/stb_image/*.cpp
    ${PROJECT_SOURCE_DIR}/hazel/Renderer/*.cpp
)
add_library(hazel ${HAZEL_SRC_FILES})
target_include_directories(hazel
    PUBLIC ${PROJECT_SOURCE_DIR}/hazel
    PUBLIC ${PROJECT_SOURCE_DIR}/hazel/Renderer
    PUBLIC ${PROJECT_SOURCE_DIR}/hazel/imgui
    PUBLIC ${PROJECT_SOURCE_DIR}/hazel/vendor/stb_image
)
target_link_libraries(hazel PUBLIC
    glad::glad
    glfw
    common
    imgui::imgui
    glm::glm
)
target_precompile_headers(hazel PRIVATE ${PROJECT_SOURCE_DIR}/hazel/pch.h)
# hazel library end

add_executable(playground ${PROJECT_SOURCE_DIR}/playground/main.cpp)
target_include_directories(playground PRIVATE
    ${PROJECT_SOURCE_DIR}/playground
)
target_link_libraries(playground PRIVATE
    hazel
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
