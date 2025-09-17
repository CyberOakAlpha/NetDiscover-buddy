cmake_minimum_required(VERSION 3.16)

project(NetDiscoverBuddy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

qt6_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)

set(HEADERS
    src/mainwindow.h
)

qt6_add_executable(NetDiscoverBuddy ${SOURCES} ${HEADERS})

target_link_libraries(NetDiscoverBuddy
    PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

# Set the output directory
set_target_properties(NetDiscoverBuddy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)