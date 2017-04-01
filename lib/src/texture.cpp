#include "texture.hpp"
#include "opengl.h"

namespace glRender {

Texture::Texture(const char * p_pathToFile)
{
	Image* image = new Image( p_pathToFile );
	
    // if( image->isLoaded() )
	// {
		glGenTextures(1, &m_id);

		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if( image->components() == 3)
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width(), image->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->data() );
		else if( image->components() == 4)
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data() );

		glBindTexture(GL_TEXTURE_2D, 0);

		image->clear();
		delete image;
	// }
	// else
	// {
	//     printf (" %d ***************** Failed to load image ***********************\n", i);
	// 	// throw( std::string("Failed to load image") );

	// }

}

Texture::~Texture()
{
}

uint32_t Texture::id()
{
	return m_id;
}

}
