cmake_minimum_required(VERSION 3.6)
project(CustomOGL)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

message(STATUS "Checking OpenMP")
find_package(OpenMP)
IF (OPENMP_FOUND)
    message("Found OpenMP!")
    # add flags for OpenMP
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ELSE ()
    message("Missed OpenMP!")
ENDIF ()

include_directories(${CUDA_PART_SOURCE_DIR}/common)
# packages
find_package(CUDA REQUIRED)

# nvcc flags
set(CUDA_NVCC_FLAGS -gencode arch=compute_60,code=sm_60;-G;-g)
set(CUDA_VERBOSE_BUILD ON)

add_subdirectory(OpenGL/glfw)
include_directories(OpenGL/glfw/include)
include_directories(OpenGL/glfw/deps/)
add_subdirectory(OpenGL/glm)
include_directories(OpenGL/glm/)
find_package(OpenGL REQUIRED)
include_directories(idek ${OPENGL_INCLUDE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_FILES
        cogl.h
        cogl/Camera.cpp
        cogl/Camera.h
        cogl/LightSource.cpp
        cogl/LightSource.h
        cogl/Mesh.cpp
        cogl/Mesh.h
        cogl/MeshInstance.cpp
        cogl/MeshInstance.h
        cogl/GLWindow.cpp
        cogl/GLWindow.h
        cogl/Shader.cpp
        cogl/Shader.h
        cogl/Renderable.h
        Constants.h
        OpenGL/glfw/deps/glad.c cogl/StateBase.h cogl/StateBase.cpp cogl/Framebuffer.cpp cogl/Framebuffer.h cogl/StateBaseGLWindow.cpp cogl/StateBaseGLWindow.h)

CUDA_ADD_LIBRARY(CustomOGL ${SOURCE_FILES})
target_link_libraries(CustomOGL ${OPENGL_gl_LIBRARY})
target_link_libraries(CustomOGL glfw ${GLFW_LIBRARIES})

add_executable(base_test "tests/Base_Test/main.cpp" ${SOURCE_FILES})
add_executable(instancing_test "tests/Instancing_Test/main.cpp" ${SOURCE_FILES})
target_link_libraries(base_test ${OPENGL_gl_LIBRARY})
target_link_libraries(base_test glfw ${GLFW_LIBRARIES})
target_link_libraries(instancing_test ${OPENGL_gl_LIBRARY})
target_link_libraries(instancing_test glfw ${GLFW_LIBRARIES})