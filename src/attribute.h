#ifndef __ATTRIBUTE_H__		
#define __ATTRIBUTE_H__

#include "base.h"

namespace glRender
{

struct Attribute {
	GLuint index;
 	GLint size;
 	GLenum type;
 	GLboolean normalized;
 	GLsizei stride;
 	const GLvoid * pointer;
};

}

#endif /* __ATTRIBUTE_H__ */