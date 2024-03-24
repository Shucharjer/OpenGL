cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang.exe)
set(CMAKE_CXX_COMPILER clang++.exe)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_DEFAULT_TRIPLET x64-windows)
set(VCPKG_DEFAULT_HOST_TRIPLET x64-windows)

project(OpenGL)

include_directories(./include)

file (GLOB SRC_FILES
"${PROJECT_SOURCE_DIR}/source/*.cpp"
"${PROJECT_SOURCE_DIR}/source/*/*.cpp"
"${PROJECT_SOURCE_DIR}/source/*/*/*.cpp"
"${PROJECT_SOURCE_DIR}/source/*/*/*/*.cpp"
)

add_executable(
    ${PROJECT_NAME} ${SRC_FILES}
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
find_package(Freetype REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)

