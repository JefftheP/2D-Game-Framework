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

__OBJ_DIR=bin\\


# define any compile-time flags
__CXXFLAGS=/Zi /D WINDOWS /Fe$(__OUTPUT)/$(__EXECUTABLE) /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR)

__EXECUTABLE=game.exe

# define source directory
__SRC_DIR=src/

__EXTERNAL_LIBS= shell32.lib lib/SDL2.lib lib/SDL2main.lib lib/SDL2_image.lib lib/SDL2_ttf.lib lib/SDL2_mixer.lib

__LINKER_ARGS = /link /LIBPATH:./lib /SUBSYSTEM:CONSOLE

__SRC_FILES=src\main.cpp

__OBJ_FILES=bin\engine_renderer.obj \
 			bin\engine_functions.obj \
  			bin\engine_texture.obj \
   			bin\engine_timer.obj \
    		bin\engine_font.obj \
	 		bin\engine_animation.obj \
			bin\game_character.obj \
			bin\game_functions.obj \
			bin\game_movement.obj

output\game.exe: src\main.cpp $(__OBJ_FILES)
	if not exist $(__OUTPUT) mkdir $(__OUTPUT)
	$(__CXX) $(__CXXFLAGS) $(__SRC_FILES) $(__OBJ_FILES) $(__EXTERNAL_LIBS) $(__LINKER_ARGS)
	copy .\lib\*.dll .\output

bin\engine_animation.obj: src\Engine\engine_animation.cpp
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_animation.cpp

bin\engine_font.obj: src\Engine\engine_font.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_font.cpp

bin\engine_functions.obj: src\Engine\engine_functions.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_functions.cpp

bin\engine_renderer.obj: src\Engine\engine_renderer.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_renderer.cpp

bin\engine_texture.obj: src\Engine\engine_texture.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_texture.cpp

bin\engine_timer.obj: src\Engine\engine_timer.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Engine\engine_timer.cpp

bin\game_character.obj: src\Game\game_character.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Game\game_character.cpp

bin\game_functions.obj: src\Game\game_functions.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Game\game_functions.cpp

bin\game_movement.obj: src\Game\game_movement.cpp 
	$(__CXX) /c /Fo$(__OBJ_DIR) /I$(__INCLUDE_DIRS) /I$(__LIB_DIR) src\Game\game_movement.cpp

src\%.cpp:


.PHONY: clean
clean:
	if exist $(__OUTPUT) rmdir /s /q $(__OUTPUT) && \
	del *.obj && \
	del *.pdb
	@echo Cleanup complete!