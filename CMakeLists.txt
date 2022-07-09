cmake_minimum_required(VERSION 2.8)

project(clocktest CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# コンパイルオプション指定
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall -O3 -w")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

# include指定
include_directories(${PROJECT_SOURCE_DIR}/include)

# src
add_executable(clocktest main.cpp)

