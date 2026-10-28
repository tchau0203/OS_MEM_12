cmake_minimum_required(VERSION 3.14)
project(SegmentMMU VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
    src/segment_table.cpp
    src/mmu.cpp
)

# Main executable
add_executable(segment_mmu
    src/main.cpp
    ${SOURCE_FILES}
)

# Test executable
add_executable(test_mmu
    tests/test_main.cpp
    ${SOURCE_FILES}
)
