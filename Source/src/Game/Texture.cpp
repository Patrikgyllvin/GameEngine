#include "../../include/Game/Texture.h"

Texture::Texture()
:
texID( 0 ),
rawImage(),
loaded( false ),
w( 0 ),
h( 0 )
{}

Texture::Texture( std::string tex )
:
texID( 0 ),
rawImage(),
loaded( false ),
w( 0 ),
h( 0 )
{
	loadTexture( tex );
}

Texture::~Texture()
{
	glDeleteTextures( 1, &texID );
}

void Texture::loadTexture( std::string tFile )
{
    if( loaded )
        return;

    this->rawImage = png::image< png::rgba_pixel >( tFile.c_str() );

	if( rawImage.get_width() & ( rawImage.get_width() - 1 ) || rawImage.get_height() & ( rawImage.get_height() - 1 ) )
	{
		fprintf( stderr, "Error: texture is not power of two!\n" );
		return;
	}

    /*
	GLenum texFmt;
	GLint bpp = tex->format->BytesPerPixel;

	if( bpp == 4 )
	{
		if( tex->format->Rmask == 0x000000ff )
			texFmt = GL_RGBA;
		else
			texFmt = GL_BGRA;
	}
	else if( bpp == 3 )
	{
		if( tex->format->Rmask == 0x0000ff )
			texFmt = GL_RGB;
		else
			texFmt = GL_BGR;
	}
	else
	{
		fprintf( stderr, "Cannot load texture, Not True-Color!\n" );
		return;
	}
*/
	w = rawImage.get_width();
	h = rawImage.get_height();

	loaded = true;

	glGenTextures( 1, &texID );
	bind();

	GLfloat maxA = 0;
	glGetFloatv( GL_TEXTURE_MAX_ANISOTROPY_EXT, &maxA );

    const void* buffer = rawImage.get_pixbuf().get_row( 0 ).data();
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->w, this->h, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, buffer );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxA );

    glGenerateMipmap( GL_TEXTURE_2D );
}

void Texture::bind() const
{
	glBindTexture( GL_TEXTURE_2D, texID );
}

bool Texture::getLoaded() const
{
	return loaded;
}

const png::image< png::rgba_pixel >& Texture::getRawImage() const
{
    return this->rawImage;
}

size_t Texture::getWidth() const
{
	return w;
}

size_t Texture::getHeight() const
{
	return h;
}
