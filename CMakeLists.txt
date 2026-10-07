cmake_minimum_required(VERSION 3.10.0)
project(watermark VERSION 0.1.0 LANGUAGES C CXX)

add_compile_options(-Wall -Wextra)

add_library(bmp_watermark src/bmp_image.cpp src/watermark.cpp)
target_include_directories(bmp_watermark PUBLIC include)

add_executable(watermark src/main.cpp)
target_link_libraries(watermark PRIVATE bmp_watermark)