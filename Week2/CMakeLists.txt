cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_WEEK2 WEEK2)

set(WEEK2_ROOT ${CMAKE_CURRENT_LIST_DIR})

project(${TARGET_NAME_WEEK2})
file(GLOB TARGET_SOURCES
    src/*.cpp
)
add_executable(${TARGET_NAME_WEEK2} ${TARGET_SOURCES})

target_include_directories(${TARGET_NAME_WEEK2} PRIVATE ${IMG_LIB_INC})

target_link_libraries(${TARGET_NAME_WEEK2} ImageProcessing)

add_custom_command(
    TARGET ${TARGET_NAME_WEEK2} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_ROOT}/imgs/carnavalWheel.jfif
    ${CMAKE_BINARY_DIR}/${TARGET_NAME_WEEK2}/$<CONFIG>/
)   