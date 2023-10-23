cmake_minimum_required(VERSION 3.26)
project(DLLTaskManager)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DLLTaskManager
        DLL.cpp
        DLL.hpp
        DNode.cpp
        DNode.hpp
        MainDLL.cpp
        Task.cpp
        Task.hpp
        TaskManager-1.cpp
        TaskManager.hpp
        TaskManager.cpp)
