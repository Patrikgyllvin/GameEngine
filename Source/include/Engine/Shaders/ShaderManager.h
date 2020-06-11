#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Shader.h"

namespace Engine
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		void useProgram( const Shader& shader );
		
		const Shader standard, standardNoTexture;
	private:
		GLuint currProgram;
	};
}

#endif
