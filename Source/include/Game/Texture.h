#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <png++/png.hpp>

#include <cstdio>

class Texture
{
public:
	Texture();
	Texture( std::string tex );

	~Texture();

	void loadTexture( std::string tFile );

	bool getLoaded() const;

	void bind() const;

	size_t getWidth() const;
	size_t getHeight() const;

    const png::image< png::rgba_pixel >& getRawImage() const;

private:
	GLuint texID;
    png::image< png::rgba_pixel > rawImage;

	bool loaded;

	size_t w, h;
};

#endif
