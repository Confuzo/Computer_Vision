# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6"

# Include any dependencies generated for this target.
include CMakeFiles/Visao.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Visao.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Visao.dir/flags.make

CMakeFiles/Visao.dir/src/noiseCancel.cpp.o: CMakeFiles/Visao.dir/flags.make
CMakeFiles/Visao.dir/src/noiseCancel.cpp.o: src/noiseCancel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Visao.dir/src/noiseCancel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Visao.dir/src/noiseCancel.cpp.o -c "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/src/noiseCancel.cpp"

CMakeFiles/Visao.dir/src/noiseCancel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Visao.dir/src/noiseCancel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/src/noiseCancel.cpp" > CMakeFiles/Visao.dir/src/noiseCancel.cpp.i

CMakeFiles/Visao.dir/src/noiseCancel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Visao.dir/src/noiseCancel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/src/noiseCancel.cpp" -o CMakeFiles/Visao.dir/src/noiseCancel.cpp.s

# Object files for target Visao
Visao_OBJECTS = \
"CMakeFiles/Visao.dir/src/noiseCancel.cpp.o"

# External object files for target Visao
Visao_EXTERNAL_OBJECTS =

Visao: CMakeFiles/Visao.dir/src/noiseCancel.cpp.o
Visao: CMakeFiles/Visao.dir/build.make
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_dnn.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_gapi.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_ml.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_objdetect.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_photo.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_stitching.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_video.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_calib3d.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_features2d.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_flann.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_highgui.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_videoio.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_imgcodecs.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_imgproc.so.4.0.1
Visao: /home/confuzo/Área\ de\ Trabalho/opencv-4.0.1/build/lib/libopencv_core.so.4.0.1
Visao: CMakeFiles/Visao.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Visao"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Visao.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Visao.dir/build: Visao

.PHONY : CMakeFiles/Visao.dir/build

CMakeFiles/Visao.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Visao.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Visao.dir/clean

CMakeFiles/Visao.dir/depend:
	cd "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6" "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6" "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6" "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6" "/home/confuzo/Área de Trabalho/disciplinas/visao_computacional/list_1/question_6/CMakeFiles/Visao.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Visao.dir/depend

