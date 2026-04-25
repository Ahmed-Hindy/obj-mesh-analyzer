cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(
    obj_mesh_analyzer
    VERSION 0.1.0
    DESCRIPTION "A C++20 learning project that analyzes Wavefront OBJ mesh files from the console."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(FMT_DOC OFF CACHE BOOL "" FORCE)
set(FMT_TEST OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(TINYOBJLOADER_BUILD_TEST_LOADER OFF CACHE BOOL "" FORCE)
set(TINYOBJLOADER_BUILD_OBJ_STICHER OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    fmt
    URL https://github.com/fmtlib/fmt/archive/refs/tags/12.1.0.zip
    URL_HASH SHA256=e6a2b43c6ec4779fb53b15b705f7c20b4eb9d5ae35784d610ac6daec30737019
)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.zip
    URL_HASH SHA256=3aa4347b8f13cba882df1c7b61a6ca910c75a875c56ec3d75d7dc9ae8eac34df
)

FetchContent_Declare(
    tinyobjloader
    URL https://github.com/tinyobjloader/tinyobjloader/archive/refs/tags/v2.0.0rc13.zip
    URL_HASH SHA256=ed8d10e23a40c392a9d2db60b48428c88d0617949208e5c7514536fe5cea2414
)

FetchContent_MakeAvailable(fmt glm tinyobjloader)

add_executable(mesh_analyzer app/main.cpp)

target_link_libraries(mesh_analyzer
    PRIVATE
        fmt::fmt
        glm::glm
        tinyobjloader
)

add_custom_command(
    TARGET mesh_analyzer
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:mesh_analyzer>/assets
)
