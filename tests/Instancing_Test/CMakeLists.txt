cmake_minimum_required(VERSION 3.9)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(instancing_test src/main.cpp)
target_include_directories (instancing_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							${COGL_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
target_compile_features(instancing_test PRIVATE cxx_auto_type cxx_decltype_auto)
target_link_libraries (instancing_test
                       cogl
                       )