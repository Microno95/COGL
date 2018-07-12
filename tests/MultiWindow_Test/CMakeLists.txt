set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(multiwindow_test src/main.cpp)
target_include_directories (multiwindow_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							${COGL_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
target_compile_features(multiwindow_test PRIVATE cxx_auto_type cxx_decltype_auto)
target_link_libraries (multiwindow_test
                       cogl
                       )