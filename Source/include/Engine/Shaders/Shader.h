#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>

#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{ 
	class Shader
	{
	public:
		Shader();
		Shader( const char* vertPath, const char* fragPath );

		~Shader();

		void loadAndCompile( const char* vertPath, const char* fragPath );

		const GLuint getProgram() const;

	private:
		GLuint programID;
	};
}

#endif
