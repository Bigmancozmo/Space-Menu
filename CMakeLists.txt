cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(SpaceMenu VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    # Add your cpp files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

ADD_CUSTOM_TARGET(clear_cache ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND geode.exe project clear-cache)

#message(STATUS "fixing fonts")
# file(REMOVE "${PROJECT_SOURCE_DIR}/out/build/Geode Build/bigmancozmo.spacemenu.geode")

#file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/out/build/Geode Build/BFDICOOL")

#file(COPY "${PROJECT_SOURCE_DIR}/out/build/Geode Build/bigmancozmo.spacemenu.geode" DESTINATION "${PROJECT_SOURCE_DIR}/out/build/Geode Build/BFDICOOL/")

#file(ARCHIVE_EXTRACT INPUT "${PROJECT_SOURCE_DIR}/out/build/Geode Build/BFDICOOL/bigmancozmo.spacemenu.geode" DESTINATION "${PROJECT_SOURCE_DIR}/out/build/Geode Build/BFDICOOL/")
#file(REMOVE "${PROJECT_SOURCE_DIR}/out/build/Geode Build/BFDICOOL/bigmancozmo.spacemenu.geode")

#message(STATUS "fixed!")

setup_geode_mod(${PROJECT_NAME})

