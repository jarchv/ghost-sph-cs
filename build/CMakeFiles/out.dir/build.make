# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build

# Include any dependencies generated for this target.
include CMakeFiles/out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/out.dir/flags.make

CMakeFiles/out.dir/src/main.cpp.o: CMakeFiles/out.dir/flags.make
CMakeFiles/out.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/out.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/out.dir/src/main.cpp.o -c /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/main.cpp

CMakeFiles/out.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/out.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/main.cpp > CMakeFiles/out.dir/src/main.cpp.i

CMakeFiles/out.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/out.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/main.cpp -o CMakeFiles/out.dir/src/main.cpp.s

# Object files for target out
out_OBJECTS = \
"CMakeFiles/out.dir/src/main.cpp.o"

# External object files for target out
out_EXTERNAL_OBJECTS =

out: CMakeFiles/out.dir/src/main.cpp.o
out: CMakeFiles/out.dir/build.make
out: libbase.a
out: /usr/lib/x86_64-linux-gnu/libglfw.so.3.2
out: /usr/lib/x86_64-linux-gnu/libOpenGL.so
out: /usr/lib/x86_64-linux-gnu/libGLX.so
out: /usr/lib/x86_64-linux-gnu/libGLU.so
out: /usr/lib/x86_64-linux-gnu/libGLEW.so
out: CMakeFiles/out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/out.dir/build: out

.PHONY : CMakeFiles/out.dir/build

CMakeFiles/out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/out.dir/clean

CMakeFiles/out.dir/depend:
	cd /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles/out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/out.dir/depend

