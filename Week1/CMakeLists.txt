cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME WEEK1)

set(WEEK1_ROOT ${CMAKE_CURRENT_LIST_DIR})

project(${TARGET_NAME})
file(GLOB TARGET_SOURCES
    src/*.cpp
    inc/*.h
)
add_executable(${TARGET_NAME} ${TARGET_SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${IMG_LIB_INC})

target_link_libraries(${TARGET_NAME} ImageProcessing)

add_custom_command(
    TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${WEEK1_ROOT}/imgs/carnavalWheel.jfif
    ${CMAKE_BINARY_DIR}/${TARGET_NAME}/$<CONFIG>/
)   