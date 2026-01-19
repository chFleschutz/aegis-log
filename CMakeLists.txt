cmake_minimum_required(VERSION 3.28)

project(aegis-log LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Options ---
option(AEGIS_LOG_BUILD_EXAMPLES "Build examples for Aegis::Log" OFF)
option(AEGIS_LOG_ENABLE_STATIC_ANALYSIS "Enable static analysis tools" ON)

# Force enabling examples in root project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(AEGIS_LOG_BUILD_EXAMPLES ON CACHE BOOL "Force enable examples in root project" FORCE)
endif()

# --- Library ---
add_library(${PROJECT_NAME} INTERFACE)
add_library(Aegis::Log ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# --- Examples ---
if(AEGIS_LOG_BUILD_EXAMPLES)
    # Psuedo target for headers to show in IDEs
    file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    add_custom_target(${PROJECT_NAME}-headers SOURCES ${${PROJECT_NAME}_HEADERS})

    add_subdirectory(examples)
endif()
