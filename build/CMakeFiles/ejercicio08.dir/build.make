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
include CMakeFiles/ejercicio08.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ejercicio08.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ejercicio08.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ejercicio08.dir/flags.make

CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o: CMakeFiles/ejercicio08.dir/flags.make
CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e08/ejercicio08.cpp
CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o: CMakeFiles/ejercicio08.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o -MF CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o.d -o CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e08/ejercicio08.cpp

CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e08/ejercicio08.cpp > CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.i

CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e08/ejercicio08.cpp -o CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.s

CMakeFiles/ejercicio08.dir/common/shader.cpp.o: CMakeFiles/ejercicio08.dir/flags.make
CMakeFiles/ejercicio08.dir/common/shader.cpp.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp
CMakeFiles/ejercicio08.dir/common/shader.cpp.o: CMakeFiles/ejercicio08.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ejercicio08.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ejercicio08.dir/common/shader.cpp.o -MF CMakeFiles/ejercicio08.dir/common/shader.cpp.o.d -o CMakeFiles/ejercicio08.dir/common/shader.cpp.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp

CMakeFiles/ejercicio08.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejercicio08.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp > CMakeFiles/ejercicio08.dir/common/shader.cpp.i

CMakeFiles/ejercicio08.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejercicio08.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/common/shader.cpp -o CMakeFiles/ejercicio08.dir/common/shader.cpp.s

# Object files for target ejercicio08
ejercicio08_OBJECTS = \
"CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o" \
"CMakeFiles/ejercicio08.dir/common/shader.cpp.o"

# External object files for target ejercicio08
ejercicio08_EXTERNAL_OBJECTS =

ejercicio08: CMakeFiles/ejercicio08.dir/e08/ejercicio08.cpp.o
ejercicio08: CMakeFiles/ejercicio08.dir/common/shader.cpp.o
ejercicio08: CMakeFiles/ejercicio08.dir/build.make
ejercicio08: /usr/lib/libGL.so
ejercicio08: /usr/lib/libGLU.so
ejercicio08: external/glfw-3.1.2/src/libglfw3.a
ejercicio08: external/libGLEW_1130.a
ejercicio08: /usr/lib/libglut.so
ejercicio08: /usr/lib/libXmu.so
ejercicio08: /usr/lib/libXi.so
ejercicio08: /usr/lib/libfreetype.so
ejercicio08: /usr/lib/librt.a
ejercicio08: /usr/lib/libm.so
ejercicio08: /usr/lib/libX11.so
ejercicio08: /usr/lib/libXrandr.so
ejercicio08: /usr/lib/libXinerama.so
ejercicio08: /usr/lib/libXxf86vm.so
ejercicio08: /usr/lib/libXcursor.so
ejercicio08: /usr/lib/librt.a
ejercicio08: /usr/lib/libm.so
ejercicio08: /usr/lib/libX11.so
ejercicio08: /usr/lib/libXrandr.so
ejercicio08: /usr/lib/libXinerama.so
ejercicio08: /usr/lib/libXxf86vm.so
ejercicio08: /usr/lib/libXcursor.so
ejercicio08: /usr/lib/libGL.so
ejercicio08: /usr/lib/libGLU.so
ejercicio08: /usr/lib/libXi.so
ejercicio08: CMakeFiles/ejercicio08.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ejercicio08"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ejercicio08.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/./ejercicio08 /home/larguelles/school/atitulos/graficas/ejercicios/cpp/e08/

# Rule to build all files generated by this target.
CMakeFiles/ejercicio08.dir/build: ejercicio08
.PHONY : CMakeFiles/ejercicio08.dir/build

CMakeFiles/ejercicio08.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ejercicio08.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ejercicio08.dir/clean

CMakeFiles/ejercicio08.dir/depend:
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larguelles/school/atitulos/graficas/ejercicios/cpp /home/larguelles/school/atitulos/graficas/ejercicios/cpp /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles/ejercicio08.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ejercicio08.dir/depend

