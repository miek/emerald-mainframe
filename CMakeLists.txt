cmake_minimum_required(VERSION 2.8)
project(emerald-mainframe CXX)
enable_testing()

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# For OSX - don't clear RPATH on install
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (WIN32)
    find_library (MMAN mman)
    if(NOT(MMAN))
    message(FATAL_ERROR "please install mman-win32")
    else(NOT(MMAN))
    set (extraLibs  ${extraLibs} ${MMAN})
    endif(NOT(MMAN))
ENDIF (WIN32)

if (NOT CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "-O2")
endif (NOT CMAKE_CXX_FLAGS)

list(APPEND emerald-mainframe_sources 
    main.cpp
    filesource.cpp
    fft.cpp
    histogram.cpp
    mainwindow.cpp
    specanwidget.cpp
)

INCLUDE(FindPkgConfig)

find_package(Qt5Widgets REQUIRED)
pkg_check_modules(FFTW REQUIRED fftw3f)
find_package(Liquid REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${FFTW_INCLUDEDIR}
    ${FFTW_INCLUDE_DIRS}
    ${LIQUID_INCLUDES}
)

link_directories(
    ${FFTW_LIBRARY_DIRS}
)

add_executable(emerald-mainframe ${emerald-mainframe_sources})
qt5_use_modules(emerald-mainframe Widgets Concurrent)

target_link_libraries(emerald-mainframe
    ${QT_LIBRARIES}
    ${FFTW_LIBRARIES}
    ${LIQUID_LIBRARIES}
    ${extraLibs}
)
set(INSTALL_DEFAULT_BINDIR "bin" CACHE STRING "Appended to CMAKE_INSTALL_PREFIX")

install(TARGETS emerald-mainframe RUNTIME DESTINATION ${INSTALL_DEFAULT_BINDIR})

# This only works in cmake >3.1
set_property(TARGET emerald-mainframe PROPERTY CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# Create uninstall target
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
