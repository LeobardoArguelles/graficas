# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/larguelles/school/atitulos/graficas/ejercicios/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/ejercicio07.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ejercicio07.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ejercicio07.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ejercicio07.dir/flags.make

CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o: CMakeFiles/ejercicio07.dir/flags.make
CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e07/ejercicio07.cpp
CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o: CMakeFiles/ejercicio07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o -MF CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o.d -o CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e07/ejercicio07.cpp

CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e07/ejercicio07.cpp > CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.i

CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e07/ejercicio07.cpp -o CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.s

CMakeFiles/ejercicio07.dir/common/shader.cpp.o: CMakeFiles/ejercicio07.dir/flags.make
CMakeFiles/ejercicio07.dir/common/shader.cpp.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp
CMakeFiles/ejercicio07.dir/common/shader.cpp.o: CMakeFiles/ejercicio07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ejercicio07.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ejercicio07.dir/common/shader.cpp.o -MF CMakeFiles/ejercicio07.dir/common/shader.cpp.o.d -o CMakeFiles/ejercicio07.dir/common/shader.cpp.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp

CMakeFiles/ejercicio07.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejercicio07.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp > CMakeFiles/ejercicio07.dir/common/shader.cpp.i

CMakeFiles/ejercicio07.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejercicio07.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp -o CMakeFiles/ejercicio07.dir/common/shader.cpp.s

# Object files for target ejercicio07
ejercicio07_OBJECTS = \
"CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o" \
"CMakeFiles/ejercicio07.dir/common/shader.cpp.o"

# External object files for target ejercicio07
ejercicio07_EXTERNAL_OBJECTS =

ejercicio07: CMakeFiles/ejercicio07.dir/e07/ejercicio07.cpp.o
ejercicio07: CMakeFiles/ejercicio07.dir/common/shader.cpp.o
ejercicio07: CMakeFiles/ejercicio07.dir/build.make
ejercicio07: /usr/lib/libGL.so
ejercicio07: /usr/lib/libGLU.so
ejercicio07: external/glfw-3.1.2/src/libglfw3.a
ejercicio07: external/libGLEW_1130.a
ejercicio07: /usr/lib/libglut.so
ejercicio07: /usr/lib/libXmu.so
ejercicio07: /usr/lib/libXi.so
ejercicio07: /usr/lib/libfreetype.so
ejercicio07: /usr/lib/librt.a
ejercicio07: /usr/lib/libm.so
ejercicio07: /usr/lib/libX11.so
ejercicio07: /usr/lib/libXrandr.so
ejercicio07: /usr/lib/libXinerama.so
ejercicio07: /usr/lib/libXxf86vm.so
ejercicio07: /usr/lib/libXcursor.so
ejercicio07: /usr/lib/librt.a
ejercicio07: /usr/lib/libm.so
ejercicio07: /usr/lib/libX11.so
ejercicio07: /usr/lib/libXrandr.so
ejercicio07: /usr/lib/libXinerama.so
ejercicio07: /usr/lib/libXxf86vm.so
ejercicio07: /usr/lib/libXcursor.so
ejercicio07: /usr/lib/libGL.so
ejercicio07: /usr/lib/libGLU.so
ejercicio07: /usr/lib/libXi.so
ejercicio07: CMakeFiles/ejercicio07.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ejercicio07"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ejercicio07.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/./ejercicio07 /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e07/

# Rule to build all files generated by this target.
CMakeFiles/ejercicio07.dir/build: ejercicio07
.PHONY : CMakeFiles/ejercicio07.dir/build

CMakeFiles/ejercicio07.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ejercicio07.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ejercicio07.dir/clean

CMakeFiles/ejercicio07.dir/depend:
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larguelles/school/atitulos/graficas/ejercicios/cpp /home/larguelles/school/atitulos/graficas/ejercicios/cpp /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles/ejercicio07.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ejercicio07.dir/depend

