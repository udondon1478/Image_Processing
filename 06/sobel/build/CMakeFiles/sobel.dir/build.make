# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/x22004xx/src/imgProc/第6回/sobel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/x22004xx/src/imgProc/第6回/sobel/build

# Include any dependencies generated for this target.
include CMakeFiles/sobel.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sobel.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sobel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sobel.dir/flags.make

CMakeFiles/sobel.dir/main.cpp.o: CMakeFiles/sobel.dir/flags.make
CMakeFiles/sobel.dir/main.cpp.o: /Users/x22004xx/src/imgProc/第6回/sobel/main.cpp
CMakeFiles/sobel.dir/main.cpp.o: CMakeFiles/sobel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/x22004xx/src/imgProc/第6回/sobel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sobel.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sobel.dir/main.cpp.o -MF CMakeFiles/sobel.dir/main.cpp.o.d -o CMakeFiles/sobel.dir/main.cpp.o -c /Users/x22004xx/src/imgProc/第6回/sobel/main.cpp

CMakeFiles/sobel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sobel.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/x22004xx/src/imgProc/第6回/sobel/main.cpp > CMakeFiles/sobel.dir/main.cpp.i

CMakeFiles/sobel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sobel.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/x22004xx/src/imgProc/第6回/sobel/main.cpp -o CMakeFiles/sobel.dir/main.cpp.s

# Object files for target sobel
sobel_OBJECTS = \
"CMakeFiles/sobel.dir/main.cpp.o"

# External object files for target sobel
sobel_EXTERNAL_OBJECTS =

sobel: CMakeFiles/sobel.dir/main.cpp.o
sobel: CMakeFiles/sobel.dir/build.make
sobel: /opt/homebrew/lib/libopencv_gapi.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_stitching.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_alphamat.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_aruco.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_barcode.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_bgsegm.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_bioinspired.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_ccalib.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_dnn_objdetect.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_dnn_superres.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_dpm.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_face.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_freetype.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_fuzzy.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_hfs.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_img_hash.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_intensity_transform.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_line_descriptor.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_mcc.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_quality.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_rapid.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_reg.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_rgbd.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_saliency.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_sfm.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_stereo.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_structured_light.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_superres.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_surface_matching.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_tracking.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_videostab.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_viz.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_wechat_qrcode.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_xfeatures2d.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_xobjdetect.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_xphoto.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_shape.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_highgui.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_datasets.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_plot.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_text.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_ml.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_phase_unwrapping.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_optflow.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_ximgproc.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_video.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_videoio.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_imgcodecs.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_objdetect.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_calib3d.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_dnn.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_features2d.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_flann.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_photo.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_imgproc.4.7.0.dylib
sobel: /opt/homebrew/lib/libopencv_core.4.7.0.dylib
sobel: CMakeFiles/sobel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/x22004xx/src/imgProc/第6回/sobel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sobel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sobel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sobel.dir/build: sobel
.PHONY : CMakeFiles/sobel.dir/build

CMakeFiles/sobel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sobel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sobel.dir/clean

CMakeFiles/sobel.dir/depend:
	cd /Users/x22004xx/src/imgProc/第6回/sobel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/x22004xx/src/imgProc/第6回/sobel /Users/x22004xx/src/imgProc/第6回/sobel /Users/x22004xx/src/imgProc/第6回/sobel/build /Users/x22004xx/src/imgProc/第6回/sobel/build /Users/x22004xx/src/imgProc/第6回/sobel/build/CMakeFiles/sobel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sobel.dir/depend

