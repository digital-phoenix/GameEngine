#include "graphicsMain.h"

GLuint programObject;
GLuint vPos;
GLuint vao; //vertex array object
GLuint buffer;
GLuint buffer2;

float vertices[] = { -1.0, -1.0, 0.0, 1.0,
					1.0, -1.0, 0.0, 1.0,
					0.0, 1.0, 0.0, 1.0};

float vertices2[] = { -0.5, -1.0, 0.0, 1.0,
					0.5, -1.0, 0.0, 1.0,
					0.0, 1.0, 0.0, 1.0};

bool Running = true;

SDL_Window* Surf_Display = NULL;
SDL_GLContext GL_Context = NULL;
int width = 800;
int height = 600;

SDL_Event Event;

// int main(){

//     SetupSDL();
//     while(Running){
//         step_graphics_frame();
//     }
//     cleanup_graphics();

//     return 0;
// }

// void step_graphics_frame(){

// 	while(SDL_PollEvent(&Event)) {
// 		processEvent(&Event);
// 	}

// 	draw();
// }

int init_graphics (lua_State *L){
	SetupSDL();
	return 0;
}

//-----------------------------------
// Setup SDL and OpenGL
void SetupSDL(void)
{
	// init video system
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
		fprintf(stderr,"Failed to initialize SDL Video!\n");
		exit(1);
	}

	// tell system which funciton to process when exit() call is made
	atexit(SDL_Quit);

	// set opengl attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       5);
#ifdef __APPLE__
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      32);
#else
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
#endif
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,    1);

	// get a framebuffer

	Surf_Display = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	GL_Context = SDL_GL_CreateContext(Surf_Display);

	if( !Surf_Display ){
		fprintf(stderr,"Couldn't set video mode!\n%s\n", SDL_GetError());
		exit(1);
	}

	// set opengl viewport and perspective view
	glClearColor(0, 0, 0.3, 0);
	glViewport(0,0,width, height);
	glEnable(GL_TEXTURE_2D);

	printf("GL Version = %s\n", glGetString( GL_VERSION ));
	printf("GLSL Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Create and compile our GLSL program from the shaders
	programObject = ShaderLoader::createShader( "../Shaders/vertexTest.vertex", "../Shaders/fragmentTest.fragment" );
	vPos = glGetAttribLocation(programObject, "position");

	setupVAO();
}


void setupVAO(){

	// glGenVertexArrays(1, &vao);
	// glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,	sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(
		vPos,				
		4,                  // size
		GL_FLOAT,           // type
		0,					// normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDisableVertexAttribArray(vPos);


	glGenBuffers(1, &buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER,	sizeof(vertices2), vertices2, GL_STATIC_DRAW);

}

int step_graphics_frame(lua_State *L){
	bool running = true;
	while(running && SDL_PollEvent(&Event)) {
		running = processEvent(&Event);
	}

	if(running){
		draw();
	}

	lua_pushboolean(L, running);
	return 1;
}

bool processEvent(SDL_Event* Event) {
	if(Event->type == SDL_QUIT) {
		return false;
	}
	return true;
}

void draw() {
	glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programObject);
	glEnableVertexAttribArray(vPos);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(vPos);

	SDL_GL_SwapWindow(Surf_Display);
}

int cleanup_graphics(lua_State *L){
	SDL_DestroyWindow(Surf_Display);
	SDL_Quit();

	return 0;
}