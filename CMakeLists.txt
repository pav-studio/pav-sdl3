cmake_minimum_required(VERSION 3.16)
project(RoguePong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)
find_package(sdl3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(RoguePong src/main.cpp
    src/lib/asset_manager/asset_manager.cpp
    src/screens/game_screen.h
    src/lib/font/font.cpp
    src/lib/font_manager/font_manager.h
    src/lib/font_manager/font_manager.cpp
    src/lib/sprite/sprite.h
    src/lib/camera/camera.h
    src/glad.c
    src/lib/renderer/renderer2d.h
    src/lib/renderer/renderer2d.cpp)

target_link_libraries(RoguePong
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    OpenGL::GL
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_BINARY_DIR}/assets
)

add_custom_command(TARGET RoguePong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/SDL3.dll"
        $<TARGET_FILE_DIR:RoguePong>
)

add_custom_command(TARGET RoguePong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/SDL3_image.dll"
        $<TARGET_FILE_DIR:RoguePong>
)

add_custom_command(TARGET RoguePong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/SDL3_ttf.dll"
        $<TARGET_FILE_DIR:RoguePong>
)

include_directories(src)
include_directories(src/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_dependencies(RoguePong copy_assets)