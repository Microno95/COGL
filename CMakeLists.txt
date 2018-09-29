cmake_minimum_required(VERSION 3.9)
project(libcogl VERSION 1.0.0 LANGUAGES CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

option(COGL_BUILD_EXAMPLES "Build the cogl example programs" ON)
option(COGL_EXPORT "Build COGL as a dependency" ON)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

if(NOT COGL_EXPORT)
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
endif()

set(COGL_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include")

# Include OpenMP libraries
message(STATUS "Checking OpenMP")
find_package(OpenMP)

# Include OpenGL libraries
set(OpenGL_GL_PREFERENCE GLVND)
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

add_library(cogl ${COGL_SOURCES})

set_target_properties(cogl PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(cogl PRIVATE cxx_std_14)
set_target_properties(cogl PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(cogl
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        INTERFACE
        $<INSTALL_INTERFACE:include/cogl>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

if(OpenMP_CXX_FOUND)
    target_link_libraries(cogl PUBLIC OpenMP::OpenMP_CXX)
endif()

include_directories(cogl ${OPENGL_INCLUDE_DIR})
target_link_libraries(cogl PUBLIC ${OPENGL_gl_LIBRARY})

target_include_directories(cogl PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(cogl PRIVATE "GLFW_INCLUDE_NONE")
target_link_libraries(cogl PUBLIC glfw ${GLFW_LIBRARIES})

target_include_directories(cogl PRIVATE "${GLM_DIR}/glm")
target_link_libraries(cogl PUBLIC glm)

target_include_directories(cogl PRIVATE ${GLAD_INCLUDE_DIRS})
target_link_libraries(cogl PUBLIC glad)

if (UNIX)
    target_link_libraries(cogl PUBLIC ${CMAKE_DL_LIBS})
endif()

#[[# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS cogl EXPORT coglTargets
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT coglTargets DESTINATION share/COGL/cmake)]]#

#Export COGL Directories
if(COGL_EXPORT)
    set(COGL_LIBRARIES cogl PARENT_SCOPE)
    set(COGL_INCLUDE_DIRS ${COGL_INCLUDE_DIRS} PARENT_SCOPE)
endif()

if (COGL_BUILD_EXAMPLES)
	enable_testing()

	add_subdirectory(tests/Base_Test)
	add_subdirectory(tests/Instancing_Test)
	add_subdirectory(tests/Merge_Test)
	add_subdirectory(tests/MultiWindow_Test)
endif (COGL_BUILD_EXAMPLES)