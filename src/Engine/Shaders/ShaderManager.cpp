#include "Engine/Shaders/ShaderManager.h"

namespace Engine
{
	ShaderManager::ShaderManager()
	:
	stdShader( "Res/Engine/Shaders/std.vs", "Res/Engine/Shaders/std.fs" ),
	stdNoTextureShader( "Res/Engine/Shaders/NoTex.vs", "Res/Engine/Shaders/NoTex.fs" ),
	currProgram( 0 )
	{}

	ShaderManager::~ShaderManager()
	{}

	void ShaderManager::useProgram( const Shader& shader )
	{
		GLuint program = shader.getProgram();
		if( program != this->currProgram )
		{
			glUseProgram( program );

			currProgram = program;
		}
	}
}
