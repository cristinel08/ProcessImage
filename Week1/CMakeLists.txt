cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME WEEK1)

set(WEEK1_ROOT ${CMAKE_CURRENT_LIST_DIR})

project(${TARGET_NAME})

file(GLOB TARGET_SOURCES
    src/*.cpp
    inc/*.h
)
find_package(OpenCV REQUIRED)

set(TARGET_INCLUDE_DIRS
    ${WEEK1_ROOT}/inc
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})

add_custom_command(
    TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${WEEK1_ROOT}/imgs/carnavalWheel.jfif
    ${CMAKE_BINARY_DIR}/$<CONFIG>/
)   