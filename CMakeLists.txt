cmake_minimum_required(VERSION 3.9) # CMake install : https://cmake.org/download/
project(PWMcalculator VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Program Files/Qt/6.8.0/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
find_package(Vulkan REQUIRED)

# add_compile_options(-std=c++11 -Wall)
set(CMAKE_BUILD_TYPE)
#set(CMAKE_CXX_FLAGS "-mwindows")

# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Can manually add the sources using the set command as follows:
# set(SOURCES src/mainapp.cpp src/Student.cpp)
# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

# set((EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build))
add_executable(${PROJECT_NAME}
    #WIN32 # If you need a terminal for debug, please comment this statement
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets) # Qt6 Shared Library

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${PROJECT_NAME}/lib
    RUNTIME DESTINATION ${PROJECT_NAME}/bin
    PUBLIC_HEADER DESTINATION ${PROJECT_NAME}/include
    
)

include(InstallRequiredSystemLibraries)
set(CPACK_SOURCE_GENERATOR "NSIS")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/static\\\\calculator.ico")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
include(CPack)
