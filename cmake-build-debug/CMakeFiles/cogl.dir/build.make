# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\External Program Files\JetBrains\apps\CLion\ch-0\182.3684.76\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\External Program Files\JetBrains\apps\CLion\ch-0\182.3684.76\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ekin4\CLionProjects\COGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cogl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cogl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cogl.dir/flags.make

CMakeFiles/cogl.dir/src/Camera.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/Camera.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/Camera.cpp.obj: ../src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cogl.dir/src/Camera.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\Camera.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\Camera.cpp

CMakeFiles/cogl.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/Camera.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\Camera.cpp > CMakeFiles\cogl.dir\src\Camera.cpp.i

CMakeFiles/cogl.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/Camera.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\Camera.cpp -o CMakeFiles\cogl.dir\src\Camera.cpp.s

CMakeFiles/cogl.dir/src/framebuffer.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/framebuffer.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/framebuffer.cpp.obj: ../src/framebuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cogl.dir/src/framebuffer.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\framebuffer.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\framebuffer.cpp

CMakeFiles/cogl.dir/src/framebuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/framebuffer.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\framebuffer.cpp > CMakeFiles\cogl.dir\src\framebuffer.cpp.i

CMakeFiles/cogl.dir/src/framebuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/framebuffer.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\framebuffer.cpp -o CMakeFiles\cogl.dir\src\framebuffer.cpp.s

CMakeFiles/cogl.dir/src/GLWindow.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/GLWindow.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/GLWindow.cpp.obj: ../src/GLWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cogl.dir/src/GLWindow.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\GLWindow.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\GLWindow.cpp

CMakeFiles/cogl.dir/src/GLWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/GLWindow.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\GLWindow.cpp > CMakeFiles\cogl.dir\src\GLWindow.cpp.i

CMakeFiles/cogl.dir/src/GLWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/GLWindow.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\GLWindow.cpp -o CMakeFiles\cogl.dir\src\GLWindow.cpp.s

CMakeFiles/cogl.dir/src/Mesh.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/Mesh.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/Mesh.cpp.obj: ../src/Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cogl.dir/src/Mesh.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\Mesh.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\Mesh.cpp

CMakeFiles/cogl.dir/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/Mesh.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\Mesh.cpp > CMakeFiles\cogl.dir\src\Mesh.cpp.i

CMakeFiles/cogl.dir/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/Mesh.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\Mesh.cpp -o CMakeFiles\cogl.dir\src\Mesh.cpp.s

CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj: ../src/MeshInstance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\MeshInstance.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\MeshInstance.cpp

CMakeFiles/cogl.dir/src/MeshInstance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/MeshInstance.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\MeshInstance.cpp > CMakeFiles\cogl.dir\src\MeshInstance.cpp.i

CMakeFiles/cogl.dir/src/MeshInstance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/MeshInstance.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\MeshInstance.cpp -o CMakeFiles\cogl.dir\src\MeshInstance.cpp.s

CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj: ../src/MeshRepresentation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\MeshRepresentation.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\MeshRepresentation.cpp

CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\MeshRepresentation.cpp > CMakeFiles\cogl.dir\src\MeshRepresentation.cpp.i

CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\MeshRepresentation.cpp -o CMakeFiles\cogl.dir\src\MeshRepresentation.cpp.s

CMakeFiles/cogl.dir/src/Shader.cpp.obj: CMakeFiles/cogl.dir/flags.make
CMakeFiles/cogl.dir/src/Shader.cpp.obj: CMakeFiles/cogl.dir/includes_CXX.rsp
CMakeFiles/cogl.dir/src/Shader.cpp.obj: ../src/Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/cogl.dir/src/Shader.cpp.obj"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cogl.dir\src\Shader.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\src\Shader.cpp

CMakeFiles/cogl.dir/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cogl.dir/src/Shader.cpp.i"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\src\Shader.cpp > CMakeFiles\cogl.dir\src\Shader.cpp.i

CMakeFiles/cogl.dir/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cogl.dir/src/Shader.cpp.s"
	C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\src\Shader.cpp -o CMakeFiles\cogl.dir\src\Shader.cpp.s

# Object files for target cogl
cogl_OBJECTS = \
"CMakeFiles/cogl.dir/src/Camera.cpp.obj" \
"CMakeFiles/cogl.dir/src/framebuffer.cpp.obj" \
"CMakeFiles/cogl.dir/src/GLWindow.cpp.obj" \
"CMakeFiles/cogl.dir/src/Mesh.cpp.obj" \
"CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj" \
"CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj" \
"CMakeFiles/cogl.dir/src/Shader.cpp.obj"

# External object files for target cogl
cogl_EXTERNAL_OBJECTS =

libcogl.a: CMakeFiles/cogl.dir/src/Camera.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/framebuffer.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/GLWindow.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/Mesh.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/MeshInstance.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/MeshRepresentation.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/src/Shader.cpp.obj
libcogl.a: CMakeFiles/cogl.dir/build.make
libcogl.a: CMakeFiles/cogl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libcogl.a"
	$(CMAKE_COMMAND) -P CMakeFiles\cogl.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cogl.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cogl.dir/build: libcogl.a

.PHONY : CMakeFiles/cogl.dir/build

CMakeFiles/cogl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cogl.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cogl.dir/clean

CMakeFiles/cogl.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ekin4\CLionProjects\COGL C:\Users\ekin4\CLionProjects\COGL C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles\cogl.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cogl.dir/depend
