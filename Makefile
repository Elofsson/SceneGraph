# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(CMAKE_COMMAND) -E cmake_progress_start /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master/CMakeFiles /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master/examples/lab1//CMakeFiles/progress.marks
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 examples/lab1/all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 examples/lab1/clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 examples/lab1/preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 examples/lab1/preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

# Convenience name for target.
examples/lab1/CMakeFiles/lab1.dir/rule:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 examples/lab1/CMakeFiles/lab1.dir/rule
.PHONY : examples/lab1/CMakeFiles/lab1.dir/rule

# Convenience name for target.
lab1: examples/lab1/CMakeFiles/lab1.dir/rule

.PHONY : lab1

# fast build rule for target.
lab1/fast:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/build
.PHONY : lab1/fast

Application.o: Application.cpp.o

.PHONY : Application.o

# target to build an object file
Application.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Application.cpp.o
.PHONY : Application.cpp.o

Application.i: Application.cpp.i

.PHONY : Application.i

# target to preprocess a source file
Application.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Application.cpp.i
.PHONY : Application.cpp.i

Application.s: Application.cpp.s

.PHONY : Application.s

# target to generate assembly for a file
Application.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Application.cpp.s
.PHONY : Application.cpp.s

Camera.o: Camera.cpp.o

.PHONY : Camera.o

# target to build an object file
Camera.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Camera.cpp.o
.PHONY : Camera.cpp.o

Camera.i: Camera.cpp.i

.PHONY : Camera.i

# target to preprocess a source file
Camera.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Camera.cpp.i
.PHONY : Camera.cpp.i

Camera.s: Camera.cpp.s

.PHONY : Camera.s

# target to generate assembly for a file
Camera.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Camera.cpp.s
.PHONY : Camera.cpp.s

Debug.o: Debug.cpp.o

.PHONY : Debug.o

# target to build an object file
Debug.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Debug.cpp.o
.PHONY : Debug.cpp.o

Debug.i: Debug.cpp.i

.PHONY : Debug.i

# target to preprocess a source file
Debug.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Debug.cpp.i
.PHONY : Debug.cpp.i

Debug.s: Debug.cpp.s

.PHONY : Debug.s

# target to generate assembly for a file
Debug.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Debug.cpp.s
.PHONY : Debug.cpp.s

DotVisitor.o: DotVisitor.cpp.o

.PHONY : DotVisitor.o

# target to build an object file
DotVisitor.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/DotVisitor.cpp.o
.PHONY : DotVisitor.cpp.o

DotVisitor.i: DotVisitor.cpp.i

.PHONY : DotVisitor.i

# target to preprocess a source file
DotVisitor.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/DotVisitor.cpp.i
.PHONY : DotVisitor.cpp.i

DotVisitor.s: DotVisitor.cpp.s

.PHONY : DotVisitor.s

# target to generate assembly for a file
DotVisitor.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/DotVisitor.cpp.s
.PHONY : DotVisitor.cpp.s

FPSCounter.o: FPSCounter.cpp.o

.PHONY : FPSCounter.o

# target to build an object file
FPSCounter.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/FPSCounter.cpp.o
.PHONY : FPSCounter.cpp.o

FPSCounter.i: FPSCounter.cpp.i

.PHONY : FPSCounter.i

# target to preprocess a source file
FPSCounter.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/FPSCounter.cpp.i
.PHONY : FPSCounter.cpp.i

FPSCounter.s: FPSCounter.cpp.s

.PHONY : FPSCounter.s

# target to generate assembly for a file
FPSCounter.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/FPSCounter.cpp.s
.PHONY : FPSCounter.cpp.s

Geometry.o: Geometry.cpp.o

.PHONY : Geometry.o

# target to build an object file
Geometry.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Geometry.cpp.o
.PHONY : Geometry.cpp.o

Geometry.i: Geometry.cpp.i

.PHONY : Geometry.i

# target to preprocess a source file
Geometry.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Geometry.cpp.i
.PHONY : Geometry.cpp.i

Geometry.s: Geometry.cpp.s

.PHONY : Geometry.s

# target to generate assembly for a file
Geometry.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Geometry.cpp.s
.PHONY : Geometry.cpp.s

Group.o: Group.cpp.o

.PHONY : Group.o

# target to build an object file
Group.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Group.cpp.o
.PHONY : Group.cpp.o

Group.i: Group.cpp.i

.PHONY : Group.i

# target to preprocess a source file
Group.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Group.cpp.i
.PHONY : Group.cpp.i

Group.s: Group.cpp.s

.PHONY : Group.s

# target to generate assembly for a file
Group.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Group.cpp.s
.PHONY : Group.cpp.s

InitVisitor.o: InitVisitor.cpp.o

.PHONY : InitVisitor.o

# target to build an object file
InitVisitor.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/InitVisitor.cpp.o
.PHONY : InitVisitor.cpp.o

InitVisitor.i: InitVisitor.cpp.i

.PHONY : InitVisitor.i

# target to preprocess a source file
InitVisitor.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/InitVisitor.cpp.i
.PHONY : InitVisitor.cpp.i

InitVisitor.s: InitVisitor.cpp.s

.PHONY : InitVisitor.s

# target to generate assembly for a file
InitVisitor.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/InitVisitor.cpp.s
.PHONY : InitVisitor.cpp.s

Light.o: Light.cpp.o

.PHONY : Light.o

# target to build an object file
Light.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Light.cpp.o
.PHONY : Light.cpp.o

Light.i: Light.cpp.i

.PHONY : Light.i

# target to preprocess a source file
Light.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Light.cpp.i
.PHONY : Light.cpp.i

Light.s: Light.cpp.s

.PHONY : Light.s

# target to generate assembly for a file
Light.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Light.cpp.s
.PHONY : Light.cpp.s

Loader.o: Loader.cpp.o

.PHONY : Loader.o

# target to build an object file
Loader.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Loader.cpp.o
.PHONY : Loader.cpp.o

Loader.i: Loader.cpp.i

.PHONY : Loader.i

# target to preprocess a source file
Loader.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Loader.cpp.i
.PHONY : Loader.cpp.i

Loader.s: Loader.cpp.s

.PHONY : Loader.s

# target to generate assembly for a file
Loader.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Loader.cpp.s
.PHONY : Loader.cpp.s

LodCallback.o: LodCallback.cpp.o

.PHONY : LodCallback.o

# target to build an object file
LodCallback.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/LodCallback.cpp.o
.PHONY : LodCallback.cpp.o

LodCallback.i: LodCallback.cpp.i

.PHONY : LodCallback.i

# target to preprocess a source file
LodCallback.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/LodCallback.cpp.i
.PHONY : LodCallback.cpp.i

LodCallback.s: LodCallback.cpp.s

.PHONY : LodCallback.s

# target to generate assembly for a file
LodCallback.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/LodCallback.cpp.s
.PHONY : LodCallback.cpp.s

Material.o: Material.cpp.o

.PHONY : Material.o

# target to build an object file
Material.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Material.cpp.o
.PHONY : Material.cpp.o

Material.i: Material.cpp.i

.PHONY : Material.i

# target to preprocess a source file
Material.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Material.cpp.i
.PHONY : Material.cpp.i

Material.s: Material.cpp.s

.PHONY : Material.s

# target to generate assembly for a file
Material.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Material.cpp.s
.PHONY : Material.cpp.s

Mesh.o: Mesh.cpp.o

.PHONY : Mesh.o

# target to build an object file
Mesh.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Mesh.cpp.o
.PHONY : Mesh.cpp.o

Mesh.i: Mesh.cpp.i

.PHONY : Mesh.i

# target to preprocess a source file
Mesh.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Mesh.cpp.i
.PHONY : Mesh.cpp.i

Mesh.s: Mesh.cpp.s

.PHONY : Mesh.s

# target to generate assembly for a file
Mesh.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Mesh.cpp.s
.PHONY : Mesh.cpp.s

MovingLightCallback.o: MovingLightCallback.cpp.o

.PHONY : MovingLightCallback.o

# target to build an object file
MovingLightCallback.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/MovingLightCallback.cpp.o
.PHONY : MovingLightCallback.cpp.o

MovingLightCallback.i: MovingLightCallback.cpp.i

.PHONY : MovingLightCallback.i

# target to preprocess a source file
MovingLightCallback.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/MovingLightCallback.cpp.i
.PHONY : MovingLightCallback.cpp.i

MovingLightCallback.s: MovingLightCallback.cpp.s

.PHONY : MovingLightCallback.s

# target to generate assembly for a file
MovingLightCallback.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/MovingLightCallback.cpp.s
.PHONY : MovingLightCallback.cpp.s

Node.o: Node.cpp.o

.PHONY : Node.o

# target to build an object file
Node.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Node.cpp.o
.PHONY : Node.cpp.o

Node.i: Node.cpp.i

.PHONY : Node.i

# target to preprocess a source file
Node.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Node.cpp.i
.PHONY : Node.cpp.i

Node.s: Node.cpp.s

.PHONY : Node.s

# target to generate assembly for a file
Node.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Node.cpp.s
.PHONY : Node.cpp.s

NodeVisitor.o: NodeVisitor.cpp.o

.PHONY : NodeVisitor.o

# target to build an object file
NodeVisitor.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/NodeVisitor.cpp.o
.PHONY : NodeVisitor.cpp.o

NodeVisitor.i: NodeVisitor.cpp.i

.PHONY : NodeVisitor.i

# target to preprocess a source file
NodeVisitor.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/NodeVisitor.cpp.i
.PHONY : NodeVisitor.cpp.i

NodeVisitor.s: NodeVisitor.cpp.s

.PHONY : NodeVisitor.s

# target to generate assembly for a file
NodeVisitor.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/NodeVisitor.cpp.s
.PHONY : NodeVisitor.cpp.s

RenderVisitor.o: RenderVisitor.cpp.o

.PHONY : RenderVisitor.o

# target to build an object file
RenderVisitor.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RenderVisitor.cpp.o
.PHONY : RenderVisitor.cpp.o

RenderVisitor.i: RenderVisitor.cpp.i

.PHONY : RenderVisitor.i

# target to preprocess a source file
RenderVisitor.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RenderVisitor.cpp.i
.PHONY : RenderVisitor.cpp.i

RenderVisitor.s: RenderVisitor.cpp.s

.PHONY : RenderVisitor.s

# target to generate assembly for a file
RenderVisitor.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RenderVisitor.cpp.s
.PHONY : RenderVisitor.cpp.s

RotateCallback.o: RotateCallback.cpp.o

.PHONY : RotateCallback.o

# target to build an object file
RotateCallback.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RotateCallback.cpp.o
.PHONY : RotateCallback.cpp.o

RotateCallback.i: RotateCallback.cpp.i

.PHONY : RotateCallback.i

# target to preprocess a source file
RotateCallback.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RotateCallback.cpp.i
.PHONY : RotateCallback.cpp.i

RotateCallback.s: RotateCallback.cpp.s

.PHONY : RotateCallback.s

# target to generate assembly for a file
RotateCallback.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/RotateCallback.cpp.s
.PHONY : RotateCallback.cpp.s

Scene.o: Scene.cpp.o

.PHONY : Scene.o

# target to build an object file
Scene.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Scene.cpp.o
.PHONY : Scene.cpp.o

Scene.i: Scene.cpp.i

.PHONY : Scene.i

# target to preprocess a source file
Scene.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Scene.cpp.i
.PHONY : Scene.cpp.i

Scene.s: Scene.cpp.s

.PHONY : Scene.s

# target to generate assembly for a file
Scene.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Scene.cpp.s
.PHONY : Scene.cpp.s

State.o: State.cpp.o

.PHONY : State.o

# target to build an object file
State.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/State.cpp.o
.PHONY : State.cpp.o

State.i: State.cpp.i

.PHONY : State.i

# target to preprocess a source file
State.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/State.cpp.i
.PHONY : State.cpp.i

State.s: State.cpp.s

.PHONY : State.s

# target to generate assembly for a file
State.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/State.cpp.s
.PHONY : State.cpp.s

Texture.o: Texture.cpp.o

.PHONY : Texture.o

# target to build an object file
Texture.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Texture.cpp.o
.PHONY : Texture.cpp.o

Texture.i: Texture.cpp.i

.PHONY : Texture.i

# target to preprocess a source file
Texture.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Texture.cpp.i
.PHONY : Texture.cpp.i

Texture.s: Texture.cpp.s

.PHONY : Texture.s

# target to generate assembly for a file
Texture.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Texture.cpp.s
.PHONY : Texture.cpp.s

Transform.o: Transform.cpp.o

.PHONY : Transform.o

# target to build an object file
Transform.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Transform.cpp.o
.PHONY : Transform.cpp.o

Transform.i: Transform.cpp.i

.PHONY : Transform.i

# target to preprocess a source file
Transform.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Transform.cpp.i
.PHONY : Transform.cpp.i

Transform.s: Transform.cpp.s

.PHONY : Transform.s

# target to generate assembly for a file
Transform.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/Transform.cpp.s
.PHONY : Transform.cpp.s

UpdateVisitor.o: UpdateVisitor.cpp.o

.PHONY : UpdateVisitor.o

# target to build an object file
UpdateVisitor.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/UpdateVisitor.cpp.o
.PHONY : UpdateVisitor.cpp.o

UpdateVisitor.i: UpdateVisitor.cpp.i

.PHONY : UpdateVisitor.i

# target to preprocess a source file
UpdateVisitor.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/UpdateVisitor.cpp.i
.PHONY : UpdateVisitor.cpp.i

UpdateVisitor.s: UpdateVisitor.cpp.s

.PHONY : UpdateVisitor.s

# target to generate assembly for a file
UpdateVisitor.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/UpdateVisitor.cpp.s
.PHONY : UpdateVisitor.cpp.s

VectorUtils.o: VectorUtils.cpp.o

.PHONY : VectorUtils.o

# target to build an object file
VectorUtils.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/VectorUtils.cpp.o
.PHONY : VectorUtils.cpp.o

VectorUtils.i: VectorUtils.cpp.i

.PHONY : VectorUtils.i

# target to preprocess a source file
VectorUtils.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/VectorUtils.cpp.i
.PHONY : VectorUtils.cpp.i

VectorUtils.s: VectorUtils.cpp.s

.PHONY : VectorUtils.s

# target to generate assembly for a file
VectorUtils.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/VectorUtils.cpp.s
.PHONY : VectorUtils.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/main.cpp.s
.PHONY : main.cpp.s

shader_utils.o: shader_utils.cpp.o

.PHONY : shader_utils.o

# target to build an object file
shader_utils.cpp.o:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/shader_utils.cpp.o
.PHONY : shader_utils.cpp.o

shader_utils.i: shader_utils.cpp.i

.PHONY : shader_utils.i

# target to preprocess a source file
shader_utils.cpp.i:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/shader_utils.cpp.i
.PHONY : shader_utils.cpp.i

shader_utils.s: shader_utils.cpp.s

.PHONY : shader_utils.s

# target to generate assembly for a file
shader_utils.cpp.s:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(MAKE) $(MAKESILENT) -f examples/lab1/CMakeFiles/lab1.dir/build.make examples/lab1/CMakeFiles/lab1.dir/shader_utils.cpp.s
.PHONY : shader_utils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... lab1"
	@echo "... Application.o"
	@echo "... Application.i"
	@echo "... Application.s"
	@echo "... Camera.o"
	@echo "... Camera.i"
	@echo "... Camera.s"
	@echo "... Debug.o"
	@echo "... Debug.i"
	@echo "... Debug.s"
	@echo "... DotVisitor.o"
	@echo "... DotVisitor.i"
	@echo "... DotVisitor.s"
	@echo "... FPSCounter.o"
	@echo "... FPSCounter.i"
	@echo "... FPSCounter.s"
	@echo "... Geometry.o"
	@echo "... Geometry.i"
	@echo "... Geometry.s"
	@echo "... Group.o"
	@echo "... Group.i"
	@echo "... Group.s"
	@echo "... InitVisitor.o"
	@echo "... InitVisitor.i"
	@echo "... InitVisitor.s"
	@echo "... Light.o"
	@echo "... Light.i"
	@echo "... Light.s"
	@echo "... Loader.o"
	@echo "... Loader.i"
	@echo "... Loader.s"
	@echo "... LodCallback.o"
	@echo "... LodCallback.i"
	@echo "... LodCallback.s"
	@echo "... Material.o"
	@echo "... Material.i"
	@echo "... Material.s"
	@echo "... Mesh.o"
	@echo "... Mesh.i"
	@echo "... Mesh.s"
	@echo "... MovingLightCallback.o"
	@echo "... MovingLightCallback.i"
	@echo "... MovingLightCallback.s"
	@echo "... Node.o"
	@echo "... Node.i"
	@echo "... Node.s"
	@echo "... NodeVisitor.o"
	@echo "... NodeVisitor.i"
	@echo "... NodeVisitor.s"
	@echo "... RenderVisitor.o"
	@echo "... RenderVisitor.i"
	@echo "... RenderVisitor.s"
	@echo "... RotateCallback.o"
	@echo "... RotateCallback.i"
	@echo "... RotateCallback.s"
	@echo "... Scene.o"
	@echo "... Scene.i"
	@echo "... Scene.s"
	@echo "... State.o"
	@echo "... State.i"
	@echo "... State.s"
	@echo "... Texture.o"
	@echo "... Texture.i"
	@echo "... Texture.s"
	@echo "... Transform.o"
	@echo "... Transform.i"
	@echo "... Transform.s"
	@echo "... UpdateVisitor.o"
	@echo "... UpdateVisitor.i"
	@echo "... UpdateVisitor.s"
	@echo "... VectorUtils.o"
	@echo "... VectorUtils.i"
	@echo "... VectorUtils.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... shader_utils.o"
	@echo "... shader_utils.i"
	@echo "... shader_utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	cd /home/dv19/dv19eft/workspace/AvanceradDatorgrafik/5dv180-master && $(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

