cmake_minimum_required(VERSION 3.13)
project(MySTL)

set(CMAKE_CXX_STANDARD 17)

add_executable(MySTL main.cpp vector.h mystl_config.h memory.h mystl_allocator.h mystl_construct.h type_traits.h mystl_iterator.h list.h mystl_alloc.h algorithm.h iterator.h mystl_function.h functional.h array.h mystl_uninitialized.h deque.h mystl_algobase.h queue.h forward_list.h mystl_heap.h mystl_tree.h)
add_executable(DebugList list.h main.cpp)
add_executable(DebugFunctional functional.h main.cpp)
add_executable(DebugInitializerList main.cpp)
add_executable(DebugDeque stack.h deque.h queue.h main.cpp)
add_executable(DebugVector vector.h main.cpp)


add_compile_options(" -lthread")
set(CMAKE_CXX_FLAGS -pthread)