#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderingSystem.h"

#include "../CoreComponents/TransformComponent.h"

namespace Engine
{
	typedef struct {
		GLfloat x, y, z;
	} Vertex;

	typedef struct {
		GLubyte r, g, b, a;
	} Color;

	typedef struct {
		GLfloat u, v;
	} UVs;

	class StdRenderSystem : public Engine::RenderingSystem
	{
	public:
		StdRenderSystem();

		~StdRenderSystem();

		virtual bool shouldProcessEntity( const Engine::Entity& entity );
		virtual bool shouldRenderEntity( const Engine::Entity& entity );

		void drawSpriteBillboarded( glm::vec3 pos, glm::vec3 lookAtPos, int w, int h, int uP, int vP, glm::vec4 col );
		void drawQuad( glm::vec4 col );

		void drawCube( int uP, int vP, glm::vec4 col );

		void setTexture( std::string tex );

	protected:
		virtual void init( Engine::EntityManager& entityManager );

		virtual void preProcess();
		virtual void processEntity( Engine::Entity& entity );
		virtual void postProcess();

		virtual void preRender();
		virtual void renderEntity( Engine::Entity& entity );
		virtual void postRender();

	private:
		void changePerspective( int w, int h );

		glm::vec3 cam, camRotation;

		glm::mat4 transMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;

		glm::mat4 camTransMatrix;
		glm::mat4 camRotationMatrix;

		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 modelViewProjectionMatrix;

		int winW, winH;

		GLuint vao, quad, cube, UV, color;

		//Texture texture, ground;

		GLuint MVPLocation, texMatLoc, MVPLocationNoTex;
	};
}

#endif
