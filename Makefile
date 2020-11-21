#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
__CXX=cl

# define output directory
__OUTPUT=output

# define any compile-time flags
__CXXFLAGS=/Zi /Fe$(__OUTPUT)/

__EXECUTABLE=game.exe

# define include directory
__INCLUDE=include

# define source directory
__SRC=src

__EXTERNAL_LIBS= 
__LIBS=$(EXTERNAL_LIBS)
# define lib directory
__LIB=lib



game.exe: src\main.cpp
	if not exist $(__OUTPUT) mkdir $(__OUTPUT)
	$(__CXX) $(__CXXFLAGS) src\main.cpp $(__LIBS)

.PHONY: clean
clean:
	if exist $(__OUTPUT) rmdir /s /q $(__OUTPUT) && \
	del *.obj && \
	del *.pdb
	@echo Cleanup complete!