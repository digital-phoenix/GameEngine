#ifndef __GRAPHICS_MAIN__
#define __GRAPHICS_MAIN__

#include "ShaderLoader.h"
// #include "SDL.h"
#include <stdio.h>
extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define GL_GLEXT_PROTOTYPES 1
// #include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

#ifdef __APPLE__
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
#else
	#include <GL/glu.h>
	#include <GL/glext.h>
	#include <GL/glx.h>
	#include <GL/glxext.h>
	#define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

int init_graphics (lua_State *L);
int step_graphics_frame(lua_State *L);
int cleanup_graphics(lua_State *L);

void draw();
bool processEvent(SDL_Event* Event);
void setupVAO();
void SetupSDL();

extern bool Running;
#endif