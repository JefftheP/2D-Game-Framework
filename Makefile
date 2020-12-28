#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
__CXX=cl

# define output directory
__OUTPUT=output

# define include directory
__INCLUDE_DIRS=.\include

# define lib directory
__LIB_DIR=.\lib

# define any compile-time flags
__CXXFLAGS=/Zi /D WINDOWS /Fe$(__OUTPUT)/$(__EXECUTABLE) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR)

__EXECUTABLE=game.exe

# define source directory
__SRC_DIR=src/

__EXTERNAL_LIBS= shell32.lib lib/SDL2.lib lib/SDL2main.lib lib/SDL2_image.lib

__LINKER_ARGS = /link /LIBPATH:./lib /SUBSYSTEM:CONSOLE

game.exe: src\main.cpp
	if not exist $(__OUTPUT) mkdir $(__OUTPUT)
	$(__CXX) $(__CXXFLAGS) src\main.cpp $(__EXTERNAL_LIBS) $(__LINKER_ARGS)
	copy .\lib\*.dll .\output
	

.PHONY: clean
clean:
	if exist $(__OUTPUT) rmdir /s /q $(__OUTPUT) && \
	del *.obj && \
	del *.pdb
	@echo Cleanup complete!