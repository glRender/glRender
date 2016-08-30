#include "image.hpp"

#define STBI_NO_GIF 1
#define STB_IMAGE_IMPLEMENTATION 1

#include "../libs/stb/stb_image.h"

namespace glRender {
Image::Image(std::string pathToFile) :
	m_pathToFile( pathToFile )
{
	m_data = stbi_load( pathToFile.c_str(), &m_width, &m_height, &m_components, STBI_rgb );

}

Image::~Image()
{
    clear();
}

bool Image::isLoaded()
{
	if( m_data == nullptr )
	{
		return false;		
	}
	else
	{
		return true;
	}
}

unsigned char* Image::data()
{
	return m_data;
}

int Image::width()
{
	return m_width;
}

int Image::height()
{
	return m_height;
}

int Image::components()
{
	return m_components;
}

void Image::clear()
{
    if( m_data != nullptr )
    {
        stbi_image_free( m_data );
        m_data = nullptr;
    }
}
	
}
