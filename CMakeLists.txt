cmake_minimum_required(VERSION 3.15)

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
# find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::omniverse-physx-sdk::sdk)

# Optional: import the defined target to copy over the GPU acceleration libraries (3rd party provided by NVIDIA)
# if(TARGET unofficial::omniverse-physx-sdk::gpu-library)
#     if(UNIX)
#         # Add rpath setting to find .so libraries on unix based systems
#         set_target_properties(${PROJECT_NAME} PROPERTIES
#             BUILD_WITH_INSTALL_RPATH TRUE
#             INSTALL_RPATH "$ORIGIN"
#         )
#     endif()
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                     $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-library>
#                     $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#     if(WIN32)
#         add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                     $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-device-library>
#                     $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#     endif()
# else()
#     message(WARNING "GPU acceleration library target not defined - GPU acceleration will NOT be available!")
# endif()