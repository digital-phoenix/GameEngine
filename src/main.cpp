/*
 * test.c
 * Example of a C program that interfaces with Lua.
 * Based on Lua 5.0 code by Pedro Martelletto in November, 2003.
 * Updated to Lua 5.1. David Manura, January 2007.
 */

#include <stdlib.h>
#include <stdio.h>    

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "graphicsMain.h"

int main(){

    printf("Script Started\n");

    int status, result, i;
    double sum;
    lua_State *L;

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    luaL_openlibs(L); /* Load Lua libraries */

    lua_pushcfunction(L, init_graphics);
    lua_setglobal(L, "init_graphics");

    lua_pushcfunction(L, step_graphics_frame);
    lua_setglobal(L, "step_graphics_frame");

    lua_pushcfunction(L, cleanup_graphics);
    lua_setglobal(L, "cleanup_graphics");

    /* Load the file containing the script we are going to run */
    status = luaL_loadfile(L, "Lua/main.lua");
    if (status) {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    lua_pop(L, 1);  /* Take the returned value out of the stack */

    // SetupSDL();
    // while(Running){
    //     step_graphics_frame();
    // }
    // cleanup_graphics();

    lua_close(L);   /* Cya, Lua */
    return 0;
}



