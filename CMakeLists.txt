cmake_minimum_required(VERSION 3.21)
project(OperatingSystemsAssignment2)

set(CMAKE_CXX_STANDARD 11)

add_executable(OperatingSystemsAssignment2 main.cpp populatetree.h populatetree.cpp countwords.cpp countwords.h EXEC_STATUS.cpp EXEC_STATUS.h dictentry.cpp dictentry.h threadHelper.cpp threadHelper.h)
