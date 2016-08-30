#ifndef __TEXTURE_HPP__		
#define __TEXTURE_HPP__

#include "base.h"
#include "image.hpp"

namespace glRender
{

class Texture
{
protected:
	GLuint m_id;

public:
	Texture(std::string pathToFile);
    ~Texture();

	GLuint getId();

};

}

#endif /* __TEXTURE_HPP__ */
