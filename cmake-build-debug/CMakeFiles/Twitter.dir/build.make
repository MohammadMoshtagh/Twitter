# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Twitter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Twitter\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Twitter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Twitter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Twitter.dir/flags.make

CMakeFiles/Twitter.dir/main.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Twitter.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\main.c.obj   -c D:\Twitter\main.c

CMakeFiles/Twitter.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\main.c > CMakeFiles\Twitter.dir\main.c.i

CMakeFiles/Twitter.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\main.c -o CMakeFiles\Twitter.dir\main.c.s

CMakeFiles/Twitter.dir/Register.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/Register.c.obj: ../Register.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Twitter.dir/Register.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\Register.c.obj   -c D:\Twitter\Register.c

CMakeFiles/Twitter.dir/Register.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/Register.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\Register.c > CMakeFiles\Twitter.dir\Register.c.i

CMakeFiles/Twitter.dir/Register.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/Register.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\Register.c -o CMakeFiles\Twitter.dir\Register.c.s

CMakeFiles/Twitter.dir/Client.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/Client.c.obj: ../Client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Twitter.dir/Client.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\Client.c.obj   -c D:\Twitter\Client.c

CMakeFiles/Twitter.dir/Client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/Client.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\Client.c > CMakeFiles\Twitter.dir\Client.c.i

CMakeFiles/Twitter.dir/Client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/Client.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\Client.c -o CMakeFiles\Twitter.dir\Client.c.s

CMakeFiles/Twitter.dir/cJSON.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/cJSON.c.obj: ../cJSON.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Twitter.dir/cJSON.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\cJSON.c.obj   -c D:\Twitter\cJSON.c

CMakeFiles/Twitter.dir/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/cJSON.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\cJSON.c > CMakeFiles\Twitter.dir\cJSON.c.i

CMakeFiles/Twitter.dir/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/cJSON.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\cJSON.c -o CMakeFiles\Twitter.dir\cJSON.c.s

CMakeFiles/Twitter.dir/json.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/json.c.obj: ../json.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Twitter.dir/json.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\json.c.obj   -c D:\Twitter\json.c

CMakeFiles/Twitter.dir/json.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/json.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\json.c > CMakeFiles\Twitter.dir\json.c.i

CMakeFiles/Twitter.dir/json.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/json.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\json.c -o CMakeFiles\Twitter.dir\json.c.s

CMakeFiles/Twitter.dir/Main_menu.c.obj: CMakeFiles/Twitter.dir/flags.make
CMakeFiles/Twitter.dir/Main_menu.c.obj: ../Main_menu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Twitter.dir/Main_menu.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Twitter.dir\Main_menu.c.obj   -c D:\Twitter\Main_menu.c

CMakeFiles/Twitter.dir/Main_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Twitter.dir/Main_menu.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Twitter\Main_menu.c > CMakeFiles\Twitter.dir\Main_menu.c.i

CMakeFiles/Twitter.dir/Main_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Twitter.dir/Main_menu.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Twitter\Main_menu.c -o CMakeFiles\Twitter.dir\Main_menu.c.s

# Object files for target Twitter
Twitter_OBJECTS = \
"CMakeFiles/Twitter.dir/main.c.obj" \
"CMakeFiles/Twitter.dir/Register.c.obj" \
"CMakeFiles/Twitter.dir/Client.c.obj" \
"CMakeFiles/Twitter.dir/cJSON.c.obj" \
"CMakeFiles/Twitter.dir/json.c.obj" \
"CMakeFiles/Twitter.dir/Main_menu.c.obj"

# External object files for target Twitter
Twitter_EXTERNAL_OBJECTS =

Twitter.exe: CMakeFiles/Twitter.dir/main.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/Register.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/Client.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/cJSON.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/json.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/Main_menu.c.obj
Twitter.exe: CMakeFiles/Twitter.dir/build.make
Twitter.exe: CMakeFiles/Twitter.dir/linklibs.rsp
Twitter.exe: CMakeFiles/Twitter.dir/objects1.rsp
Twitter.exe: CMakeFiles/Twitter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Twitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Twitter.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Twitter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Twitter.dir/build: Twitter.exe

.PHONY : CMakeFiles/Twitter.dir/build

CMakeFiles/Twitter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Twitter.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Twitter.dir/clean

CMakeFiles/Twitter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Twitter D:\Twitter D:\Twitter\cmake-build-debug D:\Twitter\cmake-build-debug D:\Twitter\cmake-build-debug\CMakeFiles\Twitter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Twitter.dir/depend

