cmake_minimum_required(VERSION 3.20)
project(Console VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#if you are using ui files then uncomment it
#set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(
    ${PROJECT_NAME}     #binary name

    Console.cpp
    main.cpp

    Console.hpp
    
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Widgets
)
