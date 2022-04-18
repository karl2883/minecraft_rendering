# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/karl2883/programming/c++/minecraft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/karl2883/programming/c++/minecraft/build

# Include any dependencies generated for this target.
include src/gfx/CMakeFiles/Gfx.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/gfx/CMakeFiles/Gfx.dir/compiler_depend.make

# Include the progress variables for this target.
include src/gfx/CMakeFiles/Gfx.dir/progress.make

# Include the compile flags for this target's objects.
include src/gfx/CMakeFiles/Gfx.dir/flags.make

src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o: src/gfx/CMakeFiles/Gfx.dir/flags.make
src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o: ../src/gfx/Shader.cpp
src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o: src/gfx/CMakeFiles/Gfx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/karl2883/programming/c++/minecraft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o -MF CMakeFiles/Gfx.dir/Shader.cpp.o.d -o CMakeFiles/Gfx.dir/Shader.cpp.o -c /home/karl2883/programming/c++/minecraft/src/gfx/Shader.cpp

src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gfx.dir/Shader.cpp.i"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karl2883/programming/c++/minecraft/src/gfx/Shader.cpp > CMakeFiles/Gfx.dir/Shader.cpp.i

src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gfx.dir/Shader.cpp.s"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karl2883/programming/c++/minecraft/src/gfx/Shader.cpp -o CMakeFiles/Gfx.dir/Shader.cpp.s

src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o: src/gfx/CMakeFiles/Gfx.dir/flags.make
src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o: ../src/gfx/Renderer.cpp
src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o: src/gfx/CMakeFiles/Gfx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/karl2883/programming/c++/minecraft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o -MF CMakeFiles/Gfx.dir/Renderer.cpp.o.d -o CMakeFiles/Gfx.dir/Renderer.cpp.o -c /home/karl2883/programming/c++/minecraft/src/gfx/Renderer.cpp

src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gfx.dir/Renderer.cpp.i"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karl2883/programming/c++/minecraft/src/gfx/Renderer.cpp > CMakeFiles/Gfx.dir/Renderer.cpp.i

src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gfx.dir/Renderer.cpp.s"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karl2883/programming/c++/minecraft/src/gfx/Renderer.cpp -o CMakeFiles/Gfx.dir/Renderer.cpp.s

src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o: src/gfx/CMakeFiles/Gfx.dir/flags.make
src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o: ../src/gfx/Texture.cpp
src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o: src/gfx/CMakeFiles/Gfx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/karl2883/programming/c++/minecraft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o -MF CMakeFiles/Gfx.dir/Texture.cpp.o.d -o CMakeFiles/Gfx.dir/Texture.cpp.o -c /home/karl2883/programming/c++/minecraft/src/gfx/Texture.cpp

src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gfx.dir/Texture.cpp.i"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karl2883/programming/c++/minecraft/src/gfx/Texture.cpp > CMakeFiles/Gfx.dir/Texture.cpp.i

src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gfx.dir/Texture.cpp.s"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karl2883/programming/c++/minecraft/src/gfx/Texture.cpp -o CMakeFiles/Gfx.dir/Texture.cpp.s

src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o: src/gfx/CMakeFiles/Gfx.dir/flags.make
src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o: ../src/gfx/TextureHandler.cpp
src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o: src/gfx/CMakeFiles/Gfx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/karl2883/programming/c++/minecraft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o -MF CMakeFiles/Gfx.dir/TextureHandler.cpp.o.d -o CMakeFiles/Gfx.dir/TextureHandler.cpp.o -c /home/karl2883/programming/c++/minecraft/src/gfx/TextureHandler.cpp

src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gfx.dir/TextureHandler.cpp.i"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karl2883/programming/c++/minecraft/src/gfx/TextureHandler.cpp > CMakeFiles/Gfx.dir/TextureHandler.cpp.i

src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gfx.dir/TextureHandler.cpp.s"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karl2883/programming/c++/minecraft/src/gfx/TextureHandler.cpp -o CMakeFiles/Gfx.dir/TextureHandler.cpp.s

# Object files for target Gfx
Gfx_OBJECTS = \
"CMakeFiles/Gfx.dir/Shader.cpp.o" \
"CMakeFiles/Gfx.dir/Renderer.cpp.o" \
"CMakeFiles/Gfx.dir/Texture.cpp.o" \
"CMakeFiles/Gfx.dir/TextureHandler.cpp.o"

# External object files for target Gfx
Gfx_EXTERNAL_OBJECTS =

src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/Shader.cpp.o
src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/Renderer.cpp.o
src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/Texture.cpp.o
src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/TextureHandler.cpp.o
src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/build.make
src/gfx/libGfx.a: src/gfx/CMakeFiles/Gfx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/karl2883/programming/c++/minecraft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libGfx.a"
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && $(CMAKE_COMMAND) -P CMakeFiles/Gfx.dir/cmake_clean_target.cmake
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Gfx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/gfx/CMakeFiles/Gfx.dir/build: src/gfx/libGfx.a
.PHONY : src/gfx/CMakeFiles/Gfx.dir/build

src/gfx/CMakeFiles/Gfx.dir/clean:
	cd /home/karl2883/programming/c++/minecraft/build/src/gfx && $(CMAKE_COMMAND) -P CMakeFiles/Gfx.dir/cmake_clean.cmake
.PHONY : src/gfx/CMakeFiles/Gfx.dir/clean

src/gfx/CMakeFiles/Gfx.dir/depend:
	cd /home/karl2883/programming/c++/minecraft/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/karl2883/programming/c++/minecraft /home/karl2883/programming/c++/minecraft/src/gfx /home/karl2883/programming/c++/minecraft/build /home/karl2883/programming/c++/minecraft/build/src/gfx /home/karl2883/programming/c++/minecraft/build/src/gfx/CMakeFiles/Gfx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/gfx/CMakeFiles/Gfx.dir/depend

