## Use the variable PROJECT_NAME for changing the target name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
set( PROJECT_NAME ${ProjectId} )

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
include_directories(/usr/local/opt/glew/include)
include_directories(/opt/homebrew/opt/glew/include)
include_directories(/usr/local/opt/glfw/include)
include_directories(/opt/homebrew/opt/glfw/include)
link_directories(/usr/local/lib)
link_directories(/opt/homebrew/lib)

## add imgui as a library
add_library(imgui STATIC
  src/imgui/imgui.cpp
  src/imgui/imgui_demo.cpp
  src/imgui/imgui_draw.cpp
  src/imgui/imgui_widgets.cpp
  src/imgui/imgui_impl_glfw.cpp
  src/imgui/imgui_impl_opengl3.cpp
)

add_subdirectory(lib/rapidyaml ryml)

## Define libraries
add_library(${PROJECT_NAME}_lib STATIC
 src/Rule.cpp
 src/LTurtle.cpp
 src/LSystemBase.cpp
 src/LSystemOption.cpp
)
target_include_directories(${PROJECT_NAME}_lib PUBLIC 
  include
)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ryml)

## Define the executable
set(SRCS 
  src/main.cpp
)
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC
  include
)
target_link_libraries(${PROJECT_NAME} imgui glfw ${OPENGL_gl_LIBRARY} glew ${PROJECT_NAME}_lib)
