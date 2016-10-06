#ifndef __SHADER_LOADER__
#define __SHADER_LOADER__

#include <SDL2/SDL.h>
#ifdef __APPLE__
	#define glGenVertexArrays glGenVertexArraysAPPLE
	#define glBindVertexArray glBindVertexArrayAPPLE
	#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#else
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

#include<string>
#include <iostream>

class ShaderLoader{

	public:
		static GLuint createShader( std::string vectorShader, std::string fragmentShader);
	private:
		static unsigned long getFileSize(std::istream &file);
		static int loadShader( std::string file, std::string &shaderSource, unsigned long *length);
		inline static void printLog(std::string s){ std::cout<< __FILE__ <<" " << __LINE__ << " "<< s;}
		static int compileShader(GLuint shaderObject);
};

#endif