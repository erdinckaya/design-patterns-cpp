cmake_minimum_required(VERSION 3.15)
project(design-patterns-cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(singleton 01_singleton.cpp)
add_executable(factory 02_factory.cpp)
add_executable(abstract_factory 03_abstract_factory.cpp)
add_executable(adapter 04_adapter.cpp)
add_executable(observer 05_observer.cpp)
