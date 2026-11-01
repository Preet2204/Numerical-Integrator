cmake_minimum_required(VERSION 3.14)
project(NumericalIntegrator C CXX)

# Suppress FetchContent timestamp warnings
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# 1. Fetch and build Raylib 5.5
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
)
FetchContent_MakeAvailable(raylib)

# 2. Fetch Raygui
FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(raygui)

# Add your executable (removed main.cpp since integrator.cpp handles main)
add_executable(integrator 
    integrator.cpp 
    tinyexpr.c
)

# Link Raylib
target_link_libraries(integrator PRIVATE raylib)

# Include Raygui headers
target_include_directories(integrator PRIVATE ${raygui_SOURCE_DIR}/src)

# Copy resources folder to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
