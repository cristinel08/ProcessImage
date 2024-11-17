cmake_minimum_required(VERSION 3.20)

set(IMAGE_PROCESS_PATH ${CMAKE_CURRENT_LIST_DIR})

project(ImageProcessing)

set(IMG_LIB_PROCESS_NAME ${PROJECT_NAME})

find_package(OpenCV REQUIRED)

file(GLOB SRC_FILES
    src/*.cpp
    inc/*.h
)
set(IMG_LIB_INC
    ${IMAGE_PROCESS_PATH}/inc/
    ${OpenCV_INCLUDE_DIRS}
)

add_library(${IMG_LIB_PROCESS_NAME} ${SRC_FILES})

target_include_directories(${IMG_LIB_PROCESS_NAME} PUBLIC ${IMG_LIB_INC})

target_link_libraries(${IMG_LIB_PROCESS_NAME} ${OpenCV_LIBS})

