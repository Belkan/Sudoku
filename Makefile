# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Adar\CLionProjects\Github\Sudoko

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Adar\CLionProjects\Github\Sudoko\cmake-build-debug

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E echo "No interactive CMake dialog available."
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\Adar\CLionProjects\Github\Sudoko\cmake-build-debug\CMakeFiles C:\Users\Adar\CLionProjects\Github\Sudoko\cmake-build-debug\CMakeFiles\progress.marks
	$(MAKE) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\Adar\CLionProjects\Github\Sudoko\cmake-build-debug\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Sudoku

# Build rule for target.
Sudoku: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 Sudoku
.PHONY : Sudoku

# fast build rule for target.
Sudoku/fast:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/build
.PHONY : Sudoku/fast

Game/Game.obj: Game/Game.c.obj

.PHONY : Game/Game.obj

# target to build an object file
Game/Game.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/Game.c.obj
.PHONY : Game/Game.c.obj

Game/Game.i: Game/Game.c.i

.PHONY : Game/Game.i

# target to preprocess a source file
Game/Game.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/Game.c.i
.PHONY : Game/Game.c.i

Game/Game.s: Game/Game.c.s

.PHONY : Game/Game.s

# target to generate assembly for a file
Game/Game.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/Game.c.s
.PHONY : Game/Game.c.s

Game/GameUnitTest.obj: Game/GameUnitTest.c.obj

.PHONY : Game/GameUnitTest.obj

# target to build an object file
Game/GameUnitTest.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/GameUnitTest.c.obj
.PHONY : Game/GameUnitTest.c.obj

Game/GameUnitTest.i: Game/GameUnitTest.c.i

.PHONY : Game/GameUnitTest.i

# target to preprocess a source file
Game/GameUnitTest.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/GameUnitTest.c.i
.PHONY : Game/GameUnitTest.c.i

Game/GameUnitTest.s: Game/GameUnitTest.c.s

.PHONY : Game/GameUnitTest.s

# target to generate assembly for a file
Game/GameUnitTest.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Game/GameUnitTest.c.s
.PHONY : Game/GameUnitTest.c.s

MainAux/MainAux.obj: MainAux/MainAux.c.obj

.PHONY : MainAux/MainAux.obj

# target to build an object file
MainAux/MainAux.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAux.c.obj
.PHONY : MainAux/MainAux.c.obj

MainAux/MainAux.i: MainAux/MainAux.c.i

.PHONY : MainAux/MainAux.i

# target to preprocess a source file
MainAux/MainAux.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAux.c.i
.PHONY : MainAux/MainAux.c.i

MainAux/MainAux.s: MainAux/MainAux.c.s

.PHONY : MainAux/MainAux.s

# target to generate assembly for a file
MainAux/MainAux.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAux.c.s
.PHONY : MainAux/MainAux.c.s

MainAux/MainAuxUnitTest.obj: MainAux/MainAuxUnitTest.c.obj

.PHONY : MainAux/MainAuxUnitTest.obj

# target to build an object file
MainAux/MainAuxUnitTest.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAuxUnitTest.c.obj
.PHONY : MainAux/MainAuxUnitTest.c.obj

MainAux/MainAuxUnitTest.i: MainAux/MainAuxUnitTest.c.i

.PHONY : MainAux/MainAuxUnitTest.i

# target to preprocess a source file
MainAux/MainAuxUnitTest.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAuxUnitTest.c.i
.PHONY : MainAux/MainAuxUnitTest.c.i

MainAux/MainAuxUnitTest.s: MainAux/MainAuxUnitTest.c.s

.PHONY : MainAux/MainAuxUnitTest.s

# target to generate assembly for a file
MainAux/MainAuxUnitTest.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/MainAux/MainAuxUnitTest.c.s
.PHONY : MainAux/MainAuxUnitTest.c.s

Parser/Parser.obj: Parser/Parser.c.obj

.PHONY : Parser/Parser.obj

# target to build an object file
Parser/Parser.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/Parser.c.obj
.PHONY : Parser/Parser.c.obj

Parser/Parser.i: Parser/Parser.c.i

.PHONY : Parser/Parser.i

# target to preprocess a source file
Parser/Parser.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/Parser.c.i
.PHONY : Parser/Parser.c.i

Parser/Parser.s: Parser/Parser.c.s

.PHONY : Parser/Parser.s

# target to generate assembly for a file
Parser/Parser.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/Parser.c.s
.PHONY : Parser/Parser.c.s

Parser/ParserUnitTest.obj: Parser/ParserUnitTest.c.obj

.PHONY : Parser/ParserUnitTest.obj

# target to build an object file
Parser/ParserUnitTest.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/ParserUnitTest.c.obj
.PHONY : Parser/ParserUnitTest.c.obj

Parser/ParserUnitTest.i: Parser/ParserUnitTest.c.i

.PHONY : Parser/ParserUnitTest.i

# target to preprocess a source file
Parser/ParserUnitTest.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/ParserUnitTest.c.i
.PHONY : Parser/ParserUnitTest.c.i

Parser/ParserUnitTest.s: Parser/ParserUnitTest.c.s

.PHONY : Parser/ParserUnitTest.s

# target to generate assembly for a file
Parser/ParserUnitTest.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Parser/ParserUnitTest.c.s
.PHONY : Parser/ParserUnitTest.c.s

Solver/Solver.obj: Solver/Solver.c.obj

.PHONY : Solver/Solver.obj

# target to build an object file
Solver/Solver.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/Solver.c.obj
.PHONY : Solver/Solver.c.obj

Solver/Solver.i: Solver/Solver.c.i

.PHONY : Solver/Solver.i

# target to preprocess a source file
Solver/Solver.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/Solver.c.i
.PHONY : Solver/Solver.c.i

Solver/Solver.s: Solver/Solver.c.s

.PHONY : Solver/Solver.s

# target to generate assembly for a file
Solver/Solver.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/Solver.c.s
.PHONY : Solver/Solver.c.s

Solver/SolverUnitTest.obj: Solver/SolverUnitTest.c.obj

.PHONY : Solver/SolverUnitTest.obj

# target to build an object file
Solver/SolverUnitTest.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/SolverUnitTest.c.obj
.PHONY : Solver/SolverUnitTest.c.obj

Solver/SolverUnitTest.i: Solver/SolverUnitTest.c.i

.PHONY : Solver/SolverUnitTest.i

# target to preprocess a source file
Solver/SolverUnitTest.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/SolverUnitTest.c.i
.PHONY : Solver/SolverUnitTest.c.i

Solver/SolverUnitTest.s: Solver/SolverUnitTest.c.s

.PHONY : Solver/SolverUnitTest.s

# target to generate assembly for a file
Solver/SolverUnitTest.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/Solver/SolverUnitTest.c.s
.PHONY : Solver/SolverUnitTest.c.s

main.obj: main.c.obj

.PHONY : main.obj

# target to build an object file
main.c.obj:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/main.c.obj
.PHONY : main.c.obj

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles\Sudoku.dir\build.make CMakeFiles/Sudoku.dir/main.c.s
.PHONY : main.c.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... Sudoku
	@echo ... rebuild_cache
	@echo ... Game/Game.obj
	@echo ... Game/Game.i
	@echo ... Game/Game.s
	@echo ... Game/GameUnitTest.obj
	@echo ... Game/GameUnitTest.i
	@echo ... Game/GameUnitTest.s
	@echo ... MainAux/MainAux.obj
	@echo ... MainAux/MainAux.i
	@echo ... MainAux/MainAux.s
	@echo ... MainAux/MainAuxUnitTest.obj
	@echo ... MainAux/MainAuxUnitTest.i
	@echo ... MainAux/MainAuxUnitTest.s
	@echo ... Parser/Parser.obj
	@echo ... Parser/Parser.i
	@echo ... Parser/Parser.s
	@echo ... Parser/ParserUnitTest.obj
	@echo ... Parser/ParserUnitTest.i
	@echo ... Parser/ParserUnitTest.s
	@echo ... Solver/Solver.obj
	@echo ... Solver/Solver.i
	@echo ... Solver/Solver.s
	@echo ... Solver/SolverUnitTest.obj
	@echo ... Solver/SolverUnitTest.i
	@echo ... Solver/SolverUnitTest.s
	@echo ... main.obj
	@echo ... main.i
	@echo ... main.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system