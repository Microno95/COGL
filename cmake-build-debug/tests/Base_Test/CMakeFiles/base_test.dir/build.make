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
include tests/Base_Test/CMakeFiles/base_test.dir/depend.make

# Include the progress variables for this target.
include tests/Base_Test/CMakeFiles/base_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/Base_Test/CMakeFiles/base_test.dir/flags.make

tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.obj: tests/Base_Test/CMakeFiles/base_test.dir/flags.make
tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.obj: tests/Base_Test/CMakeFiles/base_test.dir/includes_CXX.rsp
tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.obj: ../tests/Base_Test/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.obj"
	cd /d C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test && C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\base_test.dir\src\main.cpp.obj -c C:\Users\ekin4\CLionProjects\COGL\tests\Base_Test\src\main.cpp

tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base_test.dir/src/main.cpp.i"
	cd /d C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test && C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ekin4\CLionProjects\COGL\tests\Base_Test\src\main.cpp > CMakeFiles\base_test.dir\src\main.cpp.i

tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base_test.dir/src/main.cpp.s"
	cd /d C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test && C:\EXTERN~1\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ekin4\CLionProjects\COGL\tests\Base_Test\src\main.cpp -o CMakeFiles\base_test.dir\src\main.cpp.s

# Object files for target base_test
base_test_OBJECTS = \
"CMakeFiles/base_test.dir/src/main.cpp.obj"

# External object files for target base_test
base_test_EXTERNAL_OBJECTS =

../tests/Base_Test/base_test.exe: tests/Base_Test/CMakeFiles/base_test.dir/src/main.cpp.obj
../tests/Base_Test/base_test.exe: tests/Base_Test/CMakeFiles/base_test.dir/build.make
../tests/Base_Test/base_test.exe: libcogl.a
../tests/Base_Test/base_test.exe: C:/External\ Program\ Files/mingw-w64/mingw64/lib/gcc/x86_64-w64-mingw32/7.2.0/libgomp.dll.a
../tests/Base_Test/base_test.exe: C:/External\ Program\ Files/mingw-w64/mingw64/x86_64-w64-mingw32/lib/libmingwthrd.a
../tests/Base_Test/base_test.exe: deps/glfw/src/libglfw3.a
../tests/Base_Test/base_test.exe: deps/glad/libglad.a
../tests/Base_Test/base_test.exe: tests/Base_Test/CMakeFiles/base_test.dir/linklibs.rsp
../tests/Base_Test/base_test.exe: tests/Base_Test/CMakeFiles/base_test.dir/objects1.rsp
../tests/Base_Test/base_test.exe: tests/Base_Test/CMakeFiles/base_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\..\..\tests\Base_Test\base_test.exe"
	cd /d C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\base_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/Base_Test/CMakeFiles/base_test.dir/build: ../tests/Base_Test/base_test.exe

.PHONY : tests/Base_Test/CMakeFiles/base_test.dir/build

tests/Base_Test/CMakeFiles/base_test.dir/clean:
	cd /d C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test && $(CMAKE_COMMAND) -P CMakeFiles\base_test.dir\cmake_clean.cmake
.PHONY : tests/Base_Test/CMakeFiles/base_test.dir/clean

tests/Base_Test/CMakeFiles/base_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ekin4\CLionProjects\COGL C:\Users\ekin4\CLionProjects\COGL\tests\Base_Test C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test C:\Users\ekin4\CLionProjects\COGL\cmake-build-debug\tests\Base_Test\CMakeFiles\base_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/Base_Test/CMakeFiles/base_test.dir/depend
