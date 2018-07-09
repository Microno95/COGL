add_executable(merge_test src/main.cpp)
target_include_directories (merge_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							${COGL_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
target_compile_features(merge_test PRIVATE cxx_auto_type)
target_link_libraries (merge_test
                       cogl
                       glm
                       glad
                       ${GLFW_LIBRARIES}
                       )