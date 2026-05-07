cmake_minimum_required(VERSION 3.16)

project(arm_neon_array_processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(ENABLE_GUI "Build the Qt Widgets GUI application" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(COMMON_SOURCES
    src/scalar.cpp
    src/scalar.hpp
    src/neon.cpp
    src/neon.hpp
    src/benchmark.cpp
    src/benchmark.hpp
)

add_executable(arm_neon_cli
    src/cli_main.cpp
    ${COMMON_SOURCES}
)

target_include_directories(arm_neon_cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(arm_neon_cli PRIVATE -O3)
endif()

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" PROJECT_CPU)
if(PROJECT_CPU MATCHES "^(arm|armv7|armv8|aarch64|arm64)")
    target_compile_definitions(arm_neon_cli PRIVATE ARM_NEON_TARGET=1)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        if(PROJECT_CPU MATCHES "^(aarch64|arm64)")
            target_compile_options(arm_neon_cli PRIVATE -march=armv8-a)
        else()
            target_compile_options(arm_neon_cli PRIVATE -mfpu=neon -march=armv7-a)
        endif()
    endif()
endif()

if(ENABLE_GUI)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
    )

    find_package(Qt6 COMPONENTS Widgets QUIET)
    if(Qt6_FOUND)
        set(QT_PACKAGE Qt6)
    else()
        find_package(Qt5 REQUIRED COMPONENTS Widgets)
        set(QT_PACKAGE Qt5)
    endif()

    add_executable(arm_neon_gui
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.hpp
        src/gui/mainwindow.ui
        ${COMMON_SOURCES}
    )

    target_include_directories(arm_neon_gui PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_link_libraries(arm_neon_gui PRIVATE ${QT_PACKAGE}::Widgets)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(arm_neon_gui PRIVATE -O3)
    endif()

    if(PROJECT_CPU MATCHES "^(arm|armv7|armv8|aarch64|arm64)")
        target_compile_definitions(arm_neon_gui PRIVATE ARM_NEON_TARGET=1)

        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            if(PROJECT_CPU MATCHES "^(aarch64|arm64)")
                target_compile_options(arm_neon_gui PRIVATE -march=armv8-a)
            else()
                target_compile_options(arm_neon_gui PRIVATE -mfpu=neon -march=armv7-a)
            endif()
        endif()
    endif()
endif()
