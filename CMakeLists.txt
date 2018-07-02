cmake_minimum_required(VERSION 3.6)
project(COGL)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES
        cogl.h
		Constants.h
        cogl/Camera.cpp
        cogl/Camera.h
		cogl/Mesh.cpp
        cogl/Mesh.h
        cogl/MeshInstance.cpp
        cogl/MeshInstance.h
        cogl/GLWindow.cpp
        cogl/GLWindow.h
        cogl/Shader.cpp
        cogl/Shader.h
        cogl/Renderable.h
        cogl/StateBase.h 
		cogl/StateBase.cpp 
		cogl/Framebuffer.cpp 
		cogl/Framebuffer.h 
		cogl/StateBaseGLWindow.cpp 
		cogl/StateBaseGLWindow.h
		cogl/MeshRepresentation.cpp
		cogl/MeshRepresentation.h)

# Include OpenMP libraries
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

add_library(${PROJECT_NAME} ${SOURCE_FILES})

# Include OpenGL libraries
find_package(OpenGL REQUIRED)
include_directories(${PROJECT_NAME} ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

# Add glfw libraries
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# Add glm libraries
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory(${GLM_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}/glm")
target_link_libraries(${PROJECT_NAME} glm)

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
add_subdirectory(${GLAD_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glad)

add_executable(base_test "tests/Base_Test/main.cpp" ${SOURCE_FILES})
add_executable(instancing_test "tests/Instancing_Test/main.cpp" ${SOURCE_FILES})
add_executable(merge_test "tests/Merge_Test/main.cpp" ${SOURCE_FILES})
target_link_libraries(base_test ${OPENGL_gl_LIBRARY})
target_link_libraries(base_test glfw ${GLFW_LIBRARIES})
target_link_libraries(base_test glm)
target_link_libraries(base_test glad)
target_link_libraries(base_test ${PROJECT_NAME})
target_link_libraries(instancing_test ${OPENGL_gl_LIBRARY})
target_link_libraries(instancing_test glfw ${GLFW_LIBRARIES})
target_link_libraries(instancing_test glm)
target_link_libraries(instancing_test glad)
target_link_libraries(instancing_test ${PROJECT_NAME})
target_link_libraries(merge_test ${OPENGL_gl_LIBRARY})
target_link_libraries(merge_test glfw ${GLFW_LIBRARIES})
target_link_libraries(merge_test glm)
target_link_libraries(merge_test glad)
target_link_libraries(merge_test ${PROJECT_NAME})