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
include CMakeFiles/base.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/base.dir/flags.make

CMakeFiles/base.dir/src/tools/utils.cpp.o: CMakeFiles/base.dir/flags.make
CMakeFiles/base.dir/src/tools/utils.cpp.o: ../src/tools/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/base.dir/src/tools/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/src/tools/utils.cpp.o -c /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/tools/utils.cpp

CMakeFiles/base.dir/src/tools/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/src/tools/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/tools/utils.cpp > CMakeFiles/base.dir/src/tools/utils.cpp.i

CMakeFiles/base.dir/src/tools/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/src/tools/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/tools/utils.cpp -o CMakeFiles/base.dir/src/tools/utils.cpp.s

CMakeFiles/base.dir/src/commons/controls.cpp.o: CMakeFiles/base.dir/flags.make
CMakeFiles/base.dir/src/commons/controls.cpp.o: ../src/commons/controls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/base.dir/src/commons/controls.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/src/commons/controls.cpp.o -c /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/controls.cpp

CMakeFiles/base.dir/src/commons/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/src/commons/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/controls.cpp > CMakeFiles/base.dir/src/commons/controls.cpp.i

CMakeFiles/base.dir/src/commons/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/src/commons/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/controls.cpp -o CMakeFiles/base.dir/src/commons/controls.cpp.s

CMakeFiles/base.dir/src/commons/loadshader.cpp.o: CMakeFiles/base.dir/flags.make
CMakeFiles/base.dir/src/commons/loadshader.cpp.o: ../src/commons/loadshader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/base.dir/src/commons/loadshader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/src/commons/loadshader.cpp.o -c /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/loadshader.cpp

CMakeFiles/base.dir/src/commons/loadshader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/src/commons/loadshader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/loadshader.cpp > CMakeFiles/base.dir/src/commons/loadshader.cpp.i

CMakeFiles/base.dir/src/commons/loadshader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/src/commons/loadshader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/src/commons/loadshader.cpp -o CMakeFiles/base.dir/src/commons/loadshader.cpp.s

# Object files for target base
base_OBJECTS = \
"CMakeFiles/base.dir/src/tools/utils.cpp.o" \
"CMakeFiles/base.dir/src/commons/controls.cpp.o" \
"CMakeFiles/base.dir/src/commons/loadshader.cpp.o"

# External object files for target base
base_EXTERNAL_OBJECTS =

libbase.a: CMakeFiles/base.dir/src/tools/utils.cpp.o
libbase.a: CMakeFiles/base.dir/src/commons/controls.cpp.o
libbase.a: CMakeFiles/base.dir/src/commons/loadshader.cpp.o
libbase.a: CMakeFiles/base.dir/build.make
libbase.a: CMakeFiles/base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libbase.a"
	$(CMAKE_COMMAND) -P CMakeFiles/base.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/base.dir/build: libbase.a

.PHONY : CMakeFiles/base.dir/build

CMakeFiles/base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/base.dir/clean

CMakeFiles/base.dir/depend:
	cd /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build /home/jose/Documentos/cs/crs/c2/computacion-grafica/final/ghost-sph-cs/build/CMakeFiles/base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/base.dir/depend
