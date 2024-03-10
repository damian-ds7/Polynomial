cmake_minimum_required(VERSION 3.27)
project(polynomial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES polynomial.cpp polynomial.h)

add_executable(polynomial main.cpp ${PROJECT_SOURCES})
