# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fbland/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fbland/Project

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fbland/Project/CMakeFiles /home/fbland/Project/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fbland/Project/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bin/test

# Build rule for target.
bin/test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 bin/test
.PHONY : bin/test

# fast build rule for target.
bin/test/fast:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/build
.PHONY : bin/test/fast

src/HashTable.o: src/HashTable.cpp.o
.PHONY : src/HashTable.o

# target to build an object file
src/HashTable.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/HashTable.cpp.o
.PHONY : src/HashTable.cpp.o

src/HashTable.i: src/HashTable.cpp.i
.PHONY : src/HashTable.i

# target to preprocess a source file
src/HashTable.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/HashTable.cpp.i
.PHONY : src/HashTable.cpp.i

src/HashTable.s: src/HashTable.cpp.s
.PHONY : src/HashTable.s

# target to generate assembly for a file
src/HashTable.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/HashTable.cpp.s
.PHONY : src/HashTable.cpp.s

src/MPIType.o: src/MPIType.cpp.o
.PHONY : src/MPIType.o

# target to build an object file
src/MPIType.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/MPIType.cpp.o
.PHONY : src/MPIType.cpp.o

src/MPIType.i: src/MPIType.cpp.i
.PHONY : src/MPIType.i

# target to preprocess a source file
src/MPIType.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/MPIType.cpp.i
.PHONY : src/MPIType.cpp.i

src/MPIType.s: src/MPIType.cpp.s
.PHONY : src/MPIType.s

# target to generate assembly for a file
src/MPIType.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/MPIType.cpp.s
.PHONY : src/MPIType.cpp.s

src/Mapper.o: src/Mapper.cpp.o
.PHONY : src/Mapper.o

# target to build an object file
src/Mapper.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Mapper.cpp.o
.PHONY : src/Mapper.cpp.o

src/Mapper.i: src/Mapper.cpp.i
.PHONY : src/Mapper.i

# target to preprocess a source file
src/Mapper.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Mapper.cpp.i
.PHONY : src/Mapper.cpp.i

src/Mapper.s: src/Mapper.cpp.s
.PHONY : src/Mapper.s

# target to generate assembly for a file
src/Mapper.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Mapper.cpp.s
.PHONY : src/Mapper.cpp.s

src/Reader.o: src/Reader.cpp.o
.PHONY : src/Reader.o

# target to build an object file
src/Reader.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reader.cpp.o
.PHONY : src/Reader.cpp.o

src/Reader.i: src/Reader.cpp.i
.PHONY : src/Reader.i

# target to preprocess a source file
src/Reader.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reader.cpp.i
.PHONY : src/Reader.cpp.i

src/Reader.s: src/Reader.cpp.s
.PHONY : src/Reader.s

# target to generate assembly for a file
src/Reader.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reader.cpp.s
.PHONY : src/Reader.cpp.s

src/Reducer.o: src/Reducer.cpp.o
.PHONY : src/Reducer.o

# target to build an object file
src/Reducer.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reducer.cpp.o
.PHONY : src/Reducer.cpp.o

src/Reducer.i: src/Reducer.cpp.i
.PHONY : src/Reducer.i

# target to preprocess a source file
src/Reducer.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reducer.cpp.i
.PHONY : src/Reducer.cpp.i

src/Reducer.s: src/Reducer.cpp.s
.PHONY : src/Reducer.s

# target to generate assembly for a file
src/Reducer.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/Reducer.cpp.s
.PHONY : src/Reducer.cpp.s

src/main_reader.o: src/main_reader.cpp.o
.PHONY : src/main_reader.o

# target to build an object file
src/main_reader.cpp.o:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/main_reader.cpp.o
.PHONY : src/main_reader.cpp.o

src/main_reader.i: src/main_reader.cpp.i
.PHONY : src/main_reader.i

# target to preprocess a source file
src/main_reader.cpp.i:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/main_reader.cpp.i
.PHONY : src/main_reader.cpp.i

src/main_reader.s: src/main_reader.cpp.s
.PHONY : src/main_reader.s

# target to generate assembly for a file
src/main_reader.cpp.s:
	$(MAKE) -f CMakeFiles/bin/test.dir/build.make CMakeFiles/bin/test.dir/src/main_reader.cpp.s
.PHONY : src/main_reader.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... bin/test"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/HashTable.o"
	@echo "... src/HashTable.i"
	@echo "... src/HashTable.s"
	@echo "... src/MPIType.o"
	@echo "... src/MPIType.i"
	@echo "... src/MPIType.s"
	@echo "... src/Mapper.o"
	@echo "... src/Mapper.i"
	@echo "... src/Mapper.s"
	@echo "... src/Reader.o"
	@echo "... src/Reader.i"
	@echo "... src/Reader.s"
	@echo "... src/Reducer.o"
	@echo "... src/Reducer.i"
	@echo "... src/Reducer.s"
	@echo "... src/main_reader.o"
	@echo "... src/main_reader.i"
	@echo "... src/main_reader.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

