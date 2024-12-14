cmake_minimum_required(VERSION 3.20)

project(orderBook VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(libOrderBook SHARED
    src/orderBook.cpp)

target_include_directories(libOrderBook PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

enable_testing()
add_executable(orderBookTest
    ${PROJECT_SOURCE_DIR}/test/tests.cpp)
target_link_libraries(orderBookTest PRIVATE
    libOrderBook)
add_test(NAME OrderBooKTest COMMAND orderBookTest)
