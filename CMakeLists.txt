cmake_minimum_required(VERSION 3.20)
enable_testing()
project(constexpr-raytracing)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS       OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(tools)
