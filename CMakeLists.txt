cmake_minimum_required(VERSION 3.17)
project(COMP20003_A2 C)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_C_STANDARD 11)

add_executable(COMP20003_A2
        map.c
        myCLUE.c
        myCLUE.h
        myCSV_Parser.c
        myCSV_Parser.h
        myLinkedList.c
        myLinkedList.h)

target_link_libraries(COMP20003_A2 PRIVATE m)
