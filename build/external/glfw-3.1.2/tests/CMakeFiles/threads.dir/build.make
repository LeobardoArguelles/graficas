# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
include external/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/tests/CMakeFiles/threads.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/tests/threads.c
external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o -MF CMakeFiles/threads.dir/threads.c.o.d -o CMakeFiles/threads.dir/threads.c.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/tests/threads.c

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/threads.c.i"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/tests/threads.c > CMakeFiles/threads.dir/threads.c.i

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/threads.c.s"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/tests/threads.c -o CMakeFiles/threads.dir/threads.c.s

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/deps/tinycthread.c
external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o -MF CMakeFiles/threads.dir/__/deps/tinycthread.c.o.d -o CMakeFiles/threads.dir/__/deps/tinycthread.c.o -c /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/deps/tinycthread.c

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/__/deps/tinycthread.c.i"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/deps/tinycthread.c > CMakeFiles/threads.dir/__/deps/tinycthread.c.i

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/__/deps/tinycthread.c.s"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/deps/tinycthread.c -o CMakeFiles/threads.dir/__/deps/tinycthread.c.s

# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/threads.c.o" \
"CMakeFiles/threads.dir/__/deps/tinycthread.c.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/threads: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o
external/glfw-3.1.2/tests/threads: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o
external/glfw-3.1.2/tests/threads: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/build.make
external/glfw-3.1.2/tests/threads: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/threads: /usr/lib/librt.a
external/glfw-3.1.2/tests/threads: /usr/lib/libm.so
external/glfw-3.1.2/tests/threads: /usr/lib/libX11.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXrandr.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXinerama.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXi.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXxf86vm.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXcursor.so
external/glfw-3.1.2/tests/threads: /usr/lib/libGL.so
external/glfw-3.1.2/tests/threads: /usr/lib/librt.a
external/glfw-3.1.2/tests/threads: /usr/lib/libm.so
external/glfw-3.1.2/tests/threads: /usr/lib/libX11.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXrandr.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXinerama.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXi.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXxf86vm.so
external/glfw-3.1.2/tests/threads: /usr/lib/libXcursor.so
external/glfw-3.1.2/tests/threads: /usr/lib/libGL.so
external/glfw-3.1.2/tests/threads: external/glfw-3.1.2/tests/CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable threads"
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/threads.dir/build: external/glfw-3.1.2/tests/threads
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/threads.dir/build

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/clean:
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/threads.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend:
	cd /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larguelles/school/atitulos/graficas/ejercicios/cpp /home/larguelles/school/atitulos/graficas/ejercicios/cpp/external/glfw-3.1.2/tests /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests /home/larguelles/school/atitulos/graficas/ejercicios/cpp/build/external/glfw-3.1.2/tests/CMakeFiles/threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend

