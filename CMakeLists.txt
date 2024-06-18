cmake_minimum_required(VERSION 3.9)
project(booksystem)

#Bring the headers, such as Student.h into the project
include_directories(${CMAKE_SOURCE_DIR}/include)
#add_compile_options(-std=c++11 -Wall)
set(CMAKE_BUILD_TYPE "script")
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
set((EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build))
add_executable(project ${SOURCES})
include(CTest)
include(CPack)