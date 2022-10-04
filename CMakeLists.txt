cmake_minimum_required(VERSION 3.0.0)

set(APP sorting-algorithms-visualizer)

project(${APP})

# all source files
set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/SortAlgoVisualizer.cpp
)

# find sdl2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# link source files and create executable
add_executable(${APP} ${SOURCES})

# header files that are needed for linking
target_include_directories(${APP} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# libraries that are needed for linking
target_link_libraries(${APP}
    ${SDL2_LIBRARIES}
)