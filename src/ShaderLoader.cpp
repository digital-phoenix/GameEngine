#include "ShaderLoader.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <exception>

unsigned long ShaderLoader::getFileSize(std::istream &file){
	if( !file.good()){
		printLog("ERROR: File is closed");
		return -1;
	}
	file.seekg(0, std::ios::end);
	unsigned long length = file.tellg();
	file.seekg(0, std::ios::beg); 
	return length;
}

int ShaderLoader::loadShader( std::string file, std::string &shaderSource, unsigned long *length){
	std::ifstream is;
	is.open(file.c_str(), std::ios::in);
	if( !is){
		printLog("Error: failed to open file");
		return -1;
	}
	
	*length = getFileSize(is);
	if( *length <= 0){
		printLog( (std::string)"Error: file " + file + " length is 0");
		is.close();
		return -2;
	}
	
	try{
		shaderSource.reserve(*length + 1);
		shaderSource.resize(*length + 1);
	}catch(	std::exception& e){
		std::cout<<"Error: file "<<file<<" is too large to store in string";
	}

	shaderSource[*length] = '\0';

	int i = 0;
	while( is.good() ){
		shaderSource[i] = is.get();
		if( !is.eof())
			i++;
	}

	shaderSource[i] = '\0';

	is.close();

	return 0;
}

GLuint ShaderLoader::createShader( std::string vectorShader, std::string fragmentShader){
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	unsigned long vertexLength, fragmentLength;
	
	loadShader(vectorShader, vertexShaderSource, &vertexLength);
	loadShader(fragmentShader, fragmentShaderSource, &fragmentLength);

	GLuint vertexShaderObject, fragmentShaderObject;
	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	char const *vertexSourcePointer = vertexShaderSource.c_str();
	char const *fragmentSourePointer = fragmentShaderSource.c_str();
	glShaderSource(vertexShaderObject, 1, &vertexSourcePointer, NULL);
	glShaderSource(fragmentShaderObject, 1, &fragmentSourePointer, NULL);

	if( compileShader(vertexShaderObject)){
		return -1;
	}

	if(compileShader(fragmentShaderObject)){
		return -1;
	}

	GLuint programObject = glCreateProgram();

	glAttachShader(programObject, vertexShaderObject);
	glAttachShader(programObject, fragmentShaderObject);
	glLinkProgram(programObject);

	GLint link;
	glGetProgramiv(programObject, GL_LINK_STATUS, &link);
	if( link){
		glDeleteShader(vertexShaderObject);
		glDeleteShader(fragmentShaderObject);
		return programObject;
	}

	GLint logLength;
	GLsizei actualLogSize;
	glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &logLength);
	if( logLength > 1){
		GLchar* log = (GLchar*) malloc(logLength);
		glGetProgramInfoLog(programObject, logLength, &actualLogSize, log);
		std::cout<<"compile log: "<<log;
		free(log);
	}

	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);
	return -1;
}

int ShaderLoader::compileShader(GLuint shaderObject){
	GLint logLength, compiled;
	GLsizei actualLogSize;

	glCompileShader(shaderObject);
	
	
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);
	if( compiled){
		return 0;
	}

	glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLength);
	if( logLength > 0){
		std::string log(logLength, '\0');
		glGetShaderInfoLog(shaderObject, logLength,&actualLogSize, (GLchar*) log.c_str());
		std::cout<<"compile log: "<< log;
	}
	return -1;
}
