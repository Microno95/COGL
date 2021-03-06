cmake_minimum_required(VERSION 3.14)
project(libcogl VERSION 1.0.0 LANGUAGES CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

option(COGL_BUILD_EXAMPLES "Build the cogl example programs" ON)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

if(MSVC)
    add_compile_options("/W3" "$<$<CONFIG:RELEASE>:/O3>")
else()
    add_compile_options("-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()

# Include OpenMP libraries
message(STATUS "Checking OpenMP")
find_package(OpenMP)

# Include OpenGL libraries
find_package(OpenGL REQUIRED)

# Add glfw libraries
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})

# Add glm libraries
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory(${GLM_DIR})

# Add glad libraries
set(GLAD_DIR "${LIB_DIR}/glad")
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
	set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
else ()
	set(GLAD_GENERATOR "c-debug" CACHE STRING "Language to generate the binding for")
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")
set(GLAD_EXTENSIONS "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included")
set(GLAD_SPEC "gl" CACHE STRING "Name of the spec")
set(GLAD_INSTALL ON CACHE BOOL "Generate installation target")
add_subdirectory(${GLAD_DIR})

include("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")

if (COGL_BUILD_EXAMPLES)
	enable_testing()

    add_executable(base_test tests/base_test.cpp)
    add_executable(merge_test tests/merge_test.cpp)
    add_executable(multiwindow_test tests/multiwindow_test.cpp)
    add_executable(instancing_test tests/instancing_test.cpp)

    target_include_directories (base_test PRIVATE
            ${GLAD_INCLUDE_DIRS}
            ${COGL_INCLUDE_DIRS}
            ${GLM_DIR}
            "${GLFW_DIR}/include")
    target_compile_features(base_test PRIVATE cxx_auto_type cxx_decltype_auto)
    target_include_directories (merge_test PRIVATE
            ${GLAD_INCLUDE_DIRS}
            ${COGL_INCLUDE_DIRS}
            ${GLM_DIR}
            "${GLFW_DIR}/include")
    target_compile_features(merge_test PRIVATE cxx_auto_type cxx_decltype_auto)
    target_include_directories (multiwindow_test PRIVATE
            ${GLAD_INCLUDE_DIRS}
            ${COGL_INCLUDE_DIRS}
            ${GLM_DIR}
            "${GLFW_DIR}/include")
    target_compile_features(multiwindow_test PRIVATE cxx_auto_type cxx_decltype_auto)
    target_include_directories (instancing_test PRIVATE
            ${GLAD_INCLUDE_DIRS}
            ${COGL_INCLUDE_DIRS}
            ${GLM_DIR}
            "${GLFW_DIR}/include")
    target_compile_features(instancing_test PRIVATE cxx_auto_type cxx_decltype_auto)

    target_link_libraries(base_test cogl)
    target_link_libraries(merge_test cogl)
    target_link_libraries(multiwindow_test cogl)
    target_link_libraries(instancing_test cogl)

    add_test(base_test base_test)
    add_test(merge_test merge_test)
    add_test(multiwindow_test multiwindow_test)
    add_test(instancing_test instancing_test)
endif (COGL_BUILD_EXAMPLES)