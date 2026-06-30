cmake_minimum_required(VERSION 3.10)
project(SusConsoleDialogs)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(SCD_IS_TOP_LEVEL ON)
else()
    set(SCD_IS_TOP_LEVEL OFF)
endif()

if(SCD_IS_TOP_LEVEL)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
endif()

option(SCD_BUILD_EXAMPLES "Build examples executables" ${SCD_IS_TOP_LEVEL})

set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

if(SCD_BUILD_EXAMPLES)
    file(GLOB EXAMPLE_FILES ${EXAMPLES_DIR}/*.cpp)
    foreach(example_file ${EXAMPLE_FILES})
        get_filename_component(example_name ${example_file} NAME_WE)
        add_executable(${example_name} ${example_file})
        target_link_libraries(${example_name} PRIVATE ${PROJECT_NAME})
    endforeach()
endif()
