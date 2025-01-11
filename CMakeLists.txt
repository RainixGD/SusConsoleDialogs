cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(SusConsoleDialogs)

set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/examples)

if(EXISTS "${CMAKE_SOURCE_DIR}/external/"${SusConsleDialogs})
    set(BUILD_EXAMPLES OFF CACHE BOOL "Disable example compilation if the library is a submodule")
else()
    set(BUILD_EXAMPLES ON CACHE BOOL "Enable example compilation")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

if(BUILD_EXAMPLES)
    file(GLOB EXAMPLE_FILES ${EXAMPLES_DIR}/*.cpp)
    foreach(example_file ${EXAMPLE_FILES})
        get_filename_component(example_name ${example_file} NAME_WE)
        add_executable(${example_name} ${example_file})
        #include_directories(${CMAKE_SOURCE_DIR}/include)
    endforeach()
endif()