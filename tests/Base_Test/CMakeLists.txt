add_executable(base_test src/main.cpp)
target_include_directories (base_test PRIVATE 
							src 
							${GLAD_INCLUDE_DIRS}
							${COGL_INCLUDE_DIRS}
							"${GLM_DIR}/glm" 
							"${GLFW_DIR}/include")
message("${COGL_INCLUDE_DIRS}")
target_compile_features(base_test PRIVATE cxx_auto_type)
target_link_libraries (base_test
                       cogl
                       glm
                       glad
                       ${GLFW_LIBRARIES}
                       )