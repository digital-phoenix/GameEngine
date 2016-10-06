# # Compilation directives
# MACHINE= $(shell uname -s)
# CC = g++
# CCFLAGS = -I/usr/local/include/luajit-2.0 -L/usr/local/lib/ -O2 -Wall -Os -lluajit-5.1 -lz -ldl -lm -pagezero_size 10000 -image_base 100000000

# ifeq ($(MACHINE),Darwin)
#     OPENGL_INC= -FOpenGL
#     OPENGL_LIB= framework GLUT -framework OpenGL -framework Cocoa -framework Carbon
#     SDL_INC= `sdl2-config --cflags`
#     SDL_LIB= `sdl2-config --libs`
# else
#     OPENGL_INC= -I/usr/X11R6/include
#     OPENGL_LIB= -I/usr/lib64 -lGL -lGLU
#     SDL_INC= `sdl2-config --cflags`
#     SDL_LIB= `sdl2-config --libs`
# endif

# OBJS = main.o
# TARGET = test

# #gcc -O2 -Wall -Wl, -o test main.cpp main.o -I/usr/local/include/luajit-2.0 -L/usr/local/lib/ -lluajit-5.1 -lm -ldl -pagezero_size 10000 -image_base 1

# mingw linux macosx: $(OBJS)
# 	$(TARGET) $(OBJS)

# %.o: %.cpp
# 	$(CC) $(CCFLAGS) -o $@ $<

# # %.o: %.lua
# # 	luajit -b $@

# clean:
# 	rm -f $(OBJS) $(TARGET)

# # luamain.o: script.lua
# test: C++/main.cpp \
# 	C++/graphicsMain.cpp \ 
# 	C++/ShaderLoader.h \
# 	C++/ShaderLoader.cpp \
# 	C++/main.o
# Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS = graphicsMain.o ShaderLoader.o main.o 

# Executable name
EXENAME = test

# Macros
CC = g++
CCOPTS = -c -g -O0 -O2 -Os -Wall -Wno-deprecated -I/usr/local/include/luajit-2.0
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# Testing for OS X v Linux
OS = $(shell uname -s)
LIBS = -L/usr/local/lib/ -lluajit-5.1 -lz -ldl -lm -pagezero_size 10000 -image_base 100000000
ifeq ($(OS), Darwin)
	LIBS := $(LIBS) -framework GLUT -framework OpenGL -framework Cocoa  -lglfw -framework SDL2
else
	LIBS := $(LIBS) -lGL -lGLU -lglut -sdl2
endif

# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS)

# Object files
# main.o : main.cpp
# 	$(CC) $(CCOPTS) main.cpp
graphicsMain.o : graphicsMain.cpp
	$(CC) $(CCOPTS) graphicsMain.cpp
ShaderLoader.o : ShaderLoader.cpp
	$(CC) $(CCOPTS) ShaderLoader.cpp
main.o : main.cpp
	$(CC) $(CCOPTS) main.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null