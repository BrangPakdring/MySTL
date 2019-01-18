cmake_minimum_required(VERSION 3.13)
project(MySTL)

set(CMAKE_CXX_STANDARD 17)

add_executable(MySTL main.cpp vector.h mystl_config.h memory.h mystl_allocator.h mystl_construct.h type_traits.h mystl_iterator.h list.h mystl_alloc.h)