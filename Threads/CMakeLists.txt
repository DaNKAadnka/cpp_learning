cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(ThreadsLearning)

add_executable(threads_init  src/threads_init.cpp)
add_executable(threads_join  src/threads_joins.cpp)
add_executable(threads_mutex src/threads_mutex.cpp)
