cmake_minimum_required(VERSION 3.1)

project(wordfreq)

if (CONAN_CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD ${CONAN_CMAKE_CXX_STANDARD})
else()
    set(CMAKE_CXX_STANDARD 17)
endif()
include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

find_package(lyra REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src)
