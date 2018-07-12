set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(base_test src/main.cpp)
target_include_directories (base_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
target_compile_features(base_test PRIVATE cxx_auto_type cxx_decltype_auto)
target_link_libraries (base_test
                       cogl
                       )