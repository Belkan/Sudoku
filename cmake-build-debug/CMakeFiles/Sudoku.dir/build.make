# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Adar\CLionProjects\Github\Sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sudoku.dir/flags.make

CMakeFiles/Sudoku.dir/main.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Sudoku.dir/main.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\main.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\main.c

CMakeFiles/Sudoku.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/main.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\main.c > CMakeFiles\Sudoku.dir\main.c.i

CMakeFiles/Sudoku.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/main.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\main.c -o CMakeFiles\Sudoku.dir\main.c.s

CMakeFiles/Sudoku.dir/Game.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Game.c.obj: ../Game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Sudoku.dir/Game.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\Game.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\Game.c

CMakeFiles/Sudoku.dir/Game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Game.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\Game.c > CMakeFiles\Sudoku.dir\Game.c.i

CMakeFiles/Sudoku.dir/Game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Game.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\Game.c -o CMakeFiles\Sudoku.dir\Game.c.s

CMakeFiles/Sudoku.dir/MainAux.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/MainAux.c.obj: ../MainAux.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Sudoku.dir/MainAux.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\MainAux.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\MainAux.c

CMakeFiles/Sudoku.dir/MainAux.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/MainAux.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\MainAux.c > CMakeFiles\Sudoku.dir\MainAux.c.i

CMakeFiles/Sudoku.dir/MainAux.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/MainAux.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\MainAux.c -o CMakeFiles\Sudoku.dir\MainAux.c.s

CMakeFiles/Sudoku.dir/Parser.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Parser.c.obj: ../Parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Sudoku.dir/Parser.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\Parser.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\Parser.c

CMakeFiles/Sudoku.dir/Parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Parser.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\Parser.c > CMakeFiles\Sudoku.dir\Parser.c.i

CMakeFiles/Sudoku.dir/Parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Parser.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\Parser.c -o CMakeFiles\Sudoku.dir\Parser.c.s

CMakeFiles/Sudoku.dir/Solver.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Solver.c.obj: ../Solver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Sudoku.dir/Solver.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\Solver.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\Solver.c

CMakeFiles/Sudoku.dir/Solver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Solver.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\Solver.c > CMakeFiles\Sudoku.dir\Solver.c.i

CMakeFiles/Sudoku.dir/Solver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Solver.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\Solver.c -o CMakeFiles\Sudoku.dir\Solver.c.s

CMakeFiles/Sudoku.dir/FileHandler.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/FileHandler.c.obj: ../FileHandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Sudoku.dir/FileHandler.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\FileHandler.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\FileHandler.c

CMakeFiles/Sudoku.dir/FileHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/FileHandler.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\FileHandler.c > CMakeFiles\Sudoku.dir\FileHandler.c.i

CMakeFiles/Sudoku.dir/FileHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/FileHandler.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\FileHandler.c -o CMakeFiles\Sudoku.dir\FileHandler.c.s

CMakeFiles/Sudoku.dir/ErrorHandler.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/ErrorHandler.c.obj: ../ErrorHandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Sudoku.dir/ErrorHandler.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\ErrorHandler.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\ErrorHandler.c

CMakeFiles/Sudoku.dir/ErrorHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/ErrorHandler.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\ErrorHandler.c > CMakeFiles\Sudoku.dir\ErrorHandler.c.i

CMakeFiles/Sudoku.dir/ErrorHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/ErrorHandler.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\ErrorHandler.c -o CMakeFiles\Sudoku.dir\ErrorHandler.c.s

CMakeFiles/Sudoku.dir/HistoryHandler.c.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/HistoryHandler.c.obj: ../HistoryHandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Sudoku.dir/HistoryHandler.c.obj"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Sudoku.dir\HistoryHandler.c.obj   -c C:\Users\Adar\CLionProjects\Github\Sudoku\HistoryHandler.c

CMakeFiles/Sudoku.dir/HistoryHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/HistoryHandler.c.i"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Adar\CLionProjects\Github\Sudoku\HistoryHandler.c > CMakeFiles\Sudoku.dir\HistoryHandler.c.i

CMakeFiles/Sudoku.dir/HistoryHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/HistoryHandler.c.s"
	C:\mingw\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Adar\CLionProjects\Github\Sudoku\HistoryHandler.c -o CMakeFiles\Sudoku.dir\HistoryHandler.c.s

# Object files for target Sudoku
Sudoku_OBJECTS = \
"CMakeFiles/Sudoku.dir/main.c.obj" \
"CMakeFiles/Sudoku.dir/Game.c.obj" \
"CMakeFiles/Sudoku.dir/MainAux.c.obj" \
"CMakeFiles/Sudoku.dir/Parser.c.obj" \
"CMakeFiles/Sudoku.dir/Solver.c.obj" \
"CMakeFiles/Sudoku.dir/FileHandler.c.obj" \
"CMakeFiles/Sudoku.dir/ErrorHandler.c.obj" \
"CMakeFiles/Sudoku.dir/HistoryHandler.c.obj"

# External object files for target Sudoku
Sudoku_EXTERNAL_OBJECTS =

Sudoku.exe: CMakeFiles/Sudoku.dir/main.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/Game.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/MainAux.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/Parser.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/Solver.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/FileHandler.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/ErrorHandler.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/HistoryHandler.c.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/build.make
Sudoku.exe: CMakeFiles/Sudoku.dir/linklibs.rsp
Sudoku.exe: CMakeFiles/Sudoku.dir/objects1.rsp
Sudoku.exe: CMakeFiles/Sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable Sudoku.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Sudoku.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sudoku.dir/build: Sudoku.exe

.PHONY : CMakeFiles/Sudoku.dir/build

CMakeFiles/Sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Sudoku.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Sudoku.dir/clean

CMakeFiles/Sudoku.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adar\CLionProjects\Github\Sudoku C:\Users\Adar\CLionProjects\Github\Sudoku C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug C:\Users\Adar\CLionProjects\Github\Sudoku\cmake-build-debug\CMakeFiles\Sudoku.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sudoku.dir/depend

