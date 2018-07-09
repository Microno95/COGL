add_executable(multiwindow_test src/main.cpp)
target_include_directories (multiwindow_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							${COGL_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
target_compile_features(multiwindow_test PRIVATE cxx_auto_type)
target_link_libraries (multiwindow_test
                       cogl
                       glm
                       glad
                       ${GLFW_LIBRARIES}
                       )