#ifndef __IMAGE_HPP__		
#define __IMAGE_HPP__

#include "base.h"

namespace glRender
{

class Image
{
private:
	std::string m_pathToFile = "";
	unsigned char* m_data = nullptr;
	int m_width = -1;
	int m_height = -1;
	int m_components = -1;

	bool m_isLoaded = false;

public:
	Image(std::string pathToFile);
    ~Image();

    bool isLoaded();

	unsigned char* data();

	int width();
	int height();
	int components();

	void clear();

};

}

#endif /* __IMAGE_HPP__ */