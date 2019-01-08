#include "../../include/Game/RenderSystem.h"

RenderSystem::RenderSystem()
{}

RenderSystem::~RenderSystem()
{
	glDeleteBuffers( 1, &quad );
	glDeleteBuffers( 1, &color );
	glDeleteBuffers( 1, &UV );
	glDeleteVertexArrays( 1, &vao );
}

bool RenderSystem::shouldProcessEntity( const Engine::Entity& entity )
{
    return entity.hasComponent( COMPONENT_CAMERA_BIT | COMPONENT_TRANSFORM_BIT );
}

bool RenderSystem::shouldRenderEntity( const Engine::Entity &entity )
{
    return entity.hasComponent( COMPONENT_PHYSICS_BIT );
}

void RenderSystem::init( Engine::EntityManager& entityManager )
{
	glfwGetWindowSize( glfwGetCurrentContext(), &winW, &winH );

    projectionMatrix = glm::mat4( 1.0f );
    projectionMatrix = glm::perspective<float>( 45.0f, (float) winW / (float) winH, 0.01f, 1000.0f );

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

#if !defined __APPLE__ || defined _MAC_MAKEFILE
    shader.loadAndCompile( "Res/Shaders/std.vs", "Res/Shaders/std.fs" );
    shaderNoTex.loadAndCompile( "Res/Shaders/NoTex.vs", "Res/Shaders/NoTex.fs" );
#else
    shader.loadAndCompile( "std.vs", "std.fs" );
    shaderNoTex.loadAndCompile( "NoTex.vs", "NoTex.fs" );
#endif
    glUseProgram( shader.getProgram() );
    isShaderSTD = true;
    isShaderNoTex = false;/*
#ifndef __APPLE__
    ground.loadTexture( "Res/Tex/ground.png" );

    texture.loadTexture( "Res/Tex/sheet.png" );
#else
    ground.loadTexture( "Prototype.app/Contents/Resources/Res/Tex/ground.png" );

    texture.loadTexture( "Prototype.app/Contents/Resources/Res/Tex/sheet.png" );
#endif
    texture.bind();
*/
    static Vertex quadArray[] = {
        { -0.5, -0.5, 0.0 },
        { -0.5, 0.5, 0.0 },
        { 0.5, -0.5, 0.0 },
        { 0.5, -0.5, 0.0 },
        { 0.5, 0.5, 0.0 },
        { -0.5, 0.5, 0.0 }
    };

    static Vertex cubeArray[] = {
        { -0.5, -0.5, 0.5 },
        { -0.5, 0.5, 0.5 },
        { 0.5, -0.5, 0.5 },
        { 0.5, -0.5, 0.5 },
        { 0.5, 0.5, 0.5 },
        { -0.5, 0.5, 0.5 },

        { 0.5, -0.5, 0.5 },
        { 0.5, 0.5, 0.5 },
        { 0.5, -0.5, -0.5 },
        { 0.5, -0.5, -0.5 },
        { 0.5, 0.5, -0.5 },
        { 0.5, 0.5, 0.5 },

        { 0.5, -0.5, -0.5 },
        { 0.5, 0.5, -0.5 },
        { -0.5, -0.5, -0.5 },
        { -0.5, -0.5, -0.5 },
        { -0.5, 0.5, -0.5 },
        { 0.5, 0.5, -0.5 },

        { -0.5, -0.5, -0.5 },
        { -0.5, 0.5, -0.5 },
        { -0.5, -0.5, 0.5 },
        { -0.5, -0.5, 0.5 },
        { -0.5, 0.5, 0.5 },
        { -0.5, 0.5, -0.5 },

        { -0.5, 0.5, 0.5 },
        { -0.5, 0.5, -0.5 },
        { 0.5, 0.5, 0.5 },
        { 0.5, 0.5, 0.5 },
        { 0.5, 0.5, -0.5 },
        { -0.5, 0.5, -0.5 },

        { -0.5, -0.5, 0.5 },
        { -0.5, -0.5, -0.5 },
        { 0.5, -0.5, 0.5 },
        { 0.5, -0.5, 0.5 },
        { 0.5, -0.5, -0.5 },
        { -0.5, -0.5, -0.5 }
    };

    static Color colArray[] = {
        { 0, 0, 255, 255 },
        { 255, 0, 0, 255 },
        { 0, 255, 0, 255 },
        { 255, 0, 255, 255 },
        { 255, 255, 0, 255 },
        { 0, 255, 255, 255 }
    };

	static UVs uvArray[] = {
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 0, 0 }
	};

    MVPLocation = glGetUniformLocation( shader.getProgram(), "MVP" );
    texMatLoc = glGetUniformLocation( shader.getProgram(), "textureMatrix" );
    MVPLocationNoTex = glGetUniformLocation( shaderNoTex.getProgram(), "MVP" );

    glGenBuffers( 1, &quad );
    glBindBuffer( GL_ARRAY_BUFFER, quad );
    glBufferData( GL_ARRAY_BUFFER, sizeof( quadArray ), quadArray, GL_STATIC_DRAW );

    glGenBuffers( 1, &cube );
    glBindBuffer( GL_ARRAY_BUFFER, cube );
    glBufferData( GL_ARRAY_BUFFER, sizeof( cubeArray ), cubeArray, GL_STATIC_DRAW );

    glGenBuffers( 1, &color );
    glBindBuffer( GL_ARRAY_BUFFER, color );
    //glBufferData( GL_ARRAY_BUFFER, 48, NULL, GL_STREAM_DRAW );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colArray ), colArray, GL_STATIC_DRAW );

    glGenBuffers( 1, &UV );
    glBindBuffer( GL_ARRAY_BUFFER, UV );

    //glBufferData( GL_ARRAY_BUFFER, 48, NULL, GL_STREAM_DRAW );
	glBufferData( GL_ARRAY_BUFFER, sizeof( uvArray ), uvArray, GL_STATIC_DRAW );
}

void RenderSystem::changePerspective( int w, int h )
{
	this->winW = w;
	this->winH = h;

	projectionMatrix = glm::mat4( 1.0f );
	projectionMatrix = glm::perspective<float>( 45.0f, (float) winW / (float) winH, 0.01f, 100.0f );
}

void RenderSystem::setTexture( std::string tex )
{
	//if( tex == "sheet" )
		//texture.bind();
	//else if( tex == "ground" )
		//ground.bind();
}
/*
void RenderSystem::drawSpriteBillboarded( glm::vec3 pos, glm::vec3 lookAtPos, int w, int h, int uP, int vP, glm::vec4 col )
{
	w *= 16;
	h *= 16;

	int texW = texture.getWidth(), texH = texture.getHeight();

	Color colArray[] = {
		{ col.r, col.g, col.b, col.a },
		{ col.r, col.g, col.b, col.a },
		{ col.r, col.g, col.b, col.a },
		{ col.r, col.g, col.b, col.a },
		{ col.r, col.g, col.b, col.a },
		{ col.r, col.g, col.b, col.a }
	};

	UVs uvArray[] = {
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 0, 0 }
	};

	translate( pos );

	glm::vec2 dist = glm::vec2( -lookAtPos.x, -lookAtPos.z ) - glm::vec2( pos.x, pos.z );

	rotate( RADTODEG( atan2f( dist.y, dist.x ) ) - 90, glm::vec3( 0, 1, 0 ) );

	scale( w / 16 * 1.0, h / 16 * 1.0, 1.0 );

	modelMatrix = transMatrix * rotationMatrix * scaleMatrix;

	camTransMatrix = glm::translate( glm::mat4( 1.0f ), glm::vec3( -cam.getPosX(), -cam.getPosY(), -cam.getPosZ() ) );
	camRotationMatrix = glm::rotate( camRotationMatrix, cam.getRotX(), glm::vec3( 1, 0, 0 ) );
	camRotationMatrix = glm::rotate( camRotationMatrix, cam.getRotY(), glm::vec3( 0, 1, 0 ) );
	camRotationMatrix = glm::rotate( camRotationMatrix, cam.getRotZ(), glm::vec3( 0, 0, 1 ) );
	viewMatrix = camTransMatrix * camRotationMatrix;

	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv( MVPLocation, 1, GL_FALSE, &modelViewProjectionMatrix[ 0 ][ 0 ] );

	glBindBuffer( GL_ARRAY_BUFFER, quad );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

	glBindBuffer( GL_ARRAY_BUFFER, color );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colArray ), colArray, GL_STREAM_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );

	glBindBuffer( GL_ARRAY_BUFFER, UV );
	glBufferData( GL_ARRAY_BUFFER, sizeof( uvArray ), uvArray, GL_STREAM_DRAW );

	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glDrawArrays( GL_TRIANGLES, 0, 6 );
}*/

void RenderSystem::preProcess()
{}

void RenderSystem::processEntity( Engine::Entity &entity )
{
    Engine::TransformComponent& transComp = static_cast< Engine::TransformComponent& >( entity.getFirstComponentOf( COMPONENT_TRANSFORM ) );
    this->cam.x = transComp.getPosX();
    this->cam.y = transComp.getPosY();
    this->cam.z = transComp.getPosZ();

    this->camRotation.x = transComp.getRotX();
    this->camRotation.y = transComp.getRotY();
    this->camRotation.z = transComp.getRotZ();

    camTransMatrix = glm::translate( glm::mat4( 1.0f ), glm::vec3( -cam.x, -cam.y, -cam.z ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.x, glm::vec3( 1, 0, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.y, glm::vec3( 0, 1, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.z, glm::vec3( 0, 0, 1 ) );
    viewMatrix = camTransMatrix * camRotationMatrix;
}

void RenderSystem::postProcess()
{}

void RenderSystem::preRender()
{}

void RenderSystem::renderEntity( Engine::Entity &entity )
{
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );

    if( !physComp.getBody() )
        return;

	if( !isShaderSTD && isShaderNoTex )
	{
		glUseProgram( shader.getProgram() );

		isShaderSTD = true;
		isShaderNoTex = false;
	}

	//int texW = texture.getWidth(), texH = texture.getHeight();

	//float u, v, uEnd, vEnd;

	//glm::mat4 texMat( 1.0f );

    /*
	w *= 16;
	h *= 16;

	uP *= 16;
	vP *= 16;

	texMat = glm::scale( texMat, glm::vec3( 1.0/texW, 1.0/texH, 0.0 ) );
	texMat = glm::translate( texMat, glm::vec3( uP+0.25, vP+0.25, 0.0 ) );
	texMat = glm::scale( texMat, glm::vec3( w - 0.5, h - 0.5, 0.0 ) );*/

	//glUniformMatrix4fv( texMatLoc, 1, GL_FALSE, &texMat[ 0 ][ 0 ] );

    glBindBuffer( GL_ARRAY_BUFFER, quad );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, color );

    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );

    glBindBuffer( GL_ARRAY_BUFFER, UV );

    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	//scale( w / 16 * 1.0, h / 16 * 1.0, 1.0 );

    for( b2Fixture* f = physComp.getBody()->GetFixtureList(); f; f = f->GetNext() )
    {
        const b2Vec3& fixtureData = *static_cast< const b2Vec3* >( f->GetUserData() );
        b2Vec2 centroid = static_cast< b2PolygonShape* >( f->GetShape() )->m_centroid;
        centroid *= 2;

        b2Vec2 pos = physComp.getBody()->GetPosition() + centroid;
        GLfloat width = fixtureData.x * 2, height = fixtureData.y * 2;

        transMatrix = glm::translate( glm::mat4( 1.0f ), glm::vec3( pos.x, pos.y, 0 ) );
        rotationMatrix = glm::rotate( glm::mat4( 1.0f ), glm::degrees( physComp.getBody()->GetAngle() + fixtureData.z ), glm::vec3( 0, 0, 1 ) );
        scaleMatrix = glm::scale( glm::mat4( 1.0f ), glm::vec3( width, height, 1 ) );

        modelMatrix = transMatrix * rotationMatrix * scaleMatrix;

        modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

        glUniformMatrix4fv( MVPLocation, 1, GL_FALSE, &modelViewProjectionMatrix[ 0 ][ 0 ] );
        glDrawArrays( GL_TRIANGLES, 0, 6 );
    }
}

void RenderSystem::postRender()
{}

void RenderSystem::drawQuad( glm::vec4 col )
{
	if( isShaderSTD && !isShaderNoTex )
	{
		glUseProgram( shaderNoTex.getProgram() );

		isShaderSTD = false;
		isShaderNoTex = true;
	}

	Color colArray[] = {
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
		{ static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) }
	};

	modelMatrix = transMatrix * rotationMatrix * scaleMatrix;

    camTransMatrix = glm::translate( glm::mat4( 1.0f ), glm::vec3( -cam.x, -cam.y, -cam.z ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.x, glm::vec3( 1, 0, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.y, glm::vec3( 0, 1, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.z, glm::vec3( 0, 0, 1 ) );
    viewMatrix = camTransMatrix * camRotationMatrix;

	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv( MVPLocationNoTex, 1, GL_FALSE, &modelViewProjectionMatrix[ 0 ][ 0 ] );

	glBindBuffer( GL_ARRAY_BUFFER, quad );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

	glBindBuffer( GL_ARRAY_BUFFER, color );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colArray ), colArray, GL_STREAM_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );

	glDrawArrays( GL_TRIANGLES, 0, 6 );
}

void RenderSystem::drawCube( int uP, int vP, glm::vec4 col )
{
	//int texW = texture.getWidth(), texH = texture.getHeight();

	float u, v, uEnd, vEnd;

    Color colArray[] = {
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) },
        { static_cast<GLubyte>( col.x ), static_cast<GLubyte>( col.y ), static_cast<GLubyte>( col.z ), static_cast<GLubyte>( col.w ) }
    };

    UVs uvArray[] = {
        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v },

        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v },

        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v },

        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v },

        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v },

        { u, vEnd },
        { u, v },
        { uEnd, vEnd },
        { uEnd, vEnd },
        { uEnd, v },
        { u, v }
    };

    modelMatrix = transMatrix * rotationMatrix * scaleMatrix;

    camTransMatrix = glm::translate( glm::mat4( 1.0f ), glm::vec3( -cam.x, -cam.y, -cam.z ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.x, glm::vec3( 1, 0, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.y, glm::vec3( 0, 1, 0 ) );
    camRotationMatrix = glm::rotate( camRotationMatrix, camRotation.z, glm::vec3( 0, 0, 1 ) );
    viewMatrix = camTransMatrix * camRotationMatrix;

    modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv( MVPLocation, 1, GL_FALSE, &modelViewProjectionMatrix[ 0 ][ 0 ] );

    glBindBuffer( GL_ARRAY_BUFFER, cube );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, color );
    glBufferData( GL_ARRAY_BUFFER, sizeof( colArray ), colArray, GL_STREAM_DRAW );

    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );

    glBindBuffer( GL_ARRAY_BUFFER, UV );
    glBufferData( GL_ARRAY_BUFFER, sizeof( uvArray ), uvArray, GL_STREAM_DRAW );

    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays( GL_TRIANGLES, 0, 6*6 );
}
