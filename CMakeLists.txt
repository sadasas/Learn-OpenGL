cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "E:/c++/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Learn VERSION 1.0)

configure_file(config.h.in config.h)

add_executable(${PROJECT_NAME}  src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/vcpkg_installed/x64-windows/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/vcpkg_installed/x64-windows)


#opengl lib 
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32)
  