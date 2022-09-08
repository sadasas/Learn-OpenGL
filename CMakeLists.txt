cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "E:/c++/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Learn VERSION 1.0)

add_executable(${PROJECT_NAME}  src/main.cpp)



#opengl lib 
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32)
  